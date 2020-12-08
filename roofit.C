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

void makeFit(TFile *f, TString name){

    TH1F *h1 = (TH1F*) f->Get(Form("h_muon_pt_%s",name.Data()));

    RooRealVar Muon1_pt("Muon1_pt", "P_{T} (GeV)", 0, 250);
    RooRealVar p("p","p", 0., 10);
    RooRealVar q("q","q", 20, 50);
    RooFormulaVar p_("p_", "1+p", p); 

    RooGenericPdf fermi("fermi", "1/(1+exp((30-Muon1_pt)/0.1))", Muon1_pt);
    RooGamma gamma("gamma","gammadist",Muon1_pt,p_,q,RooConst(0));
	   
    RooProdPdf model("model", "model", RooArgSet(gamma, fermi));    

    RooPlot *frame = Muon1_pt.frame(Title(Form("gammadist fitting to %s_muon",name.Data())));
    RooDataHist dh("dh","dh",Muon1_pt, Import(*h1));
    RooFitResult* result = model.fitTo(dh, Save());
    dh.plotOn(frame, XErrorSize(0), DataError(RooAbsData::SumW2));
    model.plotOn(frame, LineColor(kRed));
    
/*   ofstream file_1;
   file_1.open ("roofit_p.txt", ios::app);
   file_1 << Form("%s ",name.Data()) << p << p.getAsymErrorHi() << p.getAsymErrorLo() << "\n";
   file_1.close();

   ofstream file_2;
   file_2.open ("roofit_q.txt", ios::app);
   file_2 << Form("%s ", name.Data()) << q << q.getAsymErrorHi() << q.getAsymErrorLo()<<"\n";
   file_2.close();

*/
    double chi2 = frame->chiSquare();
    cout << "This is chi2: " << chi2 << endl;

    model.paramOn(frame, Layout(0.7));
    dh.statOn(frame, Layout(0.7, 0.99, 0.8));
    

    p.Print();
    q.Print();
    result->Print();

    TCanvas *c = new TCanvas(Form("c_muon_pt_roofit_%s", name.Data()),"c",1);
    frame->Draw();
    c->Print(Form("roofitting_%s.pdf",name.Data()));

    TFile fit("roofit.root","update");
    frame->Write();
    result->Write(Form("fitting_result_%s",name.Data()));
    fit.Close();
}

void roofit(){

   TFile *f_muon = new TFile("out.root");

   makeFit(f_muon, "166");
   makeFit(f_muon, "169");
   makeFit(f_muon, "171");
   makeFit(f_muon, "173");
   makeFit(f_muon, "175");
   makeFit(f_muon, "178");
}
