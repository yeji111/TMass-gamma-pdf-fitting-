#include "TF1.h"
#include "TMath.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooNovosibirsk.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooDataHist.h"
using namespace RooFit;

void makeFit(TFile *f){

   //// Get ntuple ////
   TTree *ntuple_fake = (TTree*) f->Get("tree");

   cout << "n. fake = " << ntuple_fake->GetEntries() << endl;

   RooRealVar Muon1_pt("Muon1_pt", "P_{T} (GeV)", 30, 150);

   //// Make dataset from fake ntuple ////

   RooDataSet *d_fake = new RooDataSet("d_fake", "dataset_fake", Muon1_pt, Import(*ntuple_fake));


   //// Set Variables of model function ////
   RooRealVar mass("mass", "mass", 150, 200);
   RooRealVar normalization("normalization","normalization", 0.1);
   RooRealVar mui("mui","mui", 50.2);
   RooRealVar mus("mus","mus", -0.1686);
   RooRealVar sigi("sigi","sigi", -19.91);
   RooRealVar sigs("sigs","sigs", 0.2555);
   RooRealVar taui("taui","taui", 1.257);
   RooRealVar taus("taus","taus", -0.004062);

   RooFormulaVar mu("mu","mui+mass*mus", RooArgList(mui,mass,mus)); 
   RooFormulaVar sigma("sigma","sigi+mass*sigs", RooArgList(sigi,mass,sigs)); 
   RooFormulaVar tau("tau","taui+mass*taus", RooArgList(taui,mass,taus)); 
  
   RooGenericPdf lambda("lambda", "normalization*exp(-0.5*pow(((log(1+(Muon1_pt-mu)*sinh(tau*sqrt(log(4)))/(sigma*sqrt(log(4)))))/tau),2)+pow(tau,2))", RooArgList(normalization, Muon1_pt, mu, tau, sigma));
   
   //// Fitting data to model ////
   RooPlot *frame = Muon1_pt.frame();
   RooFitResult *result = lambda.fitTo(*d_fake, Save());
   d_fake->plotOn(frame, Binning(24));
   lambda.plotOn(frame, LineColor(kBlue));   

   //// Fitting results ////
   mass.Print();
   result->Print();

   //// create NLL ////
   RooAbsReal *nll = lambda.createNLL(*d_fake);
   RooPlot *frame_nll = mass.frame(Range(170, 175));
   nll->plotOn(frame_nll, ShiftToZero());
   frame_nll -> SetMinimum(0);
   frame_nll -> SetMaximum(3);

  //// create distribution subtracted ////
  // RooRealVar mass_frame("mass_frame", "mass_frame", 165, 180);
  // RooPlot *frame_sub = mass_frame.frame(Range(165, 180));
  // RooRealVar real_mass("real_mass", "real_mass", 172.5);
  // real_mass.plotOn(frame_sub, ShiftToZero(), LineColor(kGreen));
  // mass.plotOn(frame_sub);
  // frame_sub -> SetMinimum(-4);
  // frame_sub -> SetMaximum(4);

  // frame_sub->Draw();

   //// plot ////
   TCanvas *c = new TCanvas("c_fake_unbinned_fit","c",1);
   gStyle->SetOptFit(1);
   frame->Draw();
   c->Print("unbinned_fake.pdf");

   TCanvas *c_nll = new TCanvas("c_fake_ubinned_fit_nll","c",1);
   frame_nll->Draw();
   c_nll->Print("unbinned_fake_nll.pdf");

//   TCanvas *c_sub = new TCanvas("c_fake_fit_sub","c",1);
//   frame_sub->Draw();
//   c_sub->Print("fitting_fake_sub.pdf");


   TFile fake("unbinned_fake.root","update");
   result->Write("unbinned_result");
   fake.Close();
}

void unbinned(){

   TFile *f = new TFile("ntuple_fake.root");
   makeFit(f);
}
