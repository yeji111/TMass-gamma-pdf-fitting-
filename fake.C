#include "tdrstyle.C"

void makeFake(TFile *f){

   TH1F *h1 = (TH1F*) f->Get("h_muon_pt_signal");
   TH1F *h2 = (TH1F*) f->Get("h_muon_pt_bg");
   TH1F *h3 = (TH1F*) f->Get("h_event_signal");
   TH1F *h4 = (TH1F*) f->Get("h_event_bg");
   

   double L = 59.7;
   double cs_sig = 831.;
   double cs_bg = 544.3; 
   double NGen_sig = h3->Integral();
   double NGen_bg = h4->Integral();  

   double SF_sig = L*cs_sig/NGen_sig;
   double SF_bg = L*cs_bg/NGen_bg;
   
   TCanvas *c = new TCanvas(Form("c_fake","c",1));
   h1->Scale(SF_sig);
   h2->Scale(SF_bg);

   h1->SetFillColor(kYellow); 
   h2->SetFillColor(kBlue);  

   THStack *h = new THStack();
   gStyle->SetPalette(1);

   h->Add(h1);
   h->Add(h2);

   h->Draw("hist");
   h->GetXaxis()->SetTitle("P_{T} [GeV]");
   h->GetYaxis()->SetTitle("Entries");
   
   gPad->BuildLegend();

   c->Print("h_fake_muon_pt.pdf");

   TFile fake("fake.root","update");
   h->Write("h_fake_muon_pt");
   fake.Close();

  
   return c;
}

void fake(){

   setTDRStyle();
   TFile *f_muon = new TFile("out.root");

   makeFake(f_muon);
}
