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

void Wmass(){
     ROOT::RDataFrame df_178("Events", "/xrootd/store/mc/RunIIAutumn18NanoAODv6/TTToSemiLeptonic_mtop178p5_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/*.root");
     auto df_s0_178 = df_178.Range(1000);
     auto df_s1_178 = df_s0_178.Define("goodMuon","Muon_pt >= 30 && abs(Muon_eta) < 2.5 && Muon_tightId && Muon_pfRelIso04_all < 0.15")
                               .Define("n_goodMuon","Sum(goodMuon)")
                               .Define("WTmass","sqrt(Muon_pt*Met_sumEt*(1-cos(Muon_phi-MET_phi))")
                               .Filter("(WTmass+MET_sumET)>=60", "WTmass Selection")
                               .Filter("n_goodMuon == 1","Muon Selection");
    

}
