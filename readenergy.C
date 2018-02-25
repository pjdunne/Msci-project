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
#include "Resolution.C"
#include "Linkdef.h"


int readenergy(){
  TFile* file = new TFile("T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v4.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");


  TH1D* hE = new TH1D("hE", "Energy plot", 100, 0, 10);
  TH1D* h = new TH1D("h", "True and Calorimetric Energy plots", 100, 0, 10);
  TH1D* hC = new TH1D("hC", "Calorimetric Energy", 100, 0, 10);
  TH1D* hC2 = new TH1D("hC2", "Calorimetric Energy", 100, 0, 10);
  TH1D* hD = new TH1D("hD", "Calorimetric Difference Plot", 100, -5, 5);
   TH1D* hD2 = new TH1D("hD2", "Calorimetric Difference Plot", 100, -5, 5);

 
  vector<Particle> PartVecAbove;
  vector<Particle> PartVecAbove2;
  vector<Particle> PartVec;
  vector<Particle> PartDet;
  vector<float> EVec;

  //Variables from tree
  int nfsp;                //number of final state particles
  int pdg[240];
  float px[240];
  float py[240];
  float pz[240];
  float energy[240];
  float Enut;
  int mode;
  vector<float> Ecal;

  tree->SetBranchAddress("Enu_true",&Enut);

  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);

  

  
  Long64_t nentries = tree->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
	tree->GetEntry(iEntry);
        PartVec.clear();
        PartVecAbove.clear();

	Threshold Thresh;
        Calorimetric Cal;
	Resolution Res;
        h->Fill(Enut);
        
	for (int i = 0; i < nfsp; ++i)  {
			
	          int id = 0;
		  id++;
              
                  Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);

		  PartVec.push_back(Part);}
        
        PartVecAbove=Thresh.ThreshFunc(PartVec, 0.058);
	PartVecAbove2=Thresh.ThreshFunc(PartVec, 0.058);
	PartDet=Res.ResFunc(PartVec,.05);
		  for (unsigned int j=0; j<PartVecAbove.size(); ++j){
		        Particle Partic = PartVecAbove[j];
			//if (Partic.GetPDG()==14){
			float Energy=Partic.GetEnergy();
			hE->Fill(Energy);}
	
         float Ec = Cal.CalFunc(PartVecAbove2);
	 float Ec2 = Cal.CalFunc(PartDet);
         Ecal.push_back(Ec);
	 float Diff = Ec-Enut; 
         float Diff2 = Ec2-Enut; 
         hD->Fill(Diff);
         hD2->Fill(Diff2);
         hC->Fill(Ec);					  
         hC2->Fill(Ec2);
	}

	

   

  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
  
  TCanvas *c1 = new TCanvas("c1", "Calorimetric Energy Plots");
  hC->Draw();
  c1->Update();
 // TCanvas *c2 = new TCanvas("c2", "Calorimetric Plot");
  hC2->SetLineColor(kRed);

  hC2->Draw("same");

  TCanvas *c3 = new TCanvas("c3", "Difference between true and calorimetric energies");
  hD->Draw();
  c3->Update();
  hD2->SetLineColor(kRed);
  hD2->Draw("same");
  return (0);}