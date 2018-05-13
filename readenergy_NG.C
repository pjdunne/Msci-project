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
#include "TLegend.h"
#include "Particle.C"
#include "Threshold.C"
#include "Calorimetric.C"
#include "Kinematic.C"
#include "Resolution.C"
#include "Linkdef.h"
#include "TAxis.h"
#include "TGaxis.h"

int readenergy_NG(){
  TFile* fileNEUT = new TFile("T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v4.root");
  TTree* tree = (TTree*)fileNEUT->Get("FlatTree_VARS");
  
  TFile* fileGENIE = new TFile("genie_argon_fnalsmall_MecwithNC_proc_flat.root");
  TTree* treeG = (TTree*)fileGENIE->Get("FlatTree_VARS");

  

  TH1D* h = new TH1D("h", "True  Energy plots", 100, 0, 10);

  TH1D* N_PLep = new TH1D("N_Plep", "NEUT and GENIE lepton momentum magnitude", 1000, 0, 4);
  TH1D* G_PLep = new TH1D("G_PLep", "NEUT and GENIE lepton momentum magnitude", 1000, 0, 4);


  TH1D* hNKL = new TH1D("hNKL", "Kinematic NEUT and GENIE comparison (liquid)", 1000, -2, 10);
  TH1D* hNKG = new TH1D("hNKG", "Kinematic NEUT and GENIE comparison (gas)", 1000, -2, 10);
  TH1D* hNKL_diff = new TH1D("hNKL_diff", "Kinematic NEUT and GENIE difference (liquid)", 1000, -2, 2);
  TH1D* hNKG_diff = new TH1D("hNKG_diff", "Kinematic NEUT and GENIE difference (gas)", 1000, -2, 2);

  TH1D* hGKL = new TH1D("hGKL", "Kinematic NEUT and GENIE comparison (liquid)", 1000, -2, 10);
  TH1D* hGKG = new TH1D("hGKG", "Kinematic NEUT and GENIE comparison (gas)", 1000, -2, 10);
  TH1D* hGKL_diff = new TH1D("hGKL_diff", "Kinematic NEUT and GENIE difference (liquid)", 1000, -2, 2);
  TH1D* hGKG_diff = new TH1D("hGKG_diff", "Kinematic NEUT and GENIE difference (gas)", 1000, -2, 2);

  TH1D* hNCL = new TH1D("hNKL", "Calorimetric NEUT and GENIE comparison (liquid)", 1000, -2, 10);
  TH1D* hNCG = new TH1D("hNKG", "Calorimetric NEUT and GENIE comparison (gas)", 1000, -2, 10);
  TH1D* hNCL_diff = new TH1D("hNKL_diff", "Calorimetric NEUT and GENIE difference (liquid)", 1000, -2, 2);
  TH1D* hNCG_diff = new TH1D("hNKG_diff", "Calorimetric NEUT and GENIE difference (gas)", 1000, -2, 2);

  TH1D* hGCL = new TH1D("hGKL", "Calorimetric NEUT and GENIE comparison (liquid)", 1000, -2, 10);
  TH1D* hGCG = new TH1D("hGKG", "Calorimetric NEUT and GENIE comparison (gas)", 1000, -2, 10);
  TH1D* hGCL_diff = new TH1D("hGKL_diff", "Calorimetric NEUT and GENIE difference (liquid)", 1000, -2, 2);
  TH1D* hGCG_diff = new TH1D("hGKG_diff", "Calorimetric NEUT and GENIE difference (gas)", 1000, -2, 2);
  

 //hCL->SetFillColor(kYellow-7);
  //hKL->SetFillColor(kYellow-7);
 // hKL_diff->SetFillColor(kYellow-7);
 // hCL_diff->SetFillColor(kYellow-7);
  //hCG->SetFillColor(kYellow-7);
 // hCG_diff->SetFillColor(kYellow-7);
 // hKG_diff->SetFillColor(kYellow-7);
//  hKG->SetFillColor(kYellow-7);
  TGaxis::SetMaxDigits(4);

  vector<Particle> PartVecLiquid;
  vector<Particle> PartVecGas;
  vector<Particle> PartVec;
  vector<Particle> PartRes;
  vector<float> EVec;

  //Variables from NEUT tree
  int nfsp;                
  float coslep;
  int pdg[240];
  float px[240];
  float py[240];
  float pz[240];
  float energy[240];
  float Enu_t;
  int mode;
 

  //Variables from GENIE tree
  int nfspG;                
  float coslepG;
  int pdgG[240];
  float pxG[240];
  float pyG[240];
  float pzG[240];
  float energyG[240];
  float Enu_tG;
  int modeG;


  //NEUT
  tree->SetBranchAddress("Enu_true",&Enu_t);
  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);
  tree->SetBranchAddress("CosLep",&coslep);

  //GENIE
  treeG->SetBranchAddress("Enu_true",&Enu_tG);
  treeG->SetBranchAddress("nfsp",&nfspG);
  treeG->SetBranchAddress("pdg",&pdgG);
  treeG->SetBranchAddress("px",&pxG);
  treeG->SetBranchAddress("py",&pyG);
  treeG->SetBranchAddress("pz",&pzG);
  treeG->SetBranchAddress("E",&energyG);
  treeG->SetBranchAddress("Mode",&modeG);
  treeG->SetBranchAddress("CosLep",&coslepG);
 
