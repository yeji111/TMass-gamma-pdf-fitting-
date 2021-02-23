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

using namespace ROOT::VecOps;
using rvec_i = RVec<int>;

template <typename T>
void plot(T hist, TString name){
    TCanvas *c = new TCanvas("c",Form("c_%s", name.Data()));
    hist->Write();
    hist->DrawClone();
    c->Print(Form("%s.pdf",name.Data()));
}

int goodleading_idx(rvec_i good){
    int idx = -1;
    for( int i = 0; i < good.size(); i++){
        if(good[i]) idx = i;
        break;
    }
    return idx;
}


void Tmass(){
	ROOT::RDataFrame df_166("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop166p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop166p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root"});
	ROOT::RDataFrame df_169("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20_ext1-v1/280000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20_ext1-v1/10000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root"});
	ROOT::RDataFrame df_171("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop171p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop171p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop171p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root"});
	ROOT::RDataFrame df_173("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop173p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop173p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop173p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root"});
	ROOT::RDataFrame df_175("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop175p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop175p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20_ext1-v1/130000/*.root"});
	ROOT::RDataFrame df_178("Events", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop178p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root");
  
    auto df_s0_166 = df_166.Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_169 = df_169.Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_171 = df_171.Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_173 = df_173.Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_175 = df_175.Filter("HLT_IsoMu20","SingleMuon Trigger");
    auto df_s0_178 = df_178.Filter("HLT_IsoMu20","SingleMuon Trigger");

    //**** Muon Selection ( tight ) ****//
    auto df_s1_166 = df_166.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Filter("n_goodMuon == 1","Muon Selection")
			      .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_169 = df_169.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Filter("n_goodMuon == 1","Muon Selection")
		              .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_171 = df_171.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Filter("n_goodMuon == 1","Muon Selection")
	                      .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_173 = df_173.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Filter("n_goodMuon == 1","Muon Selection")
			      .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_175 = df_175.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Filter("n_goodMuon == 1","Muon Selection")
                              .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_178 = df_178.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Filter("n_goodMuon == 1","Muon Selection")
                              .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    
    //**** Jet Selection ( tight ) ****//
    auto df_s2_166 = df_s1_166.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_169 = df_s1_169.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_171 = df_s1_171.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_173 = df_s1_173.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_175 = df_s1_175.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_178 = df_s1_178.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");

    
    //**** b Tagged Jet selection ( medium )****//
    auto df_s3_166 = df_s2_166.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_169 = df_s2_169.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_171 = df_s2_171.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_173 = df_s2_173.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_175 = df_s2_175.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_178 = df_s2_178.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");


   //***** MET selection *****//
   auto df_s4_166 = df_s3_166.Filter("MET_pt >= 20", "MET Selection");
   auto df_s4_169 = df_s3_169.Filter("MET_pt >= 20", "MET Selection");
   auto df_s4_171 = df_s3_171.Filter("MET_pt >= 20", "MET Selection");
   auto df_s4_173 = df_s3_173.Filter("MET_pt >= 20", "MET Selection");
   auto df_s4_175 = df_s3_175.Filter("MET_pt >= 20", "MET Selection");
   auto df_s4_178 = df_s3_178.Filter("MET_pt >= 20", "MET Selection");
    
   //***** W boson transverse mass selection *****//
   auto df_s5_166 = df_s4_166.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_169 = df_s4_169.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_171 = df_s4_171.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_173 = df_s4_173.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_175 = df_s4_175.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_178 = df_s4_178.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");

    //histograms 
    auto h_muon_pt_166 = df_s5_166.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_166", "h_muon_pt_166", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_169 = df_s5_169.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_169", "h_muon_pt_169", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_171 = df_s5_171.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_171", "h_muon_pt_171", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_173 = df_s5_173.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_173", "h_muon_pt_173", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_175 = df_s5_175.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_175", "h_muon_pt_175", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_178 = df_s5_178.Define("Muon1_pt","Muon_pt[goodMuon]").Histo1D({"h_muon_pt_178", "h_muon_pt_178", 24, 30, 150}, "Muon1_pt");
/*
    auto h_event_166 = df_166.Histo1D({"h_event_166","h_event_166",10,0,10},"nMuon");
    auto h_event_169 = df_169.Histo1D({"h_event_169","h_event_169",10,0,10},"nMuon");
    auto h_event_171 = df_171.Histo1D({"h_event_171","h_event_171",10,0,10},"nMuon");
    auto h_event_173 = df_173.Histo1D({"h_event_173","h_event_173",10,0,10},"nMuon");
    auto h_event_175 = df_175.Histo1D({"h_event_175","h_event_175",10,0,10},"nMuon");
    auto h_event_178 = df_178.Histo1D({"h_event_178","h_event_178",10,0,10},"nMuon");
*/ 
    TFile f("out.root", "recreate");

    plot(h_muon_pt_166, "h_muon_pt_166");
    plot(h_muon_pt_169, "h_muon_pt_169");
    plot(h_muon_pt_171, "h_muon_pt_171");
    plot(h_muon_pt_173, "h_muon_pt_173");
    plot(h_muon_pt_175, "h_muon_pt_175");
    plot(h_muon_pt_178, "h_muon_pt_178");
/*
    plot(h_event_166, "h_event_166");
    plot(h_event_169, "h_event_169");
    plot(h_event_171, "h_event_171");
    plot(h_event_173, "h_event_173");
    plot(h_event_175, "h_event_175");
    plot(h_event_178, "h_event_178");
*/
    f.Close();


}
