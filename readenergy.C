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
  TH1D* hE = new TH1D("hE"," ", 100, 0, 10);
  hE->GetXaxis()->SetTitle("Energy (Gev)");
  hE->GetYaxis()->SetTitle("Number of events");
  hE->SetFillColor(kYellow-7);
  hE->SetLineColor(kBlack);
  hE->SetStats(kFALSE);
  TH1D* hC = new TH1D("hC"," ", 100, 0, 10);
  hC->GetXaxis()->SetTitle("Energy (Gev)");
  hC->GetYaxis()->SetTitle("Number of events");
  hC->SetFillColor(kYellow-7);
  hC->SetLineColor(kBlack);
  hC->SetStats(kFALSE);
  TH1D* hK = new TH1D("hK"," ",100,-5,10);
  hK->GetXaxis()->SetTitle("Energy (Gev)");
  hK->GetYaxis()->SetTitle("Number of events");
  hK->SetFillColor(kYellow-7);
  hK->SetLineColor(kBlack);
  hK->SetStats(kFALSE);
  TGaxis::SetMaxDigits(4);


  vector<Particle> PartVecAbove;
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
    PartVecAbove.clear();

    for (int i = 0; i < nfsp; ++i)  {
      
      id++;
              
      Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);

      PartVec.push_back(Part);
    }

    PartVecAbove=threshold(PartVec);
    float Ec = calorimetric(PartVecAbove);
    Ecal.push_back(Ec);
    float Ec_diff = Ec-Enu_t;
    hC->Fill(Ec);
    if(mode==1){
      float Ek = kinematic(PartVecAbove,coslep);
      float Ek_diff = Ek - Enu_t;
      hK->Fill(Ek);
    }
    hE->Fill(Enu_t);   
  }

  
  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
  
  TCanvas *c1 = new TCanvas("c1", "Calorimetric Plot");
  hC->Draw();

  TCanvas *c2 = new TCanvas("c2","Kinetic Plot");
  hK->Draw();
  
return (0);
}
 
