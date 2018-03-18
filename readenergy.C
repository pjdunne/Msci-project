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
#include "Identify.C"
// #include "Resolution.C"

int readenergy(){
  TFile* file = new TFile("/Users/AnishaKadri/Desktop/Final/Eshita4.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  //HISTOGRAM SET UP
  TH1D* hE = new TH1D("hE","True energy", 100, 0, 10);
  hE->GetXaxis()->SetTitle("Energy (Gev)");
  hE->GetYaxis()->SetTitle("Number of events");
  hE->SetFillColor(kYellow-7);
  hE->SetLineColor(kBlack);
  
  TH1D* hCL = new TH1D("hCL","Liquid TPC - Calorimetric", 100, -1, 15);
  hCL->GetXaxis()->SetTitle("Energy (Gev)");
  hCL->GetYaxis()->SetTitle("Number of events");
  hCL->SetFillColor(kYellow-7);
  hCL->SetLineColor(kBlack);

  TH1D* hCL_diff = new TH1D("hCL_diff","Liquid TPC - Calorimetric difference", 100, -10, 2);
  hCL_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hCL_diff->GetYaxis()->SetTitle("Number of events");
  hCL_diff->SetFillColor(kYellow-7);
  hCL_diff->SetLineColor(kBlack);

  TH2D* hCL_diff_true = new TH2D("hCL_diff_true","Liquid TPC - Calorimetric difference as function of true energy",100,0,12,100,-10,2);
  hCL_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hCL_diff_true->GetYaxis()->SetTitle("Calorimetric reconstructed energy difference (GeV)");
  
  TH1D* hCG = new TH1D("hCG","Gas TCP - Calorimetric ",100,-1,15);
  hCG->GetXaxis()->SetTitle("Energy (Gev)");
  hCG->GetYaxis()->SetTitle("Number of events");
  hCG->SetFillColor(kYellow-7);
  hCG->SetLineColor(kBlack);
  
  TH1D* hCG_diff = new TH1D("hCG_diff","Gas TPC - Calorimetric difference",100,-10,2);
  hCG_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hCG_diff->GetYaxis()->SetTitle("Number of events");
  hCG_diff->SetFillColor(kYellow-7);
  hCG_diff->SetLineColor(kBlack);

  TH2D* hCG_diff_true = new TH2D("hCG_diff_true","Gas TPC - Calorimetric difference as function of true energy",100,0,12,100,-10,2);
  hCG_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hCG_diff_true->GetYaxis()->SetTitle("Calorimetric reconstructed energy difference (GeV)");
    
  TH1D* hKL = new TH1D("hKL","Liquid TPC - Kinematic",100,-1,10);
  hKL->GetXaxis()->SetTitle("Energy (Gev)");
  hKL->GetYaxis()->SetTitle("Number of events");
  hKL->SetFillColor(kYellow-7);
  hKL->SetLineColor(kBlack);

  TH1D* hKL_diff = new TH1D("hKL_diff","Liquid TPC - Kinematic difference",100,-5,5);
  hKL_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hKL_diff->GetYaxis()->SetTitle("Number of events");
  hKL_diff->SetFillColor(kYellow-7);
  hKL_diff->SetLineColor(kBlack);

  TH2D* hKL_diff_true = new TH2D("hKL_diff_true","Liquid TPC - Kinematic difference as function of true energy",100,0,12,100,-5,10);
  hKL_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKL_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TH1D* hKG = new TH1D("hKG","Gas TPC - Kinematic",100,-1,10);
  hKG->GetXaxis()->SetTitle("Energy (Gev)");
  hKG->GetYaxis()->SetTitle("Number of events");
  hKG->SetFillColor(kYellow-7);
  hKG->SetLineColor(kBlack);
  
  TH1D* hKG_diff = new TH1D("hKG_diff","Gas TPC - Kinematic difference",100,-5,5);
  hKG_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hKG_diff->GetYaxis()->SetTitle("Number of events");
  hKG_diff->SetFillColor(kYellow-7);
  hKG_diff->SetLineColor(kBlack);

  TH2D* hKG_diff_true = new TH2D("hKG_diff_true","Gas TPC - Kinematic difference as function of true energy",100,0,12,100,-10,5);
  hKG_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TGaxis::SetMaxDigits(4);
  //gStyle->SetOptStat(0);     //to include stats box

  vector<Particle> PartVecAboveLiquid;
  vector<Particle> PartVecAboveGas;
  vector<Particle> PartVec;
  vector<float> EVec; // do we need this??

  //LOADING VARS FROM TREE
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
  
  for(unsigned int iEntry=0;iEntry<nentries;iEntry++){

    tree->GetEntry(iEntry);
    PartVec.clear();
    PartVecAboveLiquid.clear();
    PartVecAboveGas.clear();



    for (int i = 0; i < nfsp; ++i)  {
	
	   id++;    
	   Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
	   PartVec.push_back(Part);
      }

    //THRESHOLD:
    PartVecAboveLiquid = liquidMomThresh(PartVec);
    PartVecAboveGas = gasMomThresh(PartVec);

    //SMEARING:

    //MODE SELECTION
    if (id_0pi(PartVec) == 1){ // use this to choose 0 pi modes
     //if (id_1pi(PartVec) == 1){ // use this to choose 1 pi modes
     //if (id_0pi(PartVec) == 0 && id_1pi(PartVec) == 0){ // use this to choose other modes


      //DEBUGGING STATEMENTS
      //std:: cout<<"Partvec: "<< PartVec.size()<<"  Partvecaboveliquid: "<<PartVecAboveLiquid.size()<< "   Partvecabovegas: "<< PartVecAboveGas.size()<<"   mode: "<<mode<<endl;
      //cout<<"NFSP: "<<nfsp<<"    MODE: "<<mode<<endl;
        /*for (int j=0; j<PartVec.size();j++){
          Particle part = PartVec[j];
          if (abs(part.GetPDG())==11){ //(abs(part.GetPDG()) != 211 && abs(part.GetPDG()) != 2112 && abs(part.GetPDG()) != 111 && abs(part.GetPDG()) != 2212 && abs(part.GetPDG()) != 13 && abs(part.GetPDG()) != 14){
            cout<<part.GetPDG()<<endl;
          }
        }*/

    
        float ECL = calorimetric(PartVecAboveLiquid);
        float ECL_diff = ECL-Enu_t;
        hCL->Fill(ECL);
        hCL_diff->Fill(ECL_diff);
        hCL_diff_true->Fill(Enu_t,ECL_diff);
      
        float ECG = calorimetric(PartVecAboveGas);
        float ECG_diff = ECG-Enu_t;
        hCG->Fill(ECG);
        hCG_diff->Fill(ECG_diff);
        hCG_diff_true->Fill(Enu_t,ECG_diff);
    
        float EKL = kinematic(PartVecAboveLiquid,coslep);
        if (EKL != 0){
          float EKL_diff = EKL - Enu_t;
          hKL->Fill(EKL);
          hKL_diff->Fill(EKL_diff);
          hKL_diff_true->Fill(Enu_t,EKL_diff);
        }
            
        float EKG = kinematic(PartVecAboveGas,coslep);
        if (EKG != 0){
          float EKG_diff = EKG-Enu_t;
          hKG->Fill(EKG);
          hKG_diff->Fill(EKG_diff);
          hKG_diff_true->Fill(Enu_t,EKG_diff);
        }
    
        hE->Fill(Enu_t);
    }
  }

  /*
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

  TCanvas *c5 = new TCanvas("c5", "Kinetic Liquid");
  hKL->Draw();

  TCanvas *c6 = new TCanvas("c6", "Kinematic Liquid Difference");
  hKL_diff->Draw();

  TCanvas *c7 = new TCanvas("c7", "Kinematic Gas");
  hKG->Draw();

  TCanvas *c8 = new TCanvas("c8", "Kinematic Gas Difference");
  hKG_diff->Draw();
  */
  
  return (0);
}
