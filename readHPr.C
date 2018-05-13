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
#include "Identify.C"
#include "Resolution.C"
#include "Linkdef.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TextTable.h"
#include "Norm.C"
#include "Chi.C"
#include "fstream"
int readHPr(){
  ofstream myfile;
  myfile.open ("summary1.txt");
  for(int b =0; b < 2;b++){
  int bin = 400;
  //TFile* fileNEUT = new TFile("T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v4.root"); \\Choose this to read NEUT files
  TFile* fileNEUT = new TFile("genie_argon_fnalsmall_Effsftem_proc_flat.root"); \\Choose this to read GENIE files


  TTree* tree = (TTree*)fileNEUT->Get("FlatTree_VARS");
  TFile* fileGENIE;
  if(b==0){
  fileGENIE = new TFile("genie_argon_fnalsmall_run1_flat_v2.root");}
  if(b==1){
  fileGENIE = new TFile("genie_argon_fnalsmall_MecwithNC_proc_flat.root");}
  if(b==2){
  fileGENIE = new TFile("genie_argon_fnalsmall_Effsftem_proc_flat.root");}

  TTree* treeG = (TTree*)fileGENIE->Get("FlatTree_VARS");


  TH1D* N_HEpr= new TH1D("N_HEpr", "NEUT and GENIE highest proton momentum", bin, 0, 7);
  TH1D* G_HEpr= new TH1D("G_HEpr", "NEUT and GENIE highest proton momentum", bin, 0, 7);

  TH1D* N_HEprL= new TH1D("N_HEprL", "NEUT and GENIE highest proton momentum (liquid)", bin, 0, 5);
  TH1D* G_HEprL= new TH1D("G_HEprL", "NEUT and GENIE highest proton momentum (liquid)", bin, 0, 5);

  TH1D* N_HEprG= new TH1D("N_HEprG", "NEUT and GENIE highest proton momentum (gas)", bin, 0, 5);
  TH1D* G_HEprG= new TH1D("G_HEprG", "NEUT and GENIE highest proton momentum (gas)", bin, 0, 5);

 //hCL->SetFillColor(kYellow-7);
  //hKL->SetFillColor(kYellow-7);
 // hKL_diff->SetFillColor(kYellow-7);
 // hCL_diff->SetFillColor(kYellow-7);
  //hCG->SetFillColor(kYellow-7);
 // hCG_diff->SetFillColor(kYellow-7);
 // hKG_diff->SetFillColor(kYellow-7);
//  hKG->SetFillColor(kYellow-7);
   N_HEpr->GetXaxis()->SetTitle("Momentum (GeV/c)");
   N_HEpr->GetYaxis()->SetTitle("Number of events");
   G_HEpr->GetXaxis()->SetTitle("Momentum (GeV/c)");
   G_HEpr->GetYaxis()->SetTitle("Number of events");
   N_HEprL->GetXaxis()->SetTitle("Momentum (GeV/c)");
   N_HEprL->GetYaxis()->SetTitle("Number of events");
   N_HEprG->GetXaxis()->SetTitle("Momentum (GeV/c)");
   N_HEprG->GetYaxis()->SetTitle("Number of events");
   G_HEprL->GetXaxis()->SetTitle("Momentum (GeV/c)");
   G_HEprL->GetYaxis()->SetTitle("Number of events");
   G_HEprG->GetXaxis()->SetTitle("Momentum (GeV/c)");
   G_HEprG->GetYaxis()->SetTitle("Number of events");
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

float rw = 0.0;	
//Read NEUT
  Long64_t nentries = tree->GetEntries();
  double wG = 1;//20000./nentries;
  double wL = 1;//100.2*wG;
  for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
	tree->GetEntry(iEntry);
	int nPr = 0;
        PartVec.clear();
	EPrVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	//Resolution Res;


	for (int i = 0; i < nfsp; ++i)  {
	          int id = 0;
		  id++;
                  Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
		  PartVec.push_back(Part);
		  if(Part.GetPDG() == 2212){  
		  N_HEpr->Fill(Part.GetMomentum());}
			}	
		  	
	//MODE SELECTION
        if (id_0pi(PartVec) == 1){   // use this to choose 0 pi modes
        //if (id_1pi(PartVec) == 1){   // use this to choose 1 pi modes
        //if (id_0pi(PartVec) == 0 && id_1pi(PartVec) == 0){ // use this to choose other modes  


        PartRes=ResFunc(PartVec,rw);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();

		if(pd == 2212){ 
		//N_HEprL->Fill(P.GetMomentum(),wL);
		EPrVec.push_back(P.GetMomentum());}
		}
	if (EPrVec.size()>0){
        N_HEprL->Fill(maxi(EPrVec),wL);}  //highest energy proton liquid

        EPrVec.clear();

	PartVecGas=gasMomThresh(PartRes);
	for (int i =0; i<PartVecGas.size(); i++){
		Particle Pa = PartVecGas[i];
		int pdgn= Pa.GetPDG();
		if(pdgn == 2212){   
		//N_HEprG->Fill(Pa.GetMomentum(),wG);
		EPrVec.push_back(Pa.GetMomentum());}
		}	
	if (EPrVec.size()>0){
	N_HEprG->Fill(maxi(EPrVec),wG);} //highest proton energy gas	
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
	//Resolution Res2;

	for (int i = 0; i < nfspG; ++i)  {
	          int id = 0;
		  id++;
                  Particle Part = Particle(pdgG[i], pxG[i], pyG[i],pzG[i], energyG[i], id);
		  PartVec.push_back(Part);
		  if(Part.GetPDG() == 2212){  
		  G_HEpr->Fill(Part.GetMomentum());}
		  }	
		
	//MODE SELECTION
        if (id_0pi(PartVec) == 1){ // use this to choose 0 pi modes
        //if (id_1pi(PartVec) == 1){ // use this to choose 1 pi modes
        //if (id_0pi(PartVec) == 0 && id_1pi(PartVec) == 0){ // use this to choose other modes        

						
        PartRes=ResFunc(PartVec,rw);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 2212){  EPrVec.push_back(P.GetMomentum());}			
		}
	if (EPrVec.size()>0){
        G_HEprL->Fill(maxi(EPrVec),wL);} //highest energy proton liquid
	EPrVec.clear();

	PartVecGas=gasMomThresh(PartRes);
	for (unsigned int j =0; j<PartVecGas.size(); j++){
		Particle Pa = PartVecGas[j];
		int pdgn = Pa.GetPDG();
		if(pdgn == 2212){  
		//G_HEprG->Fill(Pa.GetMomentum(),wG); 		
		EPrVec.push_back(Pa.GetMomentum());}
		}
	if (EPrVec.size()>0){
	G_HEprG->Fill(maxi(EPrVec),wG);}	 
	}
	}

