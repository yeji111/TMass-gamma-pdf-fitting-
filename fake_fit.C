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

   //// Get ntuples ////
   TTree *ntuple_s = (TTree*) f_s->Get("tree");
   TTree *ntuple_b = (TTree*) f_b->Get("tree");

   cout << "n. s = " << ntuple_s->GetEntries() << endl;
   cout << "n. b = " << ntuple_b->GetEntries() << endl;

   //// Set variables of Constraints ////
   RooRealVar b("b","number of background data",ntuple_b->GetEntries());
   RooRealVar s("s","number of signal data",ntuple_s->GetEntries());
   RooFormulaVar sigma_b("sigma_b","sqrt(b)", b);
   RooFormulaVar N("N","b+s",RooArgList(b,s));

   N.Print();   

   RooRealVar Muon1_pt("Muon1_pt", "P_{T} (GeV)", 0, 250);

   //// Make RooDataSet(Fake Data) ////
   RooDataSet *d_fake = new RooDataSet("d_fake", "dataset_fake", Muon1_pt, Import(*ntuple_s));
   RooDataSet *db = new RooDataSet("db", "dataset_b", Muon1_pt, Import(*ntuple_b));

   d_fake->append(*db);

   //// Set Variables of model function ////
   RooRealVar mass("mass", "mass", 0, 250);
   RooRealVar ns("ns", "number of signal", 0, 100000000);
   RooRealVar nb("nb", "number of bg", 0., 100000000);

   RooRealVar a1("a1","a1", 0.90428);
   RooRealVar a2("a2","a2", 0.002807);
   RooRealVar a3("a3","a3", 10.21);
   RooRealVar a4("a4","a4", 0.1246);
   RooRealVar p_b("p_b","p_b", 1);
   RooRealVar q_b("q_b","q_b", 37.28);
 
   RooFormulaVar p_s("p_s", "a1+mass*a2", RooArgList(a1,mass,a2)); 
   RooFormulaVar q_s("q_s","a3+mass*a4", RooArgList(a3,mass,a4)); 
   

   //// Make model function ////
   RooGenericPdf fermi("fermi", "1/(1+exp((30-Muon1_pt)/0.1))", Muon1_pt);

   RooGamma gamma_s("gamma_s","gammadist_signal",Muon1_pt,p_s,q_s,RooConst(0));
   RooGamma gamma_b("gamma_b","gammadist_bg",Muon1_pt,p_b,q_b, RooConst(0));
   
   RooAbsPdf* sig = RooClassFactory::makePdfInstance("sig","gamma_s*fermi", RooArgSet(gamma_s,fermi)) ;
   RooAbsPdf* bg = RooClassFactory::makePdfInstance("bg","gamma_b*fermi", RooArgSet(gamma_b,fermi)) ;

   RooAddPdf model("model","model",RooArgList(*sig,*bg),RooArgList(ns,nb));

/*   //// Make Constraints function ////
   RooGaussian gaus("gaus", "gaussian_constraints", nb, b, sigma_b);
   RooFormulaVar ns_nb("ns_nb","ns+nb", RooArgList(ns,nb)); 
   RooPoisson pois("pois", "poisson_constraints", N, ns_nb);

   RooProdPdf constraints("constraints","constraints",RooArgList(gaus,pois));
 */

   //// Fitting data to model ////
   RooPlot *frame = Muon1_pt.frame();
   RooFitResult* result = model.fitTo(*d_fake, Extended(), Save());//ExternalConstraints(constraints), Save());
   d_fake->plotOn(frame, Binning(50));
   model.plotOn(frame, LineColor(kBlue));

   //// Fitting results ////
   ns.Print();
   nb.Print();
   mass.Print();
   result->Print();

   //// unbinned likelihood ////
   RooAbsReal *nll = model.createNLL(*d_fake);
   RooMinimizer(*nll).migrad();
   RooPlot *frame_nll = Muon1_pt.frame();
   nll->plotOn(frame_nll, ShiftToZero());

   TCanvas *c = new TCanvas("c_fake_fit","c",1);
   gStyle->SetOptFit(1);
   frame->Draw();
   c->Print("fitting_fake.pdf");

   TCanvas *c_nll = new TCanvas("n_fake_fit_nll","c",1);
   frame_nll->Draw();
   c_nll->Print("fitting_fake_nll.pdf");

   TFile fake("fit_fake.root","update");
   result->Write("fitting_result");
   fake.Close();
}

void roofit(){

   TFile *f_signal = new TFile("ntuple_s.root");
   TFile *f_background = new TFile("ntuple_b.root");
   makeFit(f_signal, f_background);
}