//Read NEUT
  Long64_t nentries = tree->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
	tree->GetEntry(iEntry);
	
        PartVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	Threshold Thresh;
        Calorimetric Cal;
	Resolution Res;

        h->Fill(Enu_t);
        
	if (mode==1){
	for (int i = 0; i < nfsp; ++i)  {
			
	          int id = 0;
		  id++;
              
                  Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
		  PartVec.push_back(Part);
			
		  if(pdg[i] == 11  | pdg[i] == 13 | pdg[i] == 12 | pdg[i] == 14){
		  N_PLep->Fill(Part.GetMomentum());}}	
		  
				
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	PartVecGas=gasMomThresh(PartRes);
	

   	
   	float EKL = kinematic(PartVecLiquid,coslep);
	if(EKL != 0.123){
   	float EKL_diff = EKL - Enu_t;
   	 
	hNKL->Fill(EKL);	
	hNKL_diff->Fill(EKL_diff);
	}
	
   	float EKG = kinematic(PartVecGas,coslep);
	if(EKG != 0.123){
   	float EKG_diff = EKG-Enu_t;

	hNKG->Fill(EKG);	
	hNKG_diff->Fill(EKG_diff);
	}
	 float ECL = Cal.CalFunc(PartVecLiquid);
   	 float ECL_diff = ECL-Enu_t;

	 hNCL->Fill(ECL);
	 hNCL_diff->Fill(ECL_diff);


   	 float ECG = Cal.CalFunc(PartVecGas);
   	 float ECG_diff = ECG-Enu_t;
	 hNCG->Fill(ECG);
	 hNCG_diff->Fill(ECG_diff);
					}
        
	}

//Read GENIE
  Long64_t nentriesG= treeG->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentriesG;iEntry++){
	treeG->GetEntry(iEntry);
	
        PartVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	Threshold Thresh;
        Calorimetric Cal;
	Resolution Res;

        //h->Fill(Enu_tG);
	        
        if (modeG==1){
	for (int i = 0; i < nfspG; ++i)  {
			
	          int id = 0;
		  id++;
              
                  Particle Part = Particle(pdgG[i], pxG[i], pyG[i],pzG[i], energyG[i], id);
		  PartVec.push_back(Part);
		  if(pdgG[i] == 11  | pdgG[i] == 13 | pdgG[i] == 12 | pdgG[i] == 14){
        		G_PLep->Fill(Part.GetMomentum());}	
					
					}
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	PartVecGas=gasMomThresh(PartRes);
	

   	
   	float EKL = kinematic(PartVecLiquid,coslep);

	if(EKL != 0.123){
   	float EKL_diff = EKL - Enu_tG;
   	 
	hGKL->Fill(EKL);	
	hGKL_diff->Fill(EKL_diff);
	}
	
   	float EKG = kinematic(PartVecGas,coslep);
	if(EKG != 0.123){
   	float EKG_diff = EKG-Enu_tG;
	hGKG->Fill(EKG);	
	hGKG_diff->Fill(EKG_diff);
	}
	 float ECL = Cal.CalFunc(PartVecLiquid);
   	 float ECL_diff = ECL-Enu_tG;

	 hGCL->Fill(ECL);
	 hGCL_diff->Fill(ECL_diff);


   	 float ECG = Cal.CalFunc(PartVecGas);
   	 float ECG_diff = ECG-Enu_tG;
	 hGCG->Fill(ECG);
	 hGCG_diff->Fill(ECG_diff);}
         
	}


