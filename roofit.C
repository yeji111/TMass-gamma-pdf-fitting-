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

void makeFit(TFile *f_s, TFile *f_b){

   gStyle->SetOptFit(1);

   TTree *ntuple_s = (TTree*) f_s->Get("tree");
   TTree *ntuple_b = (TTree*) f_b->Get("tree");

   cout << "n. s = " << ntuple_s->GetEntries() << endl;
   cout << "n. b = " << ntuple_b->GetEntries() << endl;

   RooRealVar Muon1_pt("Muon1_pt", "P_{T} (GeV)", 0, 250);
   RooDataSet *d_fake = new RooDataSet("d_fake", "dataset_fake", Muon1_pt, Import(*ntuple_s));
   RooDataSet *db = new RooDataSet("db", "dataset_b", Muon1_pt, Import(*ntuple_b));

   d_fake->append(*db);

   RooRealVar mass("mass", "mass", 150., 0, 250);
   RooRealVar ns("ns", "number of signal", 60000., 0, 10000);
   RooRealVar nb("nb", "number of bg", 0., 1000, 10000);
 
   RooRealVar a1("a1","a1", 1.7867);
   RooRealVar a2("a2","a2", -0.000442);
   RooRealVar a3("a3","a3", 5.068);
   RooRealVar a4("a4","a4", 0.1329);
   RooRealVar p_b("b1","b1", 0.707647);
   RooRealVar q_b("b2","b2", 42.8044);

   RooFormulaVar p_s("p_s", "a1+mass*a2", RooArgList(a1,mass,a2)); 
   RooFormulaVar q_s("q_s","a3+mass*a4", RooArgList(a3,mass,a4)); 

   RooGenericPdf fermi("fermi", "1/(1+exp((20-Muon1_pt)/0.1))", Muon1_pt);

   RooGamma gamma_s("gamma_s","gammadist_signal",Muon1_pt,p_s,q_s,RooConst(0));
   RooGamma gamma_b("gamma_b","gammadist_bg",Muon1_pt,p_b,q_b,RooConst(0));
  
   RooAbsPdf* sig = RooClassFactory::makePdfInstance("sig","gamma_s*fermi", RooArgSet(gamma_s,fermi)) ;
   RooAbsPdf* bg = RooClassFactory::makePdfInstance("bg","gamma_b*fermi", RooArgSet(gamma_b,fermi)) ;

   RooAddPdf model("model","model",RooArgList(*sig,*bg),RooArgList(ns,nb));

   RooPlot *frame = Muon1_pt.frame();
   model.fitTo(*d_fake, Extended());
   d_fake->plotOn(frame, Binning(50));
   model.plotOn(frame);
   frame->Draw();

   ns.Print();
   nb.Print();
   mass.Print();

}

void roofit(){

   TFile *f_signal = new TFile("ntuple_s.root");
   TFile *f_background = new TFile("ntuple_b.root");
   makeFit(f_signal, f_background);
}
