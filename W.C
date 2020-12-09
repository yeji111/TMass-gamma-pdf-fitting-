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
#include "TChain.h"

template <typename T>
void plot(T hist, TString name){
    TCanvas *c = new TCanvas("c",Form("c_%s", name.Data()));
    hist->Write(name.Data());
    hist->DrawClone();
    c->Print(Form("%s.pdf",name.Data()));
}


void W(){
	ROOT::RDataFrame df("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});
    
    auto df_s0 = df.Filter("HLT_IsoMu20","SingleMuon Trigger");

    //**** Muon Selection ( tight ) ****//
    auto df_s1 = df_s0.Define("goodMuon","Muon_pt >= 20 && abs(Muon_eta) < 2.0 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                      .Define("n_goodMuon","Sum(goodMuon)")
                      .Filter("n_goodMuon == 1","Muon Selection");
    
    //**** Jet Selection ( tight ) ****//
    auto df_s2 = df_s1.Define("goodJet","Jet_pt >= 20 && abs(Jet_eta) < 2.0 && Jet_jetId == 6")
                      .Define("n_goodJet","Sum(goodJet)")
                      .Filter("n_goodJet >= 4","Jet Selection");

    
    //**** b Tagged Jet selection ( medium )****//
    auto df_s3 = df_s2.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                      .Define("n_goodbJet","Sum(goodbJet)")
                      .Filter("n_goodbJet >= 2","bJet Selection");

     //***** MET selection *****//
     auto df_s4 = df_s3.Filter("MET_pt >= 20", "MET Selection");
     
     //*****veto selection *****//
     auto df_s5 = df_s4.Define("vetomuon", "Muon_pt>15.0 && abs(Muon_eta)<2.4 && Muon_looseId && Muon_pfRelIso04_all<0.25")
                       .Define("vetomuon_condition","!goodMuon && vetomuon")
                       .Filter("Sum(vetomuon_condition)==0","vetomuon selection");
     auto df_s6 = df_s5.Define("vetoelectron", "Electron_pt>15.0 && abs(Electron_eta)<2.4 && Electron_cutBased == 1 && ((abs(Electron_deltaEtaSC<=1.479) && abs(Electron_dxy) < 0.05 && abs(Electron_dz) < 0.10 ) || (abs(Electron_deltaEtaSC>1.479) && abs(Electron_dxy) < 0.10 && abs(Electron_dz) < 0.20))")
                      .Define("n_vetoelectron","Sum(vetoelectron)")
                      .Filter("n_vetoelectron==0", "vetoelectron selection");

    //histograms 
    auto h_muon_pt = df_s6.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_W", "h_muon_pt_W", 50, 0, 250}, "Muon1_pt");
    auto h_event = df.Histo1D({"h_event_W","h_event_W",10,0,10},"nMuon");
 
    TFile f("out_W.root", "update");

    plot(h_muon_pt, "h_muon_pt_W");
    plot(h_event, "h_event_W");

    f.Close();


}
