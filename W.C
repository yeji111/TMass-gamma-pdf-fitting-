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

using namespace ROOT::VecOps;
using rvec_i = RVec<int>;


template <typename T>
void plot(T hist, TString name){
    TCanvas *c = new TCanvas("c",Form("c_%s", name.Data()));
    hist->Write(name.Data());
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


void W(){
        ROOT::RDataFrame df_1345("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/40000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});
        ROOT::RDataFrame df_359("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/30000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});
       ROOT::RDataFrame df_48("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/40000/*.root", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});
      ROOT::RDataFrame df_12("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/40000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});
      ROOT::RDataFrame df_5("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/40000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});
      ROOT::RDataFrame df_1("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/*.root"});
      ROOT::RDataFrame df_0("Events", {"/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/230000/*.root","/xrootd/store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root"});

    //lumi = 15
    auto df_s0_1345 = df_1345.Range(20175000, 0);
    auto df_s0_359 = df_359.Range(5395500, 0);
    auto df_s0_48 = df_48.Range(733650, 0);
    auto df_s0_12 = df_12.Range(180750, 0);
    auto df_s0_5 = df_5.Range(82515, 0);
    auto df_s0_1 = df_1.Range(19935, 0);
    auto df_s0_0 = df_0.Range(482, 0); 
    
    //**** Muon Selection ( tight ) ****//
    auto df_s1_1345 = df_s0_1345.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                                .Define("n_goodMuon","Sum(goodMuon)")
                                .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                                .Filter("n_goodMuon == 1","Muon Selection")
                                .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_359 = df_s0_359.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                              .Define("n_goodMuon","Sum(goodMuon)")
                              .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                              .Filter("n_goodMuon == 1","Muon Selection")
                              .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_48 = df_s0_48.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                            .Define("n_goodMuon","Sum(goodMuon)")
                            .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                            .Filter("n_goodMuon == 1","Muon Selection")
                            .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_12 = df_s0_12.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                            .Define("n_goodMuon","Sum(goodMuon)")
                            .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                            .Filter("n_goodMuon == 1","Muon Selection")
                            .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_5 = df_s0_5.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                          .Define("n_goodMuon","Sum(goodMuon)")
                          .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                          .Filter("n_goodMuon == 1","Muon Selection")
                          .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_1 = df_s0_1.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                          .Define("n_goodMuon","Sum(goodMuon)")
                          .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                          .Filter("n_goodMuon == 1","Muon Selection")
                          .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});
    auto df_s1_0 = df_s0_0.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                          .Define("n_goodMuon","Sum(goodMuon)")
                          .Define("Muon1_pt","Muon_pt[goodMuon][0]")
                          .Filter("n_goodMuon == 1","Muon Selection")
                          .Define("goodMuon_leading_idx",goodleading_idx,{"goodMuon"});

    //**** Jet Selection ( tight ) ****//
    auto df_s2_1345 = df_s1_1345.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                                .Define("n_goodJet","Sum(goodJet)")
                                .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_359 = df_s1_359.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                              .Define("n_goodJet","Sum(goodJet)")
                              .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_48 = df_s1_48.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                            .Define("n_goodJet","Sum(goodJet)")
                            .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_12 = df_s1_12.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                            .Define("n_goodJet","Sum(goodJet)")
                            .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_5 = df_s1_5.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                          .Define("n_goodJet","Sum(goodJet)")
                          .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_1 = df_s1_1.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                          .Define("n_goodJet","Sum(goodJet)")
                          .Filter("n_goodJet >= 4","Jet Selection");
    auto df_s2_0 = df_s1_0.Define("goodJet","Jet_pt >= 30 && abs(Jet_eta) < 2.5 && Jet_jetId == 6")
                          .Define("n_goodJet","Sum(goodJet)")
                          .Filter("n_goodJet >= 4","Jet Selection");

    
    //**** b Tagged Jet selection ( medium )****//
    auto df_s3_1345 = df_s2_1345.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                                .Define("n_goodbJet","Sum(goodbJet)")
                                .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_359 = df_s2_359.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                              .Define("n_goodbJet","Sum(goodbJet)")
                              .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_48 = df_s2_48.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                            .Define("n_goodbJet","Sum(goodbJet)")
                            .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_12 = df_s2_12.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                            .Define("n_goodbJet","Sum(goodbJet)")
                            .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_5 = df_s2_5.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                          .Define("n_goodbJet","Sum(goodbJet)")
                          .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_1 = df_s2_1.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                          .Define("n_goodbJet","Sum(goodbJet)")
                          .Filter("n_goodbJet >= 2","bJet Selection");
    auto df_s3_0 = df_s2_0.Define("goodbJet","goodJet && Jet_btagDeepFlavB > 0.277")
                          .Define("n_goodbJet","Sum(goodbJet)")
                          .Filter("n_goodbJet >= 2","bJet Selection");

    //***** MET selection *****//
    auto df_s4_1345 = df_s3_1345.Filter("MET_pt >= 20", "MET Selection");
    auto df_s4_359 = df_s3_359.Filter("MET_pt >= 20", "MET Selection");
    auto df_s4_48 = df_s3_48.Filter("MET_pt >= 20", "MET Selection");
    auto df_s4_12 = df_s3_12.Filter("MET_pt >= 20", "MET Selection");
    auto df_s4_5 = df_s3_5.Filter("MET_pt >= 20", "MET Selection");
    auto df_s4_1 = df_s3_1.Filter("MET_pt >= 20", "MET Selection");
    auto df_s4_0 = df_s3_0.Filter("MET_pt >= 20", "MET Selection");

   //***** W boson transverse mass selection *****//
   auto df_s5_1345 = df_s4_1345.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                               .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_359 = df_s4_359.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                             .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_48 = df_s4_48.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                           .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_12 = df_s4_12.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                           .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_5 = df_s4_5.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                         .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_1 = df_s4_1.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                         .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
   auto df_s5_0 = df_s4_0.Define("WTmass","sqrt(Muon_pt[goodMuon_leading_idx]*MET_pt*(1-cos(Muon_phi[goodMuon_leading_idx]-MET_phi)))")
                         .Filter("(WTmass+MET_pt)>=60", "WTmass Selection");
 

    //histograms 
    auto h_muon_pt_W_1345 = df_s5_1345.Histo1D({"h_muon_pt_W_1345", "h_muon_pt_W_1345", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_W_359 = df_s5_359.Histo1D({"h_muon_pt_W_359", "h_muon_pt_W_359", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_W_48 = df_s5_48.Histo1D({"h_muon_pt_W_48", "h_muon_pt_W_48", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_W_12 = df_s5_12.Histo1D({"h_muon_pt_W_12", "h_muon_pt_W_12", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_W_5 = df_s5_5.Histo1D({"h_muon_pt_W_5", "h_muon_pt_W_5", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_W_1 = df_s5_1.Histo1D({"h_muon_pt_W_1", "h_muon_pt_W_1", 24, 30, 150}, "Muon1_pt");
    auto h_muon_pt_W_0 = df_s5_0.Histo1D({"h_muon_pt_W_0", "h_muon_pt_W_0", 24, 30, 150}, "Muon1_pt");

    TFile f("out_W.root", "recreate");

    plot(h_muon_pt_W_1345, "h_muon_pt_W_1345");
    plot(h_muon_pt_W_359, "h_muon_pt_W_359");
    plot(h_muon_pt_W_48, "h_muon_pt_W_48");
    plot(h_muon_pt_W_12, "h_muon_pt_W_12");
    plot(h_muon_pt_W_5, "h_muon_pt_W_5");
    plot(h_muon_pt_W_1, "h_muon_pt_W_1");
    plot(h_muon_pt_W_0, "h_muon_pt_W_0");

    f.Close();

}
