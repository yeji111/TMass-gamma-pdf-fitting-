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

   //// Get histograms ////
   TH1F *h = (TH1F*) f->Get("h_muon_pt_fake");
   RooRealVar Muon1_pt("Muon1_pt", "P_{T} (GeV)", 30, 150);
   RooDataHist data("data","dataset with muon_pt",Muon1_pt,h); 

   cout << "n. fake = " << h->GetEntries() << endl;

   //// Set variables of Constraints ////
   RooRealVar num("num","number of fake data",h->GetEntries());

   //// Set Variables of model function ////
   RooRealVar mass("mass", "mass", 30, 150);
   RooRealVar nf("ns", "number of fake", 0, 100000000);
   RooRealVar ni("ni","ni", 0.212);
   RooRealVar ns("ns","ns", -0.0006778);
   RooRealVar mui("mui","mui", 3.88);
   RooRealVar mus("mus","mus", 0.1112);
   RooRealVar sigi("sigi","sigi", -0.4083);
   RooRealVar sigs("sigs","sigs", 0.1378);
   RooRealVar taui("taui","taui", 0.7515);
   RooRealVar taus("taus","taus", -0.001007);

   RooFormulaVar normalization("normalization", "ni+mass*ns", RooArgList(ni,mass,ns)); 
   RooFormulaVar mu("mu","mui+mass*mus", RooArgList(mui,mass,mus)); 
   RooFormulaVar sigma("sigma","sigi+mass*sigs", RooArgList(sigi,mass,sigs)); 
   RooFormulaVar tau("tau","taui+mass*taus", RooArgList(taui,mass,taus)); 
  
   RooGenericPdf lamda("lamda", "normalization*exp(-0.5*pow(((log(1+(Muon1_pt-mu)*sinh(tau*sqrt(log(4)))/(sigma*sqrt(log(4)))))/tau),2)+pow(tau,2))", RooArgList(normalization, Muon1_pt, mu, tau, sigma));

   //// Make model function ////
   RooPoisson model("model", "poisson_constraints", Muon1_pt, lamda);

   //// Fitting data to model ////
   RooPlot *frame = Muon1_pt.frame();
   RooFitResult* result = model.fitTo(data, Range(30,150), Save());
   data.plotOn(frame);
   model.plotOn(frame, LineColor(kBlue));

   //// Fitting results ////
   mass.Print();
   result->Print();

   //// create NLL ////
   RooAbsReal *nll = model.createNLL(data);
   RooPlot *frame_nll = mass.frame(Range(165, 185));
   nll->plotOn(frame_nll, ShiftToZero());
   frame_nll -> SetMinimum(0);
   frame_nll -> SetMaximum(3);

   //// create distribution subtracted ////
   RooPlot *frame_sub = mass.frame(Range(165, 185));
   RooRealVar real_mass("real_mass", "real_mass", 172.5);
   real_mass.plotOn(frame_sub, ShiftToZero(), LineColor(kGreen));
   mass.plotOn(frame_sub);
   frame_sub -> SetMinimum(-4);
   frame_sub -> SetMaximum(4);

   //// plot ////
   TCanvas *c = new TCanvas("c_fake_fit","c",1);
   gStyle->SetOptFit(1);
   frame->Draw();
   c->Print("fitting_fake.pdf");

   TCanvas *c_nll = new TCanvas("c_fake_fit_nll","c",1);
   frame_nll->Draw();
   c_nll->Print("fitting_fake_nll.pdf");

   TCanvas *c_sub = new TCanvas("c_fake_fit_sub","c",1);
   frame_sub->Draw();
   c_sub->Print("fitting_fake_sub.pdf");


   TFile fake("fit_fake.root","update");
   result->Write("fitting_result");
   fake.Close();
}

void roofit(){

   TFile *f = new TFile("fake_data.root");
   makeFit(f);
}
