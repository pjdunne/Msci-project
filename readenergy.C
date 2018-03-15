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
  TFile* file = new TFile("/home/priyanka/Documents/project/Msci-project/Eshita4.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  //Historgram set-up
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
  
  TH2D* hCL_diff_true_frac = new TH2D("hCL_diff_true_frac","Liquid TPC - Fractional calorimetric difference as function of true energy",100,0,12,100,-1,0.2);
  hCL_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCL_diff_true_frac->GetYaxis()->SetTitle("Fractional calorimetric reconstructed energy difference");
  
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
  
  TH2D* hCG_diff_true_frac = new TH2D("hCG_diff_true_frac","Gas TPC - Fractional calorimetric difference as function of true energy",100,0,12,100,-1,0.2);
  hCG_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCG_diff_true_frac->GetYaxis()->SetTitle("Fractional calorimetric reconstructed energy difference");
  
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
  
  TH2D* hKL_diff_true_frac = new TH2D("hKL_diff_true_frac","Liquid TPC - Fractional kinematic difference as function of true energy",100,0,12,100,-1,5);
  hKL_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hKL_diff_true_frac->GetYaxis()->SetTitle("Fractional kinematic reconstructed energy difference");
  
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

  TH2D* hKG_diff_true = new TH2D("hKG_diff_true","Gas TPC - Kinematic difference as function of true energy",100,0,12,100,-1,5);
  hKG_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TH2D* hKG_diff_true_frac = new TH2D("hKG_diff_true_frac","Gas TPC - Fractional kinematic difference as function of true energy",100,0,12,100,-1,5);
  hKG_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true_frac->GetYaxis()->SetTitle("Fractional kinematic reconstructed energy difference");

  TH2D* hCKL_diff = new TH2D("hCKL_diff","Liquid TPC - Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKL_diff->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKL_diff->GetYaxis()->SetTitle("E_cal - E_kin (GeV)");

  TH2D* hCKG_diff = new TH2D("hCKG_diff","Gas TPC - Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKG_diff->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKG_diff->GetYaxis()->SetTitle("E_cal - E_kin (GeV)");
 
  TH3D* hL_cal_kin_true = new TH3D("hL_cal_kin_true","Liquid TPC - Calorimetric and kinematic as a function of true",100,-1,12,100,-1,12,100,0,12);
  hL_cal_kin_true->GetXaxis()->SetTitle("Calorimetirc Energy (GeV)");
  hL_cal_kin_true->GetYaxis()->SetTitle("Kinematic energy (GeV)");
  hL_cal_kin_true->GetZaxis()->SetTitle("True (GeV)");

  TH3D* hL_cal_kin_diff_true = new TH3D("hL_cal_kin_diff_true","Liquid TPC - Calorimetric and kinematic differences as a function of true",100,-0.8,0.1,100,-1,1.5,100,0,12);
  hL_cal_kin_diff_true->GetXaxis()->SetTitle("Calorimetirc Energy difference (GeV)");
  hL_cal_kin_diff_true->GetYaxis()->SetTitle("Kinematic energy difference (GeV)");
  hL_cal_kin_diff_true->GetZaxis()->SetTitle("True (GeV)");
  
  TGaxis::SetMaxDigits(4);
  //gStyle->SetOptStat(0);     //Stats box
  

  vector<Particle> PartVecAboveLiquid;
  vector<Particle> PartVecAboveGas;
  vector<Particle> PartVec;

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

    if(mode==1){          //select mode/topology
      for (int i = 0; i < nfsp; ++i)  {
	
	id++;    
	Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
	PartVec.push_back(Part);
      }

      PartVecAboveLiquid = liquidMomThresh(PartVec);
      PartVecAboveGas = gasMomThresh(PartVec);
      //std:: cout<<"Partvec: "<< PartVec.size()<<"  Partvecaboveliquid: "<<PartVecAboveLiquid.size()<< "   Partvecabovegas: "<< PartVecAboveGas.size()<<"   mode: "<<mode<<endl;
      //cout<<"NFSP: "<<nfsp<<"    MODE: "<<mode<<endl;
      /*for (int j=0; j<PartVec.size();j++){
	Particle part = PartVec[j];
	cout<<part.GetPDG()<<endl;
	}*/
    
      float ECL = calorimetric(PartVecAboveLiquid);
      float ECL_diff = 0;
      if (ECL != 0){
	ECL_diff = ECL-Enu_t;
	float ECL_diff_frac = ECL_diff/Enu_t;
	hCL->Fill(ECL);
	hCL_diff->Fill(ECL_diff);
	hCL_diff_true->Fill(Enu_t,ECL_diff);
	hCL_diff_true_frac->Fill(Enu_t,ECL_diff_frac);
      }
      
      float ECG = calorimetric(PartVecAboveGas);
      float ECG_diff = 0;
      if (ECG != 0) {
	ECG_diff = ECG-Enu_t;
	float ECG_diff_frac = ECG_diff/Enu_t;
	hCG->Fill(ECG);
	hCG_diff->Fill(ECG_diff);
	hCG_diff_true->Fill(Enu_t,ECG_diff);
	hCG_diff_true_frac->Fill(Enu_t,ECG_diff_frac);
      }
      
      float EKL = kinematic(PartVecAboveLiquid,coslep);
      if (EKL != 0){
	float EKL_diff = EKL - Enu_t;
	float EKL_diff_frac = EKL_diff/Enu_t;
	hKL->Fill(EKL);
	hKL_diff->Fill(EKL_diff);
	hKL_diff_true->Fill(Enu_t,EKL_diff);
	hKL_diff_true_frac->Fill(Enu_t,EKL_diff_frac);
	if (ECL_diff != 0) hL_cal_kin_diff_true->Fill(ECL_diff, EKL_diff, Enu_t);
      }
            
      float EKG = kinematic(PartVecAboveGas,coslep);
      if (EKG != 0){
	float EKG_diff = EKG-Enu_t;
	float EKG_diff_frac = EKG_diff/Enu_t;
	hKG->Fill(EKG);
	hKG_diff->Fill(EKG_diff);
	hKG_diff_true->Fill(Enu_t,EKG_diff);
	hKG_diff_true_frac->Fill(Enu_t,EKG_diff_frac);
      }
      if (ECL != 0 && EKL != 0){
	float ECKL_diff = ECL - EKL;
	hCKL_diff->Fill(Enu_t,ECKL_diff);
	hL_cal_kin_true->Fill(ECL,EKL,Enu_t);
      }
      if (ECG != 0 && EKG != 0){
	float ECKG_diff = ECG - EKG;
	hCKG_diff->Fill(Enu_t,ECKG_diff);
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
  
  TCanvas *c8 = new TCanvas("c8", "3D - cal - kin - true");
  hL_cal_kin_diff_true->Draw();
  */
  return (0);
}
