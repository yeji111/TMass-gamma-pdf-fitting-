#include "TF1.h"
#include "TMath.h"

void makeFit(TFile *f, TString name){

   TH1F *h1 = (TH1F*) f->Get(Form("h_muon_pt_%s",name.Data()));
   gStyle->SetOptFit(1);
   double ne = h1-> Integral();
   
   TCanvas * c1 = new TCanvas(Form("c1_%s",name.Data()),"c",1);   
   TF1 *f1 = new TF1("f1","[2]*5*TMath::GammaDist(x,1.+[0],0,[1])/(1+exp((30-x)/0.1))",0,250);
   f1->SetParNames("p","q","number of events");
   f1->SetParameter(0,1.5); 
   f1->SetParameter(1,20.); 
   f1->SetParameter(2,ne); 
   h1->Fit("f1","0","",30, 250);
   h1->Draw("E, HIST");
   h1->GetXaxis()->SetTitle("P_{T} [GeV]");
   h1->GetYaxis()->SetTitle("Entries");
   f1->Draw("same");
   c1->Print(Form("fit_h_muon_pt_%s.pdf",name.Data()));

   cout<< "Integral = "<< ne <<endl;

   TFile fit("fit.root","update");
   f1->Write(Form("fit_h_muon_pt_%s",name.Data()));
   fit.Close();
   
}

void fit(){

   TFile *f_muon = new TFile("out.root");

   makeFit(f_muon, "166");
   makeFit(f_muon, "169");
   makeFit(f_muon, "171");
   makeFit(f_muon, "173");
   makeFit(f_muon, "175");
   makeFit(f_muon, "178");
}
