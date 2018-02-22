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
#include "Linkdef.h"


int readenergy(){
  TFile* file = new TFile("/home/hep/al3614/neutrinoproject/T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v3.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");
  TH1D* hE = new TH1D("hE", "Energy plot", 100, 0, 10);
  TH1D* hC = new TH1D("hE", "Calorimetric Energy", 100, 0, 10);

 
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
  vector<float> Ecal;
  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);
  //tree->SetBranchAddress("",&Enu_t);  Edit when new tree given
 // tree->SetBranchAddress("CosLep",&coslep);
  

  
  Long64_t nentries = tree->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
	tree->GetEntry(iEntry);
        PartVec.clear();
        PartVecAbove.clear();
	Threshold Thresh;
        Calorimetric Cal;
	for (int i = 0; i < nfsp; ++i)  {
			
	          int id = 0;
		  id++;
              
                  Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);

		  PartVec.push_back(Part);}
        PartVecAbove=Thresh.ThreshFunc(PartVec);
		  for (unsigned int j=0; j<PartVecAbove.size(); ++j){
		        Particle Partic = PartVecAbove[j];
			//if (Partic.GetPDG()==14){
			float Energy=Partic.GetEnergy();
			hE->Fill(Energy);}
         float Ec = Cal.CalFunc(PartVecAbove);
         Ecal.push_back(Ec);
         hC->Fill(Ec);					  

	}


  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
  
  TCanvas *c1 = new TCanvas("c1", "Calorimetric Plot");
  hC->Draw();
  return (0);}