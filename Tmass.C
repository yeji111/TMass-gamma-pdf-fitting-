#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "ROOT/RDF/RInterface.hxx"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "Math/Vector4Dfwd.h"
#include "TStyle.h"
#include <vector>

template <typename T>
void plot(T hist, TString name){
    TCanvas *c = new TCanvas("c",Form("c_%s", name.Data()));
    hist->Write();
    hist->DrawClone();
    c->Print(Form("%s.pdf",name.Data()));
}


void Tmass(){

        std::vector<string> obj = {"Muon1_pt"};


	ROOT::RDataFrame df_signal("Events", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop175p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20_ext1-v1/130000/*.root");
	ROOT::RDataFrame df_bg("Events", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root");
//	ROOT::RDataFrame df_fake("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop175p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20_ext1-v1/130000/*.root"});
    
//   double L = 59.7;
//   double cs_sig = 831.;
//   double cs_bg = 544.3;
//   L*cs_sig = 49610700;

//    auto df_s0_fake = df_fake.Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_signal = df_signal.Range(49610700).Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_bg = df_bg.Filter("HLT_IsoMu20","SingleMuon Trigger");

    auto n_signal = df_signal.Count();
    auto n_bg = df_bg.Count();
    cout << " n. signal = " << *n_signal << " n. bg = " << *n_bg << endl;
 
    //**** Muon Selection ( tight ) ****//
    auto df_s1_signal = df_s0_signal.Define("goodMuon","Muon_pt >= 20 && abs(Muon_eta) < 2.0 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                                    .Define("n_goodMuon","Sum(goodMuon)")
                                    .Filter("n_goodMuon == 1","Muon Selection");
    auto df_s1_bg = df_s0_bg.Define("goodMuon","Muon_pt >= 20 && abs(Muon_eta) < 2.0 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                            .Define("n_goodMuon","Sum(goodMuon)")
                            .Filter("n_goodMuon == 1","Muon Selection");
    
    //**** Jet Selection ( tight ) ****//
    auto df_s2_signal = df_s1_signal.Define("goodJet","Jet_pt >= 20 && abs(Jet_eta) < 2.0 && Jet_jetId == 6")
                                    .Define("n_goodJet","Sum(goodJet)")
                                    .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_bg = df_s1_bg.Define("goodJet","Jet_pt >= 20 && abs(Jet_eta) < 2.0 && Jet_jetId == 6")
                            .Define("n_goodJet","Sum(goodJet)")
                            .Filter("n_goodJet >= 4","Jet Selection");

    
    //**** b Tagged Jet selection ( medium )****//
    auto df_s3_signal = df_s2_signal.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                                    .Define("n_goodbJet","Sum(goodbJet)")
                                    .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_bg = df_s2_bg.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                            .Define("n_goodbJet","Sum(goodbJet)")
                            .Filter("n_goodbJet >= 2","bJet Selection");

   //***** MET selection *****//
   auto df_s4_signal = df_s3_signal.Filter("MET_pt >= 20", "MET Selection");
   auto df_s4_bg = df_s3_bg.Filter("MET_pt >= 20", "MET Selection");


   //***** Muon_pt Definition *****//    
   auto df_s5_signal = df_s4_signal.Define("Muon1_pt","Muon_pt[goodMuon][0]");
   auto df_s5_bg = df_s4_bg.Define("Muon1_pt","Muon_pt[goodMuon][0]");
   
    //histograms 
    auto h_muon_pt_signal = df_s5_signal.Histo1D({"h_muon_pt_signal", "h_muon_pt_signal", 50, 0, 250}, "Muon1_pt");
    auto h_muon_pt_bg = df_s5_bg.Histo1D({"h_muon_pt_bg", "h_muon_pt_bg", 50, 0, 250}, "Muon1_pt");

    auto h_event_signal = df_signal.Histo1D({"h_event_signal","h_event_signal",10,0,10},"nMuon");
    auto h_event_bg = df_bg.Histo1D({"h_event_bg","h_event_bg",10,0,10},"nMuon");

    //ntuple
    df_s5_signal.Snapshot("tree","ntuple_s.root",obj);
    df_s5_bg.Snapshot("tree","ntuple_b.root",obj);
          

    TFile f("out.root", "recreate");
 
    plot(h_muon_pt_signal, "h_muon_pt_signal");
    plot(h_muon_pt_bg, "h_muon_pt_bg");

    plot(h_event_signal, "h_event_signal");
    plot(h_event_bg, "h_event_bg");

    f.Close();


}
