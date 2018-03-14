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

  TH1D* N_Pmu = new TH1D("N_Pmu", "NEUT and GENIE muon momentum magnitude (no threshold)", 100, 0, 4);
  TH1D* G_Pmu = new TH1D("G_Pmu", "NEUT and GENIE muon momentum magnitude (no threshold)", 100, 0, 4);

  TH1D* nPrG = new TH1D("nPrG", "NEUT and GENIE proton number (no threshold)", 1000, 0, 10);
  TH1D* nPrN = new TH1D("nPrN", "NEUT and GENIE proton number (no threshold)", 1000, 0, 10);

  TH1D* nPrG_L = new TH1D("nPrG_L", "NEUT and GENIE proton number (liquid)", 1000, 0, 10);
  TH1D* nPrG_G = new TH1D("nPrG_G", "NEUT and GENIE proton number (gas)", 1000, 0, 10);

  TH1D* nPrN_L = new TH1D("nPrN_L", "NEUT and GENIE proton number (liquid)", 1000, 0, 10);
  TH1D* nPrN_G = new TH1D("nPrN_G", "NEUT and GENIE proton number (gas)", 1000, 0, 10);

  TH1D* N_PmuG = new TH1D("N_PmuG", "NEUT and GENIE muon momentum magnitude (gas)", 100, 0, 4);
  TH1D* G_PmuG = new TH1D("G_PmuG", "NEUT and GENIE muon momentum magnitude (gas)", 100, 0, 4);

  TH1D* N_PmuL= new TH1D("N_PmuL", "NEUT and GENIE muon momentum magnitude (liquid)", 100, 0, 4);
  TH1D* G_PmuL= new TH1D("G_PmuL", "NEUT and GENIE muon momentum magnitude (liquid)", 100, 0, 4);

  TH1D* N_EpiL= new TH1D("N_EpiL", "NEUT and GENIE pion energy (liquid)", 100, 0, 4);
  TH1D* G_EpiL= new TH1D("G_EpiL", "NEUT and GENIE pion energy (liquid)", 100, 0, 4);
  TH1D* N_HEpiL= new TH1D("N_HEpiL", "NEUT and GENIE highest pion energy (liquid)", 100, 0, 4);
  TH1D* G_HEpiL= new TH1D("G_HEpiL", "NEUT and GENIE highest pion energy (liquid)", 100, 0, 4);


  TH1D* N_EpiG= new TH1D("N_EpiG", "NEUT and GENIE pion energy (gas)", 100, 0, 4);
  TH1D* G_EpiG= new TH1D("G_EpiG", "NEUT and GENIE pion energy (gas)", 100, 0, 4);
  TH1D* N_HEpiG= new TH1D("N_HEpiG", "NEUT and GENIE highest pion energy (gas)", 100, 0, 4);
  TH1D* G_HEpiG= new TH1D("G_HEpiG", "NEUT and GENIE highest pion energy (gas)", 100, 0, 4);

 //hCL->SetFillColor(kYellow-7);
  //hKL->SetFillColor(kYellow-7);
 // hKL_diff->SetFillColor(kYellow-7);
 // hCL_diff->SetFillColor(kYellow-7);
  //hCG->SetFillColor(kYellow-7);
 // hCG_diff->SetFillColor(kYellow-7);
 // hKG_diff->SetFillColor(kYellow-7);