//NEUT and GENIE Kin and Cal comparison


  TCanvas *NGKinL = new TCanvas("NGKinL", "NEUT and GENIE Kinematic energy comparison (in liquid)");
  hNKL->Draw();
  NGKinL->Update();
  hGKL->SetLineColor(kRed);
  hGKL->Draw("same");
  auto legend1 = new TLegend(0.2,0.7,0.4,0.9);
  legend1->AddEntry(hNKL,"NEUT","f");
  legend1->AddEntry(hGKL,"GENIE","f");
  legend1->Draw();


  TCanvas *NGKinG = new TCanvas("NGKinG", "NEUT and GENIE Kinematic energy comparison (gas)");
  hNKG->Draw();
  NGKinG->Update();
  hGKG->SetLineColor(kRed);
  hGKG->Draw("same");
  auto legend5 = new TLegend(0.2,0.7,0.4,0.9);
  legend5->AddEntry(hNKG,"NEUT","f");
  legend5->AddEntry(hGKG,"GENIE","f");
  legend5->Draw();

  TCanvas *NGKin2 = new TCanvas("NGKin2", "NEUT and GENIE Kinematic energy difference (in liquid)");
  hNKL_diff->Draw();
  NGKin2->Update();
  hGKL_diff->SetLineColor(kRed);
  hGKL_diff->Draw("same");
  auto legend3 = new TLegend(0.2,0.7,0.4,0.9);
  legend3->AddEntry(hNKL_diff,"NEUT","f");
  legend3->AddEntry(hGKL_diff,"GENIE","f");
  legend3->Draw();


  TCanvas *NGKinGD = new TCanvas("NGKinGD", "NEUT and GENIE Kinematic energy difference (in liquid)");
  hNKG_diff->Draw();
  NGKinGD->Update();
  hGKG_diff->SetLineColor(kRed);
  hGKG_diff->Draw("same");
  auto legend7 = new TLegend(0.2,0.7,0.4,0.9);
  legend7->AddEntry(hNKG_diff,"NEUT","f");
  legend7->AddEntry(hGKG_diff,"GENIE","f");
  legend7->Draw();



  TCanvas *NGCal = new TCanvas("NGCal", "NEUT and GENIE Calorimetric energy comparison (gas)");
  hNCG->Draw();
  NGCal->Update();
  hGCG->SetLineColor(kRed);
  hGCG->Draw("same");
  auto legend = new TLegend(0.2,0.7,0.4,0.9);
  legend->AddEntry(hNCG,"NEUT","f");
  legend->AddEntry(hGCG,"GENIE","f");
  legend->Draw();

  TCanvas *NG2 = new TCanvas("NG2", "NEUT and GENIE Calorimetric energy difference comparison (gas)");
  hNCG_diff->Draw();
  NG2->Update();
  hGCG_diff->SetLineColor(kRed);
  hGCG_diff->Draw("same");
  auto legend2 = new TLegend(0.2,0.7,0.4,0.9);
  legend2->AddEntry(hNCG_diff,"NEUT","f");
  legend2->AddEntry(hGCG_diff,"GENIE","f");
  legend2->Draw();



  return (0);}
