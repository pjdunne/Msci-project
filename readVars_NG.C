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

int readVars_NG(){
  TFile* fileNEUT = new TFile("T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v4.root");
  TTree* tree = (TTree*)fileNEUT->Get("FlatTree_VARS");
  
  TFile* fileGENIE = new TFile("genie_argon_fnalsmall_run1_flat_v2.root");
  TTree* treeG = (TTree*)fileGENIE->Get("FlatTree_VARS");

  

  TH1D* h = new TH1D("h", "True  Energy plots", 1000, 0, 10);

  TH1D* N_Pmu = new TH1D("N_Pmu", "NEUT and GENIE lepton momentum magnitude (no threshold)", 1000, 0, 4);
  TH1D* G_Pmu = new TH1D("G_Pmu", "NEUT and GENIE lepton momentum magnitude (no threshold)", 1000, 0, 4);

  TH1D* N_PmuG = new TH1D("N_PmuG", "NEUT and GENIE lepton momentum magnitude (gas)", 1000, 0, 4);
  TH1D* G_PmuG = new TH1D("G_PmuG", "NEUT and GENIE lepton momentum magnitude (gas)", 1000, 0, 4);

  TH1D* N_PmuL= new TH1D("N_PmuL", "NEUT and GENIE lepton momentum magnitude (liquid)", 1000, 0, 4);
  TH1D* G_PmuL= new TH1D("G_PmuL", "NEUT and GENIE lepton momentum magnitude (liquid)", 1000, 0, 4);

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
			
		  if(pdg[i] == 13){
		  N_Pmu->Fill(Part.GetMomentum());}}	
		  
				
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 13){
		N_PmuL->Fill(P.GetMomentum());}}
	PartVecGas=gasMomThresh(PartRes);
	for (int i =0; i<PartVecGas.size(); i++){
		Particle Pa = PartVecGas[i];
		int pdgn= Pa.GetPDG();
		if(pdgn == 13){
		N_PmuG->Fill(Pa.GetMomentum());}}

	}}

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
		  if(pdgG[i] == 13){
        		G_Pmu->Fill(Part.GetMomentum());}}	
										
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 13){
		G_PmuL->Fill(P.GetMomentum());}}
	PartVecGas=gasMomThresh(PartRes);
	for (int j =0; j<PartVecGas.size(); j++){
		Particle Pa = PartVecGas[j];
		int pdgn= Pa.GetPDG();
		if(pdgn == 13){
		G_PmuG->Fill(Pa.GetMomentum());}}
	        
	}}





//muLep NEUT and GENIE liquid
  TCanvas *hN_Pmu = new TCanvas("hN_Pmu", "NEUT and GENIE lepton momentum magnitude comparison (no threshold)");
  N_Pmu->Draw();
  hN_Pmu->Update();
  G_Pmu->SetLineColor(kRed);
  G_Pmu->Draw("same");
  auto legend2 = new TLegend(0.3,0.7,0.5,0.9);
  legend2->AddEntry(N_Pmu,"NEUT","f");
  legend2->AddEntry(G_Pmu,"GENIE","f");
  legend2->Draw();

  TCanvas *hN_PmuG = new TCanvas("hN_PmuG", "NEUT and GENIE lepton momentum magnitude comparison (gas)");
  N_PmuG->Draw();
  hN_PmuG->Update();
  G_PmuG->SetLineColor(kRed);
  G_PmuG->Draw("same");
  auto legend = new TLegend(0.3,0.7,0.5,0.9);
  legend->AddEntry(N_PmuG,"NEUT","f");
  legend->AddEntry(G_PmuG,"GENIE","f");
  legend->Draw();

  TCanvas *hN_PmuL = new TCanvas("hN_PmuL", "NEUT and GENIE lepton momentum magnitude comparison (liquid)");
  N_PmuL->Draw();
  hN_PmuL->Update();
  G_PmuL->SetLineColor(kRed);
  G_PmuL->Draw("same");
  auto legend1 = new TLegend(0.3,0.7,0.5,0.9);
  legend1->AddEntry(N_PmuL,"NEUT","f");
  legend1->AddEntry(G_PmuL,"GENIE","f");
  legend1->Draw();


  return (0);}