//  hKG->SetFillColor(kYellow-7);

   N_EpiL->GetXaxis()->SetTitle("Energy (Gev)");
   N_EpiG->GetXaxis()->SetTitle("Energy (Gev)");
   G_EpiL->GetXaxis()->SetTitle("Energy (Gev)");
   G_EpiG->GetXaxis()->SetTitle("Energy (Gev)");
  TGaxis::SetMaxDigits(4);

  vector<Particle> PartVecLiquid;
  vector<Particle> PartVecGas;
  vector<Particle> PartVec;
  vector<Particle> PartRes;
  vector<float> EPiVec;

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
	EPiVec.clear();
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
		  if(pdg[i]==2212){                    //Proton Number
		 	nPr++;}

		  if(pdg[i] == 13){                   //Muon Momentum
		  N_Pmu->Fill(Part.GetMomentum());}}	
		  
	nPrN->Fill(nPr);
	nPr=0;			
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 13){
		N_PmuL->Fill(P.GetMomentum());} //Muon momentum liquid
		
		if(pd==2212){nPr++;}
		

		if(pd == 111 | pd == 211 | pd == -211){   //Pion energy liquid
		N_EpiL->Fill(P.GetEnergy());
		EPiVec.push_back(P.GetEnergy());}
		}
	if (EPiVec.size()>0){
        N_HEpiL->Fill(*max(EPiVec.begin(),EPiVec.end()));}  //highest energy pion liquid
        nPrN_L->Fill(nPr);
        EPiVec.clear();
	nPr=0;
	PartVecGas=gasMomThresh(PartRes);
	for (int i =0; i<PartVecGas.size(); i++){
		Particle Pa = PartVecGas[i];
		int pdgn= Pa.GetPDG();
		if(pdgn == 13){          
		N_PmuG->Fill(Pa.GetMomentum());}

		if(pdgn==2212){nPr++;}                             //Proton number
			

		if(pdgn == 111 | pdgn == 211 | pdgn == -211){   //Pion energy gas
		N_EpiG->Fill(Pa.GetEnergy());
		EPiVec.push_back(Pa.GetEnergy());}
		}	
	nPrN_G->Fill(nPr);
	if (EPiVec.size()>0){
	N_HEpiG->Fill(*max(EPiVec.begin(),EPiVec.end()));} //highest pion energy gas
	}
	}

//Read GENIE
  Long64_t nentriesG= treeG->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentriesG;iEntry++){
	treeG->GetEntry(iEntry);
	int nPr = 0;
	EPiVec.clear();
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
		  if(pdgG[i]==2212){
		 	nPr++;}
		  if(pdgG[i] == 13){
        		G_Pmu->Fill(Part.GetMomentum());}}	
	nPrG->Fill(nPr);
	nPr=0;										
        PartRes=Res.ResFunc(PartVec,.05);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 13){
		G_PmuL->Fill(P.GetMomentum());}
		if(pd==2212){nPr++;}
		if(pd == 111 | pd == 211 | pd == -211){   //Pion energy liquid
		G_EpiL->Fill(P.GetEnergy());
		EPiVec.push_back(P.GetEnergy());}
		//highest energy pion liquid
		}
	if (EPiVec.size()>0){
        G_HEpiL->Fill(*max(EPiVec.begin(),EPiVec.end()));} //Highest E pion
	EPiVec.clear();
	nPrG_L->Fill(nPr);
	nPr=0;
	PartVecGas=gasMomThresh(PartRes);
	for (int j =0; j<PartVecGas.size(); j++){
		Particle Pa = PartVecGas[j];
		int pdgn= Pa.GetPDG();
		if(pdgn == 13){
		G_PmuG->Fill(Pa.GetMomentum());}
		if(pdgn==2212){nPr++;}
		if(pdgn == 111 | pdgn == 211 | pdgn == -211){   //Pion energy gas
		EPiVec.push_back(Pa.GetEnergy());
		G_EpiG->Fill(Pa.GetEnergy());}
		}
	if (EPiVec.size()>0){
	G_HEpiG->Fill(*max(EPiVec.begin(),EPiVec.end()));} 
	nPrG_G->Fill(nPr);      
	}}

//NEW GRAPH________________________________________________________________
double chi_squared_total=0;
for (int i = 0; i < N_Pmu->GetXaxis()->GetNbins()+1; ++i) {
    // N_Pmu is here the MC proton multiplicity distribution from NEUT
    double mc_content = N_Pmu->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = G_Pmu->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}
