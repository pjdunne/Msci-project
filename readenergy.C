#include "TObject.h"
#include <iostream>
#include <string>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "Particle.C"
#include "Threshold.C"
#include "Calorimetric.C"
#include "Kinematic.C"
#include "TAxis.h"
#include "TGaxis.h"
#include "TStyle.h"

int readenergy(){
  TFile* file = new TFile("/home/priyanka/Documents/project/Alastairs code/Msci-project-Alastair/Eshita4.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  //Historgram set-up
  TH1D* hE = new TH1D("hE","True energy", 100, 0, 10);
  hE->GetXaxis()->SetTitle("Energy (Gev)");
  hE->GetYaxis()->SetTitle("Number of events");
  hE->SetFillColor(kYellow-7);
  hE->SetLineColor(kBlack);
  
  TH1D* hCL = new TH1D("hCL","Liquid TPC - Calorimetric", 100, 0, 10);
  hCL->GetXaxis()->SetTitle("Energy (Gev)");
  hCL->GetYaxis()->SetTitle("Number of events");
  hCL->SetFillColor(kYellow-7);
  hCL->SetLineColor(kBlack);

  TH1D* hCL_diff = new TH1D("hCL_diff","Liquid TPC - Calorimetric difference", 100, -1, 1);
  hCL_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hCL_diff->GetYaxis()->SetTitle("Number of events");
  hCL_diff->SetFillColor(kYellow-7);
  hCL_diff->SetLineColor(kBlack);
  
  TH1D* hCG = new TH1D("hCG","Gas TCP - Calorimetric ",100,0,10);
  hCG->GetXaxis()->SetTitle("Energy (Gev)");
  hCG->GetYaxis()->SetTitle("Number of events");
  hCG->SetFillColor(kYellow-7);
  hCG->SetLineColor(kBlack);
  
  TH1D* hCG_diff = new TH1D("hCG_diff","Gas TPC - Calorimetric difference",100,-1,1);
  hCG_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hCG_diff->GetYaxis()->SetTitle("Number of events");
  hCG_diff->SetFillColor(kYellow-7);
  hCG_diff->SetLineColor(kBlack);
  
  TH1D* hKL = new TH1D("hKL","Liquid TPC - Kinematic",100,-1,10);
  hKL->GetXaxis()->SetTitle("Energy (Gev)");
  hKL->GetYaxis()->SetTitle("Number of events");
  hKL->SetFillColor(kYellow-7);
  hKL->SetLineColor(kBlack);

  TH1D* hKL_diff = new TH1D("hKL_diff","Liquid TPC - Kinematic difference",100,-1,1);
  hKL_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hKL_diff->GetYaxis()->SetTitle("Number of events");
  hKL_diff->SetFillColor(kYellow-7);
  hKL_diff->SetLineColor(kBlack);

  TH1D* hKG = new TH1D("hKG","Gas TPC - Kinematic",100,-1,10);
  hKG->GetXaxis()->SetTitle("Energy (Gev)");
  hKG->GetYaxis()->SetTitle("Number of events");
  hKG->SetFillColor(kYellow-7);
  hKG->SetLineColor(kBlack);
  
  TH1D* hKG_diff = new TH1D("hKG_diff","Gas TPC - Kinematic difference",100,-1,1);
  hKG_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hKG_diff->GetYaxis()->SetTitle("Number of events");
  hKG_diff->SetFillColor(kYellow-7);
  hKG_diff->SetLineColor(kBlack);
  
  TGaxis::SetMaxDigits(4);
  //gStyle->SetOptStat(0);     //Stats box

  vector<Particle> PartVecAboveLiquid;
  vector<Particle> PartVecAboveGas;
  vector<Particle> PartVec;
  vector<float> EVec;

  //Variables from tree
  int nfsp;                //number of final state particles
  int pdg[240];
  float px[240];
  float py[240];
  float pz[240];
  float energy[240];
  int mode;
  float Enu_t;
  float coslep;
  vector<float> Ecal;
  
  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);
  tree->SetBranchAddress("Enu_true",&Enu_t);
  tree->SetBranchAddress("CosLep",&coslep);

  int id = 0;
  Long64_t nentries = tree->GetEntries();
  
  for(unsigned int iEntry=0;iEntry< nentries;iEntry++){

    tree->GetEntry(iEntry);
    PartVec.clear();
    PartVecAboveLiquid.clear();
    PartVecAboveGas.clear();

    for (int i = 0; i < nfsp; ++i)  {
      
      id++;    
      Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
      PartVec.push_back(Part);
    }

    PartVecAboveLiquid = liquidMomThresh(PartVec);
    PartVecAboveGas = gasMomThresh(PartVec);
    
    float ECL = calorimetric(PartVecAboveLiquid);
    float ECL_diff = ECL-Enu_t;
    hCL->Fill(ECL);
    hCL_diff->Fill(ECL_diff);

    float ECG = calorimetric(PartVecAboveGas);
    float ECG_diff = ECG-Enu_t;
    hCG->Fill(ECG);
    hCG_diff->Fill(ECG_diff);

    if(mode==1){
      float EKL = kinematic(PartVecAboveLiquid,coslep);
      float EKL_diff = EKL - Enu_t;
      hKL->Fill(EKL);
      hKL_diff->Fill(EKL_diff);

      float EKG = kinematic(PartVecAboveGas,coslep);
      float EKG_diff = EKG-Enu_t;
      hKG->Fill(EKG);
      hKG_diff->Fill(EKG_diff);
    }
    hE->Fill(Enu_t);   
  }

  
  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
  
  TCanvas *c1 = new TCanvas("c1", "Calorimetric Liquid");
  hCL->Draw();

  TCanvas *c2 = new TCanvas("c2", "Calorimetric Liquid Difference");
  hCL_diff->Draw();

  TCanvas *c3 = new TCanvas("c3", "Calorimetric Gas");
  hCG->Draw();

  TCanvas *c4 = new TCanvas("c4", "Calorimetric Gas Difference");
  hCG_diff->Draw();

  TCanvas *c5 = new TCanvas("c5","Kinetic Liquid");
  hKL->Draw();

  TCanvas *c6 = new TCanvas("c6", "Kinematic Liquid Difference");
  hKL_diff->Draw();

  TCanvas *c7 = new TCanvas("c7", "Kinematic Gas");
  hKG->Draw();

  TCanvas *c8 = new TCanvas("c8", "Kinematic Gas Difference");
  hKG_diff->Draw();

  return (0);
}