N_HEprG = NormG(N_HEprG);
G_HEprG = NormG(G_HEprG);

N_HEprL = NormL(N_HEprL);
G_HEprL = NormL(G_HEprL);

double chiPprL=Chi(N_HEprL,G_HEprL,bin);
  TCanvas *h_HEprL;
  if(b==0){
  h_HEprL = new TCanvas("h_HEprL", "0pi_GENIE2 and GENIE highest proton momentum comparison 0 (liquid)");}
  if(b==1){
  h_HEprL = new TCanvas("h_HEprL1", "0pi_GENIE2 and GENIE highest  proton momentum comparison 1 (liquid)");}
  if(b==2){
  h_HEprL = new TCanvas("h_HEprL2", "NEUT and GENIE highest  proton momentum comparison 2 (liquid)");}

  G_HEprL->Draw();
  h_HEprL->Update();
  N_HEprL->SetLineColor(kRed);
  N_HEprL->Draw("same");
  auto legend7 = new TLegend(0.4,0.7,0.6,0.9);
  legend7->AddEntry(N_HEprL,"GENIE 2","f");
  legend7->AddEntry(G_HEprL,"GENIE","f");
  legend7->SetHeader(Form("#chi^{2}=%f", chiPprL));
  legend7->Draw();
  if (b==0){
  h_HEprL->SaveAs("0pi_Proton momentum GENIE2_GENIE model 0 (liquid).pdf");}
  if (b==1){
  h_HEprL->SaveAs("0pi_Proton momentum GENIE2_GENIE model 1 (liquid).pdf");}
  if (b==2){
  h_HEprL->SaveAs("Proton momentum GENIE model 2 (liquid).pdf");}


double chiPprG=Chi(N_HEprG,G_HEprG,bin);
  TCanvas *h_HEprG;
  if(b==0){
  h_HEprG = new TCanvas("h_HEprG", "0pi_GENIE2 and GENIE highest  proton momentum comparison 0 (gas)");}
  if(b==1){
  h_HEprG = new TCanvas("h_HEprG1", "0pi_GENIE2 and GENIE highest proton momentum comparison 1 (gas)");}
  if(b==2){
  h_HEprG = new TCanvas("h_HEprG2", "NEUT and GENIE highest proton momentum comparison 2 (gas)");}

  N_HEprG->Draw();
  h_HEprG->Update();
  G_HEprG->SetLineColor(kRed);
  G_HEprG->Draw("same");
  auto legend6 = new TLegend(0.4,0.7,0.6,0.9);
  legend6->AddEntry(N_HEprG,"GENIE 2","f");
  legend6->AddEntry(G_HEprG,"GENIE","f");
  legend6->SetHeader(Form("#chi^{2}=%f", chiPprG));
  legend6->Draw();
  if (b==0){
  h_HEprG->SaveAs("0pi_Proton momentum GENIE2_GENIE model 0 (gas).pdf");}
  if (b==1){
  h_HEprG->SaveAs("0pi_Proton momentum GENIE2_GENIE model 1 (gas).pdf");}
  if (b==2){
  h_HEprG->SaveAs("Proton momentum GENIE_GENIE model 2 (gas).pdf");}

/*double chi_squared_total=Chi(N_HEpr,G_HEpr,bin);
  TCanvas *h_HEpr = new TCanvas("h_HEpr", "NEUT and GENIE proton momentum comparison (no threshold)");
  G_HEpr->Draw();
  h_HEpr->Update();
  N_HEpr->SetLineColor(kRed);
  N_HEpr->Draw("same");
  auto legend = new TLegend(0.4,0.7,0.6,0.9);
  legend->AddEntry(N_HEpr,"GENIE 3","f");
  legend->AddEntry(G_HEpr,"GENIE","f");
  legend->SetHeader(Form("#chi^{2}=%f", chi_squared_total));
  legend->Draw();
  if (b==0){
  h_HEprG->SaveAs("Proton momentum GENIE model 0 (no threshold).pdf");}
  if (b==1){
  h_HEprG->SaveAs("Proton momentum GENIE model 1 (no threshold).pdf");}
  if (b==2){
  h_HEprG->SaveAs("Proton momentum GENIE model 2 (no threshold).pdf");}
*/

cout <<"GENIE Model:"<< b<<endl;
cout<<"Proton Momentum Liquid:"<<" "<<chiPprL<<endl;
cout<<"Proton Momentum Gas:"<<" "<<chiPprG<<endl;

myfile <<"GENIE Model:"<< b<<"\n";
myfile <<"Proton Momentum Liquid:"<<" "<<chiPprL<<"\n";
myfile <<"Proton Momentum Gas:"<<" "<<chiPprG<<"\n";

  }
myfile.close();
  return (0);}