//muLep NEUT and GENIE liquid
  TCanvas *hN_Pmu = new TCanvas("hN_Pmu", "NEUT and GENIE muon momentum magnitude comparison (no threshold)");
  N_Pmu->Draw();
  hN_Pmu->Update();
  G_Pmu->SetLineColor(kRed);
  G_Pmu->Draw("same");
  auto legend2 = new TLegend(0.3,0.7,0.5,0.9);
  legend2->AddEntry(N_Pmu,"NEUT","f");
  legend2->AddEntry(G_Pmu,"GENIE","f");
  legend2->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend2->Draw();

//NEW GRAPH________________________________________________________________
chi_squared_total=0;
for (int i = 0; i < N_PmuG->GetXaxis()->GetNbins()+1; ++i) {
    // N_PmuG is here the MC proton multiplicity distribution from NEUT
    double mc_content = N_PmuG->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = G_PmuG->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}

  TCanvas *hN_PmuG = new TCanvas("hN_PmuG", "NEUT and GENIE muon momentum magnitude comparison (gas)");
  N_PmuG->Draw();
  hN_PmuG->Update();
  G_PmuG->SetLineColor(kRed);
  G_PmuG->Draw("same");
  auto legend = new TLegend(0.3,0.7,0.5,0.9);
  legend->AddEntry(N_PmuG,"NEUT","f");
  legend->AddEntry(G_PmuG,"GENIE","f");
  legend->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend->Draw();


//NEW GRAPH________________________________________________________________
chi_squared_total=0;
for (int i = 0; i < N_PmuL->GetXaxis()->GetNbins()+1; ++i) {
    // N_PmuL is here the MC proton multiplicity distribution from NEUT
    double mc_content = N_PmuL->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = G_PmuL->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}

  TCanvas *hN_PmuL = new TCanvas("hN_PmuL", "NEUT and GENIE muon momentum magnitude comparison (liquid)");
  N_PmuL->Draw();
  hN_PmuL->Update();
  G_PmuL->SetLineColor(kRed);
  G_PmuL->Draw("same");
  auto legend1 = new TLegend(0.3,0.7,0.5,0.9);
  legend1->AddEntry(N_PmuL,"NEUT","f");
  legend1->AddEntry(G_PmuL,"GENIE","f");
  legend1->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend1->Draw();

//NEW GRAPH________________________________________________________________
chi_squared_total=0;
for (int i = 0; i < nPrN_L->GetXaxis()->GetNbins()+1; ++i) {
    // N_PmuL is here the MC proton multiplicity distribution from NEUT
    double mc_content = nPrN_L->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = nPrG_L->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}

  TCanvas *hnPr_L = new TCanvas("hnPr_L", "NEUT and GENIE proton number comparison (liquid)");
  nPrN_L->Draw();
  hnPr_L->Update();
  nPrG_L->SetLineColor(kRed);
  nPrG_L->Draw("same");
  auto legend8 = new TLegend(0.3,0.7,0.5,0.9);
  legend8->AddEntry(nPrN_L,"NEUT","f");
  legend8->AddEntry(nPrG_L,"GENIE","f");
  legend8->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend8->Draw();

//NEW GRAPH________________________________________________________________
chi_squared_total=0;
for (int i = 0; i < nPrN_G->GetXaxis()->GetNbins()+1; ++i) {
    // N_PmuL is here the MC proton multiplicity distribution from NEUT
    double mc_content = nPrN_G->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = nPrG_G->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}

  TCanvas *hnPr_G = new TCanvas("hnPr_G", "NEUT and GENIE proton number comparison (gas)");
  nPrN_G->Draw();
  hnPr_G->Update();
  nPrG_G->SetLineColor(kRed);
  nPrG_G->Draw("same");
  auto legend9 = new TLegend(0.3,0.7,0.5,0.9);
  legend9->AddEntry(nPrN_G,"NEUT","f");
  legend9->AddEntry(nPrG_G,"GENIE","f");
  legend9->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend9->Draw();


//NEW GRAPH________________________________________________________________
chi_squared_total=0;

