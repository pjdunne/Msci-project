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

int readHPr(){
  TFile* fileNEUT = new TFile("T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v4.root");
  TTree* tree = (TTree*)fileNEUT->Get("FlatTree_VARS");
  
  TFile* fileGENIE = new TFile("genie_argon_fnalsmall_run1_flat_v2.root");
  TTree* treeG = (TTree*)fileGENIE->Get("FlatTree_VARS");

  TH1D* N_HEpr= new TH1D("N_HEpr", "NEUT and GENIE highest proton energy (no threshold)", 100, .85, 2.5);
  TH1D* G_HEpr= new TH1D("G_HEpr", "NEUT and GENIE highest proton energy (no threshold))", 100, .85, 2.5);

  TH1D* N_HEprL= new TH1D("N_HEprL", "NEUT and GENIE highest proton energy (liquid)", 100, .85, 2.5);
  TH1D* G_HEprL= new TH1D("G_HEprL", "NEUT and GENIE highest proton energy (liquid)", 100, .85, 2.5);

  TH1D* N_HEprG= new TH1D("N_HEprG", "NEUT and GENIE highest proton energy (gas)", 100, .85, 2.5);
  TH1D* G_HEprG= new TH1D("G_HEprG", "NEUT and GENIE highest proton energy (gas)", 100, .85, 2.5);

 //hCL->SetFillColor(kYellow-7);
  //hKL->SetFillColor(kYellow-7);
 // hKL_diff->SetFillColor(kYellow-7);
 // hCL_diff->SetFillColor(kYellow-7);
  //hCG->SetFillColor(kYellow-7);
 // hCG_diff->SetFillColor(kYellow-7);
 // hKG_diff->SetFillColor(kYellow-7);
//  hKG->SetFillColor(kYellow-7);

   N_HEprL->GetXaxis()->SetTitle("Energy (Gev)");
   N_HEprG->GetXaxis()->SetTitle("Energy (Gev)");
   G_HEprL->GetXaxis()->SetTitle("Energy (Gev)");
   G_HEprG->GetXaxis()->SetTitle("Energy (Gev)");
  TGaxis::SetMaxDigits(4);

  vector<Particle> PartVecLiquid;
  vector<Particle> PartVecGas;
  vector<Particle> PartVec;
  vector<Particle> PartRes;
  vector<float> EPrVec;

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
	int nPr = 0;
        PartVec.clear();
	EPrVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	Threshold Thresh;
        Calorimetric Cal;
	Resolution Res;

        
	if (mode==11 | mode==12 | mode==13){
	for (int i = 0; i < nfsp; ++i)  {
			
	          int id = 0;
		  id++;
    
                  Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
		  PartVec.push_back(Part);
		  if(Part.GetPDG() == 2212){  
		  N_HEpr->Fill(Part.GetEnergy());}
			}	
		  			
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();

		if(pd == 2212){   
		EPrVec.push_back(P.GetEnergy());}
		}
	if (EPrVec.size()>0){
        N_HEprL->Fill(*max(EPrVec.begin(),EPrVec.end()));}  //highest energy proton liquid
        EPrVec.clear();

	PartVecGas=gasMomThresh(PartRes);
	for (int i =0; i<PartVecGas.size(); i++){
		Particle Pa = PartVecGas[i];
		int pdgn= Pa.GetPDG();
		if(pdgn == 2212){   //Pion energy gas
		EPrVec.push_back(Pa.GetEnergy());}
		}	
	if (EPrVec.size()>0){
	N_HEprG->Fill(*max(EPrVec.begin(),EPrVec.end()));} //highest proton energy gas
	}
	}

//Read GENIE
  Long64_t nentriesG= treeG->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentriesG;iEntry++){
	treeG->GetEntry(iEntry);
	int nPr = 0;
	EPrVec.clear();
        PartVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	Threshold Thresh;
        Calorimetric Cal;
	Resolution Res;

	        
        if (modeG==1){
	for (int i = 0; i < nfspG; ++i)  {
	          int id = 0;
		  id++;
                  Particle Part = Particle(pdgG[i], pxG[i], pyG[i],pzG[i], energyG[i], id);
		  PartVec.push_back(Part);
		  if(Part.GetPDG() == 2212){  
		  G_HEpr->Fill(Part.GetEnergy());}
		  }	
								
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 2212){   //Pion energy liquid
		EPrVec.push_back(P.GetEnergy());}
							//highest energy proton liquid
		}
	if (EPrVec.size()>0){
        G_HEprL->Fill(*max(EPrVec.begin(),EPrVec.end()));} //Highest E pion
	EPrVec.clear();

	PartVecGas=gasMomThresh(PartRes);
	for (int j =0; j<PartVecGas.size(); j++){
		Particle Pa = PartVecGas[j];
		int pdgn= Pa.GetPDG();
		if(pdgn == 2212){   //Pion energy gas
		EPrVec.push_back(Pa.GetEnergy());
		}
		}
	if (EPrVec.size()>0){
	G_HEprG->Fill(*max(EPrVec.begin(),EPrVec.end()));} 
	}
	}


double chi_squared_total=0;

for (int i = 0; i < N_HEprL->GetXaxis()->GetNbins()+1; ++i) {
    // N_Pmu is here the MC pmu distribution from NEUT
    double mc_content = N_HEprL->GetBinContent(i+1);

    // N_Pmu is here_data is the MC pmu distribution from GENIE
    double data_content = G_HEprL->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}


  TCanvas *h_HEprL = new TCanvas("h_HEprL", "NEUT and GENIE pion energy comparison (liquid)");
  N_HEprL->Draw();
  h_HEprL->Update();
  G_HEprL->SetLineColor(kRed);
  G_HEprL->Draw("same");
  auto legend7 = new TLegend(0.3,0.7,0.5,0.9);
  legend7->AddEntry(N_HEprL,"NEUT","f");
  legend7->AddEntry(G_HEprL,"GENIE","f");
  legend7->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend7->Draw();
//
//NEW GRAPH________________________________________________________________
chi_squared_total=0;

for (int i = 0; i < N_HEprG->GetXaxis()->GetNbins()+1; ++i) {
    double mc_content = N_HEprG->GetBinContent(i+1);
    double data_content = G_HEprG->GetBinContent(i+1);
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}
  TCanvas *h_HEprG = new TCanvas("h_HEprG", "NEUT and GENIE pion energy comparison (gas)");
  N_HEprG->Draw();
  h_HEprG->Update();
  G_HEprG->SetLineColor(kRed);
  G_HEprG->Draw("same");
  auto legend6 = new TLegend(0.3,0.7,0.5,0.9);
  legend6->AddEntry(N_HEprG,"NEUT","f");
  legend6->AddEntry(G_HEprG,"GENIE","f");
  legend6->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend6->Draw();


//NEW GRAPH________________________________________________________________
chi_squared_total=0;

for (int i = 0; i < N_HEpr->GetXaxis()->GetNbins()+1; ++i) {
    double mc_content = N_HEpr->GetBinContent(i+1);
    double data_content = G_HEpr->GetBinContent(i+1);
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}
  TCanvas *h_HEpr = new TCanvas("h_HEpr", "NEUT and GENIE pion energy comparison (no threshold)");
  N_HEpr->Draw();
  h_HEpr->Update();
  G_HEpr->SetLineColor(kRed);
  G_HEpr->Draw("same");
  auto legend = new TLegend(0.3,0.7,0.5,0.9);
  legend->AddEntry(N_HEpr,"NEUT","f");
  legend->AddEntry(G_HEpr,"GENIE","f");
  legend->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend->Draw();

  return (0);}