#include "TF1.h"
#include "TMath.h"

void makeFit(TFile *f, TString name){

   TH1F *h1 = (TH1F*) f->Get(Form("h_muon_pt_%s",name.Data()));
   gStyle->SetOptFit(1);

   TCanvas * c1 = new TCanvas(Form("c1_%s",name.Data()),"c",1);   
   TF1 *f1 = new TF1("f1","[0]*TMath::Exp(-0.5*TMath::Power((TMath::Log(1+(x-[1])*TMath::SinH([2]*TMath::Sqrt(TMath::Log(4)))/([3]*TMath::Sqrt(TMath::Log(4))))/[2]),2)+TMath::Power([2],2))",30,150);
   f1->SetParNames("normalisation","mu","tau","sigma");
   f1->FixParameter(0,0.12); 
   f1->FixParameter(1,26); 
   f1->FixParameter(2,22);
   f1->FixParameter(2,0.44);
  // h1->Fit("f1","0","",20, 250);
  // h1->Draw("HIST");
  // h1->GetXaxis()->SetTitle("P_{T} [GeV]");
  // h1->GetYaxis()->SetTitle("Entries");
   f1->Draw();//"same");
  // c1->Print(Form("fit_h_muon_pt_%s.pdf",name.Data()));

   //TFile fit("fit.root","update");
   //f1->Write(Form("fit_h_muon_pt_%s",name.Data()));
   //fit.Close();
   
}

void fit(){

   TFile *f_muon = new TFile("out.root");

   makeFit(f_muon, "171");
}