for (int i = 0; i < nPrN->GetXaxis()->GetNbins()+1; ++i) {
    // nPrN is here the MC proton multiplicity distribution from NEUT
    double mc_content = nPrN->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = nPrG->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}
  TCanvas *hnPr = new TCanvas("hnPr", "NEUT and GENIE proton number comparison (no threshold)");
  nPrN->Draw();
  hnPr->Update();
  nPrG->SetLineColor(kRed);
  nPrG->Draw("same");
  auto legend3 = new TLegend(0.3,0.7,0.5,0.9);
  legend3->AddEntry(nPrN,"NEUT","f");
  legend3->AddEntry(nPrG,"GENIE","f");
  legend3->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend3->Draw();

// NEW GRAPH_______________________________________________________________
chi_squared_total=0;

for (int i = 0; i < N_EpiL->GetXaxis()->GetNbins()+1; ++i) {
    // N_Pmu is here the MC pmu distribution from NEUT
    double mc_content = N_EpiL->GetBinContent(i+1);

    // N_Pmu is here_data is the MC pmu distribution from GENIE
    double data_content = G_EpiL->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}


  TCanvas *h_EpiL = new TCanvas("h_EpiL", "NEUT and GENIE pion energy comparison (liquid)");
  N_EpiL->Draw();
  h_EpiL->Update();
  G_EpiL->SetLineColor(kRed);
  G_EpiL->Draw("same");
  auto legend4 = new TLegend(0.3,0.7,0.5,0.9);
  legend4->AddEntry(N_EpiL,"NEUT","f");
  legend4->AddEntry(G_EpiL,"GENIE","f");
  legend4->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend4->Draw();
//
//NEW GRAPH________________________________________________________________
chi_squared_total=0;

for (int i = 0; i < N_EpiG->GetXaxis()->GetNbins()+1; ++i) {
    double mc_content = N_EpiG->GetBinContent(i+1);
    double data_content = G_EpiG->GetBinContent(i+1);
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}
  TCanvas *h_EpiG = new TCanvas("h_EpiG", "NEUT and GENIE pion energy comparison (gas)");
  N_EpiG->Draw();
  h_EpiG->Update();
  G_EpiG->SetLineColor(kRed);
  G_EpiG->Draw("same");
  auto legend5 = new TLegend(0.3,0.7,0.5,0.9);
  legend5->AddEntry(N_EpiG,"NEUT","f");
  legend5->AddEntry(G_EpiG,"GENIE","f");
  legend5->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend5->Draw();


//NEW GRAPH________________________________________________________________
chi_squared_total=0;

for (int i = 0; i < N_HEpiL->GetXaxis()->GetNbins()+1; ++i) {
    // N_Pmu is here the MC pmu distribution from NEUT
    double mc_content = N_HEpiL->GetBinContent(i+1);

    // N_Pmu is here_data is the MC pmu distribution from GENIE
    double data_content = G_HEpiL->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}


  TCanvas *h_HEpiL = new TCanvas("h_HEpiL", "NEUT and GENIE pion energy comparison (liquid)");
  N_HEpiL->Draw();
  h_HEpiL->Update();
  G_HEpiL->SetLineColor(kRed);
  G_HEpiL->Draw("same");
  auto legend7 = new TLegend(0.3,0.7,0.5,0.9);
  legend7->AddEntry(N_HEpiL,"NEUT","f");
  legend7->AddEntry(G_HEpiL,"GENIE","f");
  legend7->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend7->Draw();
//
//NEW GRAPH________________________________________________________________
chi_squared_total=0;

for (int i = 0; i < N_HEpiG->GetXaxis()->GetNbins()+1; ++i) {
    double mc_content = N_HEpiG->GetBinContent(i+1);
    double data_content = G_HEpiG->GetBinContent(i+1);
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}
  TCanvas *h_HEpiG = new TCanvas("h_HEpiG", "NEUT and GENIE pion energy comparison (gas)");
  N_HEpiG->Draw();
  h_HEpiG->Update();
  G_HEpiG->SetLineColor(kRed);
  G_HEpiG->Draw("same");
  auto legend6 = new TLegend(0.3,0.7,0.5,0.9);
  legend6->AddEntry(N_HEpiG,"NEUT","f");
  legend6->AddEntry(G_HEpiG,"GENIE","f");
  legend6->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend6->Draw();


  return (0);}
