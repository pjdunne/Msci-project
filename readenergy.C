#include "TRandom.h"
#include <ctime>
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
#include "Resolution.C"
#include "Identify.C"
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

  TH1D* hCL_diff = new TH1D("hCL_diff","Liquid TPC - Calorimetric difference", 100, -1, 1);
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

  TH1D* hCL_diff_frac = new TH1D("hCL_diff_frac","Liquid TPC - Fractional calorimetric difference",100,-0.8,0.2);
  hCL_diff_frac->GetXaxis()->SetTitle("(E_cal - E_true)/E_true");
  hCL_diff_frac->GetYaxis()->SetTitle("No. of events");
  
  TH1D* hCG = new TH1D("hCG","Gas TCP - Calorimetric ",100,-1,15);
  hCG->GetXaxis()->SetTitle("Energy (Gev)");
  hCG->GetYaxis()->SetTitle("Number of events");
  hCG->SetFillColor(kYellow-7);
  hCG->SetLineColor(kBlack);
  
  TH1D* hCG_diff = new TH1D("hCG_diff","Gas TPC - Calorimetric difference",100,-1,0.2);
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

  TH1D* hCG_diff_frac = new TH1D("hCG_diff_frac","Gas TPC - Fractional calorimetric difference",100,-0.8,0.2);
  hCG_diff_frac->GetXaxis()->SetTitle("(E_cal - E_true)/E_true");
  hCG_diff_frac->GetYaxis()->SetTitle("No. of events");

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

  TH2D* hKL_diff_true = new TH2D("hKL_diff_true","Liquid TPC - Kinematic difference as function of true energy",100,0,12,100,-5,10);
  hKL_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKL_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TH2D* hKL_diff_true_frac = new TH2D("hKL_diff_true_frac","Liquid TPC - Fractional kinematic difference as function of true energy",100,0,12,100,-1,5);
  hKL_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hKL_diff_true_frac->GetYaxis()->SetTitle("Fractional kinematic reconstructed energy difference");
  
  TH1D* hKL_diff_frac = new TH1D("hKL_diff_frac","Liquid TPC - Fractional kinematic difference",100,-0.6,1);
  hKL_diff_frac->GetXaxis()->SetTitle("(E_kin - E_true)/E_true");
  hKL_diff_frac->GetYaxis()->SetTitle("No. of events");

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

  TH2D* hKG_diff_true = new TH2D("hKG_diff_true","Gas TPC - Kinematic difference as function of true energy",100,0,12,100,-1,5);
  hKG_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TH2D* hKG_diff_true_frac = new TH2D("hKG_diff_true_frac","Gas TPC - Fractional kinematic difference as function of true energy",100,0,12,100,-1,5);
  hKG_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true_frac->GetYaxis()->SetTitle("Fractional kinematic reconstructed energy difference");

  TH1D* hKG_diff_frac = new TH1D("hKG_diff_frac","Gas TPC - Fractional kinematic difference",100,-0.6,1);
  hKG_diff_frac->GetXaxis()->SetTitle("(E_kin - E_true)/E_true");
  hKG_diff_frac->GetYaxis()->SetTitle("No. of events");
  
  TH2D* hCKL_diff = new TH2D("hCKL_diff","Liquid TPC - Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKL_diff->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKL_diff->GetYaxis()->SetTitle("E_cal - E_kin (GeV)");

  TH2D* hCKL_diff_frac = new TH2D("hCKL_diff_frac","Liquid TPC - Fractional Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKL_diff_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKL_diff_frac->GetYaxis()->SetTitle("(E_cal - E_kin)/E_true");

  TH2D* hCKG_diff = new TH2D("hCKG_diff","Gas TPC - Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKG_diff->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKG_diff->GetYaxis()->SetTitle("E_cal - E_kin (GeV)");
 
  TH2D* hCKG_diff_frac = new TH2D("hCKG_diff_frac","Gas TPC - Fractional Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKG_diff_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKG_diff_frac->GetYaxis()->SetTitle("(E_cal - E_kin)/E_true");
  
  TH3D* hL_cal_kin_true = new TH3D("hL_cal_kin_true","Liquid TPC - Calorimetric and kinematic as a function of true",100,-1,12,100,-1,12,100,0,12);
  hL_cal_kin_true->GetXaxis()->SetTitle("Calorimetirc Energy (GeV)");
  hL_cal_kin_true->GetYaxis()->SetTitle("Kinematic energy (GeV)");
  hL_cal_kin_true->GetZaxis()->SetTitle("True (GeV)");

  TH3D* hL_cal_kin_diff_true = new TH3D("hL_cal_kin_diff_true","Liquid TPC - Calorimetric and kinematic differences as a function of true",100,-0.8,0.1,100,-1,1.5,100,0,12);
  hL_cal_kin_diff_true->GetXaxis()->SetTitle("Calorimetirc Energy difference (GeV)");
  hL_cal_kin_diff_true->GetYaxis()->SetTitle("Kinematic energy difference (GeV)");
  hL_cal_kin_diff_true->GetZaxis()->SetTitle("True (GeV)");

  TH1D* hFrac_slice_0001 = new TH1D("hFrac_Slice_0001"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0102 = new TH1D("hFrac_Slice_0102"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0203 = new TH1D("hFrac_Slice_0203"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0304 = new TH1D("hFrac_Slice_0304"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0405 = new TH1D("hFrac_Slice_0405"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0506 = new TH1D("hFrac_Slice_0506"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0607 = new TH1D("hFrac_Slice_0607"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0708 = new TH1D("hFrac_Slice_0708"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0809 = new TH1D("hFrac_Slice_0809"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_0910 = new TH1D("hFrac_Slice_0910"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_1011 = new TH1D("hFrac_Slice_1011"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_1112 = new TH1D("hFrac_Slice_1112"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_1213 = new TH1D("hFrac_Slice_1213"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_1314 = new TH1D("hFrac_Slice_1314"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_1415 = new TH1D("hFrac_Slice_1415"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_1520 = new TH1D("hFrac_Slice_1520"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_2025 = new TH1D("hFrac_Slice_2025"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_2530 = new TH1D("hFrac_Slice_2530"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_3035 = new TH1D("hFrac_Slice_3035"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_3540 = new TH1D("hFrac_Slice_3540"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_4045 = new TH1D("hFrac_Slice_4045"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_4550 = new TH1D("hFrac_Slice_4550"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_5055 = new TH1D("hFrac_Slice_5055"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_5560 = new TH1D("hFrac_Slice_5560"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_6065 = new TH1D("hFrac_Slice_6065"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_6570 = new TH1D("hFrac_Slice_6570"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_7075 = new TH1D("hFrac_Slice_7075"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_7580 = new TH1D("hFrac_Slice_7580"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_8085 = new TH1D("hFrac_Slice_8085"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_8590 = new TH1D("hFrac_Slice_8590"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_9095 = new TH1D("hFrac_Slice_9095"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_95100 = new TH1D("hFrac_Slice_90100"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_100105 = new TH1D("hFrac_Slice_100105"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_105110 = new TH1D("hFrac_Slice_105110"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_110115 = new TH1D("hFrac_Slice_110115"," ",100,-0.8,0.2);
  TH1D* hFrac_slice_115120 = new TH1D("hFrac_Slice_115120"," ",100,-0.8,0.2);
  
  //TH1D* hFrac_slice = new TH1D("hFrac_slice","Slice of true energy - fractional plots",100,-0.8,0.5);
  //hFrac_slice->GetXaxis()->SetTitle("Fractional energy difference");
  //hFrac_slice->GetYaxis()->SetTitle("No. of events");

  TH2D* hcal_kin = new TH2D("hcal_kin"," ", 100,-5,10,100,-10,10);


  TH1D* hdiff = new TH1D("hdiff"," ",100,-5,5);
  
  TGaxis::SetMaxDigits(4);
  //gStyle->SetOptStat(0);     //Stats box

  vector<Particle> PartVecAboveLiquid;
  vector<Particle> PartVecAboveGas;
  vector<Particle> PartVec;
  vector<Particle> PartVecRes;

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
    PartVecRes.clear();
    
    for (int i = 0; i < nfsp; ++i)  {
	
	id++;    
	Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
	PartVec.push_back(Part);
      }
    
    vector<Particle> PartVec1;
    PartVec1 = PartVec;
    PartVec = resolution(PartVec,0.01); //1,2 or 5%

    //PartVecAboveLiquid = PartVec;
    //PartVecAboveGas = PartVec;
    
    PartVecAboveLiquid = liquidMomThresh(PartVec);
    PartVecAboveGas = gasMomThresh(PartVec);

    
    float ECL=0;
    float ECL_diff=0;
    float ECL_diff_frac=0;
    float EKL=0;
    float EKL_diff=0;
    float EKL_diff_frac=0;
    float ECKL_diff=0;
    float ECKL_diff_frac=0;
    float ECG=0;
    float ECG_diff=0;
    float ECG_diff_frac=0;
    float EKG=0;
    float EKG_diff=0;
    float EKG_diff_frac=0;
    float ECKG_diff=0;
    float ECKG_diff_frac=0;
    /////select mode/topology - liquid
    
    //if(mode==1){                                             //individual true modes
    if (id_0pi(PartVecAboveLiquid)==1){                      //0pi from detected particles 
    //if (id_1pi(PartVec) ==1){                                //1pi from detected particles
    //if (id_0pi(PartVec) == 0 && id_1pi(PartVec) == 0) {      //other
    
      float ECL = calorimetric(PartVecAboveLiquid);
      float ECL_diff=0;
      if (ECL != 0){
	ECL_diff = ECL-Enu_t;
	float ECL_diff_frac = ECL_diff/Enu_t;
	hCL->Fill(ECL);
	hCL_diff->Fill(ECL_diff);
	hCL_diff_true->Fill(Enu_t,ECL_diff);
	hCL_diff_true_frac->Fill(Enu_t,ECL_diff_frac);
	hCL_diff_frac->Fill(ECL_diff_frac);
	//if (Enu_t > 0.1 && Enu_t < 0.2) hFrac_slice->Fill(ECL_diff_frac);
	
	if (Enu_t < 0.1) hFrac_slice_0001->Fill(ECL_diff_frac);
	else if (Enu_t > 0.1 && Enu_t < 0.2) hFrac_slice_0102->Fill(ECL_diff_frac);
	else if (Enu_t > 0.2 && Enu_t < 0.3) hFrac_slice_0203->Fill(ECL_diff_frac);
	else if (Enu_t > 0.3 && Enu_t < 0.4) hFrac_slice_0304->Fill(ECL_diff_frac);
	else if (Enu_t > 0.4 && Enu_t < 0.5) hFrac_slice_0405->Fill(ECL_diff_frac);
	else if (Enu_t > 0.5 && Enu_t < 0.6) hFrac_slice_0506->Fill(ECL_diff_frac);
	else if (Enu_t > 0.6 && Enu_t < 0.7) hFrac_slice_0607->Fill(ECL_diff_frac);
	else if (Enu_t > 0.7 && Enu_t < 0.8) hFrac_slice_0708->Fill(ECL_diff_frac);
	else if (Enu_t > 0.8 && Enu_t < 0.9) hFrac_slice_0809->Fill(ECL_diff_frac);
	else if (Enu_t > 0.9 && Enu_t < 1.0) hFrac_slice_0910->Fill(ECL_diff_frac);
	else if (Enu_t > 1.0 && Enu_t < 1.1) hFrac_slice_1011->Fill(ECL_diff_frac);
	else if (Enu_t > 1.1 && Enu_t < 1.2) hFrac_slice_1112->Fill(ECL_diff_frac);
	else if (Enu_t > 1.2 && Enu_t < 1.3) hFrac_slice_1213->Fill(ECL_diff_frac);
	else if (Enu_t > 1.3 && Enu_t < 1.4) hFrac_slice_1314->Fill(ECL_diff_frac);
	else if (Enu_t > 1.4 && Enu_t < 1.5) hFrac_slice_1415->Fill(ECL_diff_frac);
	else if (Enu_t > 1.5 && Enu_t < 2.0) hFrac_slice_1520->Fill(ECL_diff_frac);
	else if (Enu_t > 2.0 && Enu_t < 2.5) hFrac_slice_2025->Fill(ECL_diff_frac);
	else if (Enu_t > 2.5 && Enu_t < 3.0) hFrac_slice_2530->Fill(ECL_diff_frac);
	else if (Enu_t > 3.0 && Enu_t < 3.5) hFrac_slice_3035->Fill(ECL_diff_frac);
	else if (Enu_t > 3.5 && Enu_t < 4.0) hFrac_slice_3540->Fill(ECL_diff_frac);
	else if (Enu_t > 4.0 && Enu_t < 4.5) hFrac_slice_4045->Fill(ECL_diff_frac);
	else if (Enu_t > 4.5 && Enu_t < 5.0) hFrac_slice_4550->Fill(ECL_diff_frac);
	else if (Enu_t > 5.0 && Enu_t < 5.5) hFrac_slice_5055->Fill(ECL_diff_frac);
	else if (Enu_t > 5.5 && Enu_t < 6.0) hFrac_slice_5560->Fill(ECL_diff_frac);
	else if (Enu_t > 6.0 && Enu_t < 6.5) hFrac_slice_6065->Fill(ECL_diff_frac);
	else if (Enu_t > 6.5 && Enu_t < 7.0) hFrac_slice_6570->Fill(ECL_diff_frac);
	else if (Enu_t > 7.0 && Enu_t < 7.5) hFrac_slice_7075->Fill(ECL_diff_frac);
	else if (Enu_t > 7.5 && Enu_t < 8.0) hFrac_slice_7580->Fill(ECL_diff_frac);
	else if (Enu_t > 8.0 && Enu_t < 8.5) hFrac_slice_8085->Fill(ECL_diff_frac);
	else if (Enu_t > 8.5 && Enu_t < 9.0) hFrac_slice_8590->Fill(ECL_diff_frac);
	else if (Enu_t > 9.0 && Enu_t < 9.5) hFrac_slice_9095->Fill(ECL_diff_frac);
	else if (Enu_t > 9.5 && Enu_t < 10.0) hFrac_slice_95100->Fill(ECL_diff_frac);
	else if (Enu_t > 10.0 && Enu_t < 10.5) hFrac_slice_100105->Fill(ECL_diff_frac);
	else if (Enu_t > 10.5 && Enu_t < 11.0) hFrac_slice_105110->Fill(ECL_diff_frac);
	else if (Enu_t > 11.0 && Enu_t < 11.5) hFrac_slice_110115->Fill(ECL_diff_frac);
	else hFrac_slice_115120->Fill(ECL_diff_frac);
      }
      
      
      EKL = kinematic(PartVecAboveLiquid,coslep);
      if (EKL != 0){
	EKL_diff = EKL - Enu_t;
	EKL_diff_frac = EKL_diff/Enu_t;
	hKL->Fill(EKL);
	hKL_diff->Fill(EKL_diff);
	hKL_diff_true->Fill(Enu_t,EKL_diff);
	hKL_diff_true_frac->Fill(Enu_t,EKL_diff_frac);
	hKL_diff_frac->Fill(EKL_diff_frac);
	if (ECL_diff != 0) {
	  hL_cal_kin_diff_true->Fill(ECL_diff, EKL_diff, Enu_t);
	  hcal_kin->Fill(ECL_diff,EKL_diff);
	}
      }
      
      if (ECL != 0 && EKL != 0){
	ECKL_diff = ECL - EKL;
	ECKL_diff_frac = ECKL_diff / Enu_t;
	hCKL_diff->Fill(Enu_t,ECKL_diff);
	hCKL_diff_frac->Fill(Enu_t,ECKL_diff_frac);
	hL_cal_kin_true->Fill(ECL,EKL,Enu_t);
      }
    }

    /////select mode/topology - gas
    
    //if(mode==1){                                             //individual true modes
    if (id_0pi(PartVecAboveGas)==1){                      //0pi from detected particles 
    //if (id_1pi(PartVecAboveGas) ==1){                                //1pi from detected particles
    //if (id_0pi(PartVecAboveGas) == 0 && id_1pi(PartVecAboveGas) == 0) {      //other

      ECG = calorimetric(PartVecAboveGas);
      if (ECG != 0) {
	ECG_diff = ECG-Enu_t;
	ECG_diff_frac = ECG_diff/Enu_t;
	hCG->Fill(ECG);
	hCG_diff->Fill(ECG_diff);
	hCG_diff_true->Fill(Enu_t,ECG_diff);
	hCG_diff_true_frac->Fill(Enu_t,ECG_diff_frac);
	hCG_diff_frac->Fill(ECG_diff_frac);
      }
	
      EKG = kinematic(PartVecAboveGas,coslep);
      if (EKG != 0){
	EKG_diff = EKG-Enu_t;
	EKG_diff_frac = EKG_diff/Enu_t;
	hKG->Fill(EKG);
	hKG_diff->Fill(EKG_diff);
	hKG_diff_true->Fill(Enu_t,EKG_diff);
	hKG_diff_true_frac->Fill(Enu_t,EKG_diff_frac);
	hKG_diff_frac->Fill(EKG_diff_frac);
      }
      	
      if (ECG != 0 && EKG != 0){
	ECKG_diff = ECG - EKG;
	ECKG_diff_frac = ECKG_diff / Enu_t;
	hCKG_diff->Fill(Enu_t,ECKG_diff);
	hCKG_diff_frac->Fill(Enu_t,ECKG_diff_frac);
      }
	
      hE->Fill(Enu_t);
    }    
  }
  /*
  hFrac_slice_0001->Fit("gaus");
  hFrac_slice_0102->Fit("gaus");
  hFrac_slice_0203->Fit("gaus");
  hFrac_slice_0304->Fit("gaus");
  hFrac_slice_0405->Fit("gaus");
  hFrac_slice_0506->Fit("gaus");
  hFrac_slice_0607->Fit("gaus");
  hFrac_slice_0708->Fit("gaus");
  hFrac_slice_0809->Fit("gaus");
  hFrac_slice_0910->Fit("gaus");
  hFrac_slice_1011->Fit("gaus");
  hFrac_slice_1112->Fit("gaus");
  hFrac_slice_1213->Fit("gaus");
  hFrac_slice_1314->Fit("gaus");
  hFrac_slice_1415->Fit("gaus");
  hFrac_slice_1520->Fit("gaus");
  hFrac_slice_2025->Fit("gaus");
  hFrac_slice_2530->Fit("gaus");
  hFrac_slice_3035->Fit("gaus");
  hFrac_slice_3540->Fit("gaus");
  hFrac_slice_4045->Fit("gaus");
  hFrac_slice_4550->Fit("gaus");
  hFrac_slice_5055->Fit("gaus");
  hFrac_slice_5560->Fit("gaus");
  hFrac_slice_6065->Fit("gaus");
  hFrac_slice_6570->Fit("gaus");
  hFrac_slice_7075->Fit("gaus");
  hFrac_slice_7580->Fit("gaus");
  hFrac_slice_8085->Fit("gaus");
  hFrac_slice_8590->Fit("gaus");
  hFrac_slice_9095->Fit("gaus");
  hFrac_slice_95100->Fit("gaus");
  hFrac_slice_100105->Fit("gaus");
  hFrac_slice_105110->Fit("gaus");
  hFrac_slice_110115->Fit("gaus");
  hFrac_slice_115120->Fit("gaus");
  */
  //plotting two 1D histograms on same canvas
  /*
  TCanvas *c1 = new TCanvas("c1","cal and kin energy difference",200,10,700,500);
  TPad *pad1 = new TPad("pad1","",0,0,1,1);
  TPad *pad2 = new TPad("pad2","",0,0,1,1);
  TPad *pad3 = new TPad("pad3","",0,0,1,1);

  pad2->SetFillStyle(4000);
  pad1->Draw();
  pad1->cd();
  
  hCL->Draw();
  pad1->Update();
  TPaveStats *ps1 = (TPaveStats*)hCL->GetListOfFunctions()->FindObject("stats");
  ps1->SetX1NDC(0.4);
  ps1->SetX2NDC(0.6);
  pad1->Modified();
  c1->cd();
  double ymin = 0;
  double ymax = 140000;
  double dy = (ymax-ymin)/0.8;
  double xmin = -1;
  double xmax = 10;
  double dx = (xmax-xmin)/0.8;
  pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
  pad2->Draw();
  pad2->cd();
      
  hKL->SetLineColor(kRed);
  hKL->Draw("][sames");
  pad2->Update();
  TPaveStats *ps2 = (TPaveStats*)hKL->GetListOfFunctions()->FindObject("stats");
  ps2->SetX1NDC(0.65);
  ps2->SetX2NDC(0.85);
  ps2->SetTextColor(kRed);
  */
  

  //Drawing out histograms on canvases - don't have to go into TBrowser
  
  TCanvas *c = new TCanvas("c", "Energy Plot");
  c->SetGrid();
  hCL_diff_true->Draw();
  /*
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
  
  TCanvas *c8 = new TCanvas("c8", "Call diff with and without protons");
  hCL_diff->Draw();
  */
  
  return (0);
}
