#include "TObject.h"
#include <iostream>
#include <string>
#include <sstream>
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
#include "Identify.C"
#include "Chi.C"
#include "Linkdef.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "Norm.C"
#include "TextTable.h"

int readVars_NG(){
 for(int b =0; b < 3;b++){
  TFile* fileNEUT = new TFile("T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v4.root");
 // TFile* fileNEUT = new TFile("genie_argon_fnalsmall_run1_flat_v2.root");
  TTree* tree = (TTree*)fileNEUT->Get("FlatTree_VARS");
  TFile* fileGENIE;
  if(b==0){
  fileGENIE = new TFile("genie_argon_fnalsmall_run1_flat_v2.root");}
  if(b==1){
  fileGENIE = new TFile("genie_argon_fnalsmall_MecwithNC_proc_flat.root");}
  if(b==2){
  fileGENIE = new TFile("genie_argon_fnalsmall_Effsftem_proc_flat.root");}


  TFile *Flux = new TFile("t2kflux_2016_plus250kA.root");
  TH1D* hFlux = (TH1D*)Flux->Get("enu_nd280_numu");
  TAxis *axis = hFlux->GetXaxis();
  int bmax = axis->GetNbins()+1;
  double wid = axis->GetBinWidth(0);
 // double integral = hFlux->Integral(0,bmax,"width");
  //cout<<integral<<endl;
  
 //TCanvas *canv = new TCanvas("enu_nd280_numu", "T2K nu_mu flux at ND280 with +250 kA horn operation");
 //hFlux->Draw();
 // canv->SaveAs("T2K_Flux.pdf");

  TTree* treeG = (TTree*)fileGENIE->Get("FlatTree_VARS");
 
  float bin = 100;
  TH1D* h = new TH1D("h", "True  Energy plots", 1000, 0, 10);

  TH1D* N_Pmu = new TH1D("N_Pmu", "NEUT and GENIE muon momentum magnitude (no threshold)", bin, 0, 4);
  TH1D* G_Pmu = new TH1D("G_Pmu", "NEUT and GENIE muon momentum magnitude (no threshold)", bin, 0, 4);

  TH1D* nPrG = new TH1D("nPrG", "NEUT and GENIE proton number (no threshold)", 12, 0, 12);
  TH1D* nPrN = new TH1D("nPrN", "NEUT and GENIE proton number (no threshold)", 12, 0, 12);

  TH1D* nPrG_L = new TH1D("nPrG_L", "NEUT and GENIE proton number (liquid)", 12, 0, 12);
  TH1D* nPrG_G = new TH1D("nPrG_G", "NEUT and GENIE proton number (gas)", 12, 0, 12);

  TH1D* nPrN_L = new TH1D("nPrN_L", "NEUT and GENIE proton number (liquid)", 12, 0, 12);
  TH1D* nPrN_G = new TH1D("nPrN_G", "NEUT and GENIE proton number (gas)", 12, 0, 12);

  TH1D* N_PmuG = new TH1D("N_PmuG", "NEUT and GENIE muon momentum magnitude (gas)", bin, 0, 4);
  TH1D* G_PmuG = new TH1D("G_PmuG", "NEUT and GENIE muon momentum magnitude (gas)", bin, 0, 4);

  TH1D* N_PmuL= new TH1D("N_PmuL", "NEUT and GENIE muon momentum magnitude (liquid)", bin, 0, 4);
  TH1D* G_PmuL= new TH1D("G_PmuL", "NEUT and GENIE muon momentum magnitude (liquid)", bin, 0, 4);

  TH1D* N_EpiL= new TH1D("N_EpiL", "NEUT and GENIE pion energy (liquid)", bin, 0, 4);
  TH1D* G_EpiL= new TH1D("G_EpiL", "NEUT and GENIE pion energy (liquid)", bin, 0, 4);
  TH1D* N_HEpiL= new TH1D("N_HEpiL", "NEUT and GENIE highest pion energy (liquid)", bin, 0, 4);
  TH1D* G_HEpiL= new TH1D("G_HEpiL", "NEUT and GENIE highest pion energy (liquid)", bin, 0, 4);


  TH1D* N_EpiG= new TH1D("N_EpiG", "NEUT and GENIE pion energy (gas)", bin, 0, 4);
  TH1D* G_EpiG= new TH1D("G_EpiG", "NEUT and GENIE pion energy (gas)", bin, 0, 4);
  TH1D* N_HEpiG= new TH1D("N_HEpiG", "NEUT and GENIE highest pion energy (gas)", bin, 0, 4);
  TH1D* G_HEpiG= new TH1D("G_HEpiG", "NEUT and GENIE highest pion energy (gas)", bin, 0, 4);

 //nPrG_L ->SetFillColor(kYellow-7);
// nPrG_G->SetFillColor(kYellow-7);
// nPrG->SetFillColor(kYellow-7);
 
   N_PmuG->GetXaxis()->SetTitle("Momentum (Gev)");
   G_PmuG->GetXaxis()->SetTitle("Momentum(Gev)");
   G_EpiL->GetXaxis()->SetTitle("Energy (Gev)");
   G_EpiG->GetXaxis()->SetTitle("Energy (Gev)");

   N_PmuG->GetYaxis()->SetTitle("Number of events");
   G_PmuG->GetYaxis()->SetTitle("Number of events");
   G_EpiL->GetYaxis()->SetTitle("Number of events");
   G_EpiG->GetYaxis()->SetTitle("Number of events");
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
  double wG = 20000./nentries;
  double wL = 100.2*wG;
  for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
	tree->GetEntry(iEntry);
	int nPr = 0;
        PartVec.clear();
	EPiVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	Resolution Res;

        h->Fill(Enu_t);

	for (int i = 0; i < nfsp; ++i)  {
	          int id = 0;
		  id++;
              
                  Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id);
		  PartVec.push_back(Part);
		  if(pdg[i]==2212){nPr++;}                //Proton Number
		  if(pdg[i] == 13){                   //Muon Momentum
		  N_Pmu->Fill(Part.GetMomentum());}}		  
	//MODE SELECTION
        if (id_0pi(PartVec) == 1){ // use this to choose 0 pi modes
       // if (id_1pi(PartVec) == 1){ // use this to choose 1 pi modes
       // if (id_0pi(PartVec) == 0 && id_1pi(PartVec) == 0){ // use this to choose other modes  
	nPrN->Fill(nPr);
	nPr=0;			
        PartRes=Res.ResFunc(PartVec,.01);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 13){
		N_PmuL->Fill(P.GetMomentum(),wL);} //Muon momentum liquid
		if(pd==2212){nPr++;}                       //Proton number
		if(pd == 111 | pd == 211 | pd == -211){   //Pion energy liquid
		N_EpiL->Fill(P.GetEnergy(),wL);
		EPiVec.push_back(P.GetEnergy());}
		}
	if (EPiVec.size()>0){
        N_HEpiL->Fill(*max(EPiVec.begin(),EPiVec.end()),wL);}  //highest energy pion liquid
        nPrN_L->Fill(nPr,wL);  //proton number liquid
        EPiVec.clear();
	nPr=0;
	PartVecGas=gasMomThresh(PartRes);
	for (int i =0; i<PartVecGas.size(); i++){
		Particle Pa = PartVecGas[i];
		int pdgn= Pa.GetPDG();
		if(pdgn == 13){          
		N_PmuG->Fill(Pa.GetMomentum(),wG);}

		if(pdgn==2212){nPr++;}                            //Proton number
			

		if(pdgn == 111 | pdgn == 211 | pdgn == -211){   //Pion energy gas
		N_EpiG->Fill(Pa.GetEnergy(),wG);
		EPiVec.push_back(Pa.GetEnergy());}
		}	
	nPrN_G->Fill(nPr,wG);
	if (EPiVec.size()>0){
	N_HEpiG->Fill(maxi(EPiVec),wG);} //highest pion energy gas
	}
	}
//Read GENIE
  double wL2 = 1*wL;//*1.49148689133;
  Long64_t nentriesG= treeG->GetEntries();
  for(unsigned int iEntry=0;iEntry< nentriesG;iEntry++){
	treeG->GetEntry(iEntry);
	int nPr = 0;
	EPiVec.clear();
        PartVec.clear();
        PartVecLiquid.clear();
	PartVecGas.clear();
	Resolution Res;

	for (int i = 0; i < nfspG; ++i)  {
	          int id = 0;
		  
		  id++;
                  Particle Part = Particle(pdgG[i], pxG[i], pyG[i],pzG[i], energyG[i], id);
		  PartVec.push_back(Part);
		  if(pdgG[i]==2212){
		 	nPr++;}
		  if(pdgG[i] == 13){
        		G_Pmu->Fill(Part.GetMomentum());}}	

	//MODE SELECTION
        if (id_0pi(PartVec) == 1){ // use this to choose 0 pi modes
        //if (id_1pi(PartVec) == 1){ // use this to choose 1 pi modes
        //if (id_0pi(PartVec) == 0 && id_1pi(PartVec) == 0){ // use this to choose other modes  
	nPrG->Fill(nPr);
	nPr=0;										
        PartRes=Res.ResFunc(PartVec,.01);
        PartVecLiquid=liquidMomThresh(PartRes);
	for (int i =0; i<PartVecLiquid.size(); i++){
		Particle P = PartVecLiquid[i];
		int pd= P.GetPDG();
		if(pd == 13){
		G_PmuL->Fill(P.GetMomentum(),wL);}
		if(pd==2212){nPr++;}
		if(pd == 111 | pd == 211 | pd == -211){   //Pion energy liquid
		G_EpiL->Fill(P.GetEnergy(), wL);
		EPiVec.push_back(P.GetEnergy());}
		//highest energy pion liquid
		}
	if (EPiVec.size()>0){
        G_HEpiL->Fill(maxi(EPiVec),wL2);} //Highest E pion
	EPiVec.clear();
	nPrG_L->Fill(nPr,wL2);
	nPr=0;
	PartVecGas=gasMomThresh(PartRes);
	for (int j =0; j<PartVecGas.size(); j++){
		Particle Pa = PartVecGas[j];
		int pdgn= Pa.GetPDG();
		if(pdgn == 13){
		G_PmuG->Fill(Pa.GetMomentum(),wG);}
		if(pdgn==2212){nPr++;}
		if(pdgn == 111 | pdgn == 211 | pdgn == -211){   //Pion energy gas
		EPiVec.push_back(Pa.GetEnergy());
		G_EpiG->Fill(Pa.GetEnergy(),wG);}
		}
	if (EPiVec.size()>0){
	G_HEpiG->Fill(maxi(EPiVec),wG);} 
	nPrG_G->Fill(nPr,wG);      
	}
	}

N_PmuG = NormG(N_PmuG);
G_PmuG = NormG(G_PmuG);

N_PmuL = NormL(N_PmuL);
G_PmuL = NormL(G_PmuL);

nPrN_L = NormL(nPrN_L);
nPrG_L = NormL(nPrG_L);

nPrN_G = NormL(nPrN_G);
nPrG_G = NormL(nPrG_G);
//GRAPHS__________________________________________________________________
double chiPmuG=Chi(N_PmuG,G_PmuG);
  TCanvas *hN_PmuG;
  if(b==0){
  hN_PmuG = new TCanvas("hN_PmuG", "NEUT and GENIE muon momentum magnitude comparison 0 (gas)");}
  if(b==1){
  hN_PmuG = new TCanvas("hN_PmuG1", "NEUT and GENIE muon momentum magnitude comparison 1 (gas)");}
  if(b==2){
  hN_PmuG = new TCanvas("hN_PmuG2", "NEUT and GENIE muon momentum magnitude comparison 2 (gas)");}
  N_PmuG->Draw();
  hN_PmuG->Update();
  G_PmuG->SetLineColor(kRed);
  G_PmuG->Draw("same");
  auto legend = new TLegend(0.3,0.7,0.5,0.9);
  legend->AddEntry(N_PmuG,"NEUT","f");
  legend->AddEntry(G_PmuG,"GENIE","f");
  legend->SetHeader(Form("#chi^{2}=%f", chiPmuG));
  legend->Draw();
  if (b==0){
  hN_PmuG->SaveAs("Muon momentum GENIE model 0 (gas).pdf");}
  if (b==1){
  hN_PmuG->SaveAs("Muon momentum GENIE model 1 (gas).pdf");}
  if (b==2){
  hN_PmuG->SaveAs("Muon momentum GENIE model 2 (gas).pdf");}

double chiPmuL=Chi(N_PmuL,G_PmuL);
  TCanvas *hN_PmuL;
  if(b==0){
  hN_PmuL = new TCanvas("hN_PmuL", "NEUT and GENIE muon momentum magnitude comparison 0 (liquid)");}
  if(b==1){
  hN_PmuL = new TCanvas("hN_PmuL1", "NEUT and GENIE muon momentum magnitude comparison 1 (liquid)");}
  if(b==2){
  hN_PmuL = new TCanvas("hN_PmuL2", "NEUT and GENIE muon momentum magnitude comparison 2 (liquid)");}
  N_PmuL->Draw();
  hN_PmuL->Update();
  G_PmuL->SetLineColor(kRed);
  G_PmuL->Draw("same");
  auto legend1 = new TLegend(0.3,0.7,0.5,0.9);
  legend1->AddEntry(N_PmuL,"NEUT","f");
  legend1->AddEntry(G_PmuL,"GENIE","f");
  legend1->SetHeader(Form("#chi^{2}=%f", chiPmuL));
  legend1->Draw();
  if (b==0){
  hN_PmuL->SaveAs("Muon momentum GENIE model 0 (liquid).pdf");}
  if (b==1){
  hN_PmuL->SaveAs("Muon momentum GENIE model 1 (liquid).pdf");}
  if (b==2){
  hN_PmuL->SaveAs("Muon momentum GENIE model 2 (liquid).pdf");} 

double chinPrL=Chi(nPrN_L,nPrG_L)*bin/12;
  TCanvas *hnPr_L;
  if(b==0){
  hnPr_L = new TCanvas("hnPr_L", "NEUT and GENIE proton multiplicity comparison 0 (liquid)");}
  if(b==1){
  hnPr_L = new TCanvas("hnPr_L1", "NEUT and GENIE proton multiplicity  comparison 1 (liquid)");}
  if(b==2){
  hnPr_L = new TCanvas("hnPr_L2", "NEUT and GENIE proton multiplicity comparison 2 (liquid)");}
  nPrN_L->Draw("*H");
  hnPr_L->Update();
  nPrG_L->SetLineColor(kRed);
  nPrG_L->Draw("same");
  auto legend8 = new TLegend(0.3,0.7,0.5,0.9);
  legend8->AddEntry(nPrN_L,"NEUT","f");
  legend8->AddEntry(nPrG_L,"GENIE","f");
  legend8->SetHeader(Form("#chi^{2}=%f", chinPrL));
  legend8->Draw();
  if (b==0){
  hnPr_L->SaveAs("Proton multiplicity GENIE model 0 (liquid).pdf");}
  if (b==1){
  hnPr_L->SaveAs("Proton multiplicity GENIE model 1 (liquid).pdf");}
  if (b==2){
  hnPr_L->SaveAs("Proton multiplicity GENIE model 2 (liquid).pdf");}

double chinPrG=Chi(nPrN_G,nPrG_G)*bin/12;
  TCanvas *hnPr_G; 
  if(b==0){
  hnPr_G = new TCanvas("hnPr_G", "NEUT and GENIE proton multiplicity comparison 0 (gas)");}
  if(b==1){
  hnPr_G = new TCanvas("hnPr_G1", "NEUT and GENIE proton multiplicity comparison 1 (gas)");}
  if(b==2){
  hnPr_G = new TCanvas("hnPr_G2", "NEUT and GENIE proton multiplicity comparison 2 (gas)");}
  nPrN_G->Draw("*H");
  hnPr_G->Update();
  nPrG_G->SetLineColor(kRed);
  nPrG_G->Draw("same");
  auto legend9 = new TLegend(0.3,0.7,0.5,0.9);
  legend9->AddEntry(nPrN_G,"NEUT","f");
  legend9->AddEntry(nPrG_G,"GENIE","f");
  legend9->SetHeader(Form("#chi^{2}=%f", chinPrG));
  legend9->Draw();
  if (b==0){
  hnPr_G->SaveAs("Proton multiplicity GENIE model 0 (gas).pdf");}
  if (b==1){
  hnPr_G->SaveAs("Proton multiplicity GENIE model 1 (gas).pdf");}
  if (b==2){
  hnPr_G->SaveAs("Proton multiplicity GENIE model 2 (gas).pdf");}

 
double chiPmu= Chi(N_Pmu,G_Pmu);
  TCanvas* hNPmu;
  if(b==0){
  hNPmu = new TCanvas("hN_Pmu", "NEUT and GENIE muon momentum magnitude comparison 0  (no threshold)");}
  if(b==1){
  hNPmu = new TCanvas("hN_Pmu1", "NEUT and GENIE muon momentum magnitude comparison 1 (no threshold)");}
  if(b==2){
  hNPmu = new TCanvas("hN_Pmu2", "NEUT and GENIE muon momentum magnitude comparison 2 (no threshold)");}
  N_Pmu->Draw();
  hNPmu->Update();
  G_Pmu->SetLineColor(kRed);
  G_Pmu->Draw("same");
  auto legend2 = new TLegend(0.3,0.7,0.5,0.9);
  legend2->AddEntry(N_Pmu,"NEUT","f");
  legend2->AddEntry(G_Pmu,"GENIE","f");
  legend2->SetHeader(Form("#chi^{2}=%f", chiPmu));
  legend2->Draw();
  if (b==0){
  hN_PmuL->SaveAs("Muon momentum GENIE model 0 (no threshold).pdf");}
  if (b==1){
  hN_PmuL->SaveAs("Muon momentum GENIE model 1 (no threshold).pdf");}
  if (b==2){
  hN_PmuL->SaveAs("Muon momentum GENIE model 2 (no threshold).pdf");} 

  

double chinPr=Chi(nPrN,nPrG);
  TCanvas *hnPr;
  if(b==0){
  hnPr = new TCanvas("hnPr", "NEUT and GENIE proton multiplicity comparison 0 (no threshold)");}
  if(b==1){
  hnPr = new TCanvas("hnPr1", "NEUT and GENIE proton multiplicity comparison 1 (no threshold)");}
  if(b==2){
  hnPr = new TCanvas("hnPr2", "NEUT and GENIE proton multiplicity comparison 2 (no threshold)");}
  nPrN->Draw("*H");
  hnPr->Update();
  nPrG->SetLineColor(kRed);
  nPrG->Draw("same");
  auto legend3 = new TLegend(0.3,0.7,0.5,0.9);
  legend3->AddEntry(nPrN,"NEUT","f");
  legend3->AddEntry(nPrG,"GENIE","f");
  legend3->SetHeader(Form("#chi^{2}=%f", chinPr));
  legend3->Draw();




cout <<"GENIE Model:"<< b<<endl;
cout<<"Proton Multiplicity Liquid:"<<""<<chinPrL<<endl;
cout<<"Proton Multiplicity Gas:"<<""<<chinPrG<<endl;
cout<<"Muon momentum Liquid:"<<""<<chiPmuL<<endl;
cout<<"Muon momentum Gas:"<<""<<chiPmuG<<endl;






/*



chi_squared_total=Chi(N_EpiL,G_EpiL);

  TCanvas *h_EpiL = new TCanvas("h_EpiL", "NEUT and GENIE pion energy comparison (liquid)");
  N_EpiL->Draw();
  h_EpiL->Update();
  G_EpiL->SetLineColor(kRed);
  G_EpiL->Draw("same");
  auto legend4 = new TLegend(0.3,0.7,0.5,0.9);
  legend4->AddEntry(N_EpiL,"NEUT","f");
  legend4->AddEntry(G_EpiL,"GENIE","f");
  legend4->SetHeader(Form("#chi^{2}=%f", chi_squared_total/bin));
  legend4->Draw();

chi_squared_total=Chi(N_EpiG,G_EpiG);
  TCanvas *h_EpiG = new TCanvas("h_EpiG", "NEUT and GENIE pion energy comparison (gas)");
  N_EpiG->Draw();
  h_EpiG->Update();
  G_EpiG->SetLineColor(kRed);
  G_EpiG->Draw("same");
  auto legend5 = new TLegend(0.3,0.7,0.5,0.9);
  legend5->AddEntry(N_EpiG,"NEUT","f");
  legend5->AddEntry(G_EpiG,"GENIE","f");
  legend5->SetHeader(Form("#chi^{2}=%f", chi_squared_total/bin));
  legend5->Draw();

chi_squared_total=Chi(N_HEpiL,G_HEpiL);
  TCanvas *h_HEpiL = new TCanvas("h_HEpiL", "NEUT and GENIE pion energy comparison (liquid)");
  N_HEpiL->Draw();
  h_HEpiL->Update();
  G_HEpiL->SetLineColor(kRed);
  G_HEpiL->Draw("same");
  auto legend7 = new TLegend(0.3,0.7,0.5,0.9);
  legend7->AddEntry(N_HEpiL,"NEUT","f");
  legend7->AddEntry(G_HEpiL,"GENIE","f");
  legend7->SetHeader(Form("#chi^{2}=%f", chi_squared_total/bin));
  legend7->Draw();
//
//NEW GRAPH________________________________________________________________
chi_squared_total=Chi(N_HEpiG,G_HEpiG);
  TCanvas *h_HEpiG = new TCanvas("h_HEpiG", "NEUT and GENIE pion energy comparison (gas)");
  N_HEpiG->Draw();
  h_HEpiG->Update();
  G_HEpiG->SetLineColor(kRed);
  G_HEpiG->Draw("same");
  auto legend6 = new TLegend(0.3,0.7,0.5,0.9);
  legend6->AddEntry(N_HEpiG,"NEUT","f");
  legend6->AddEntry(G_HEpiG,"GENIE","f");
  legend6->SetHeader(Form("#chi^{2}=%f", chi_squared_total/bin));
  legend6->Draw();
*/
}
   /* TextTable t( '-', '|', '+' );

    t.add( "0pi" );
    t.add( "GENIE 0" );
   // t.add( "GENIE 1" );
   // t.add( "GENIE 2" );
    t.endOfRow();

    t.add("");
    t.add( "Gas | Liquid" );
    t.add( "Gas | Liquid" );
    t.add( "Gas | Liquid" );
    t.endOfRow();

    t.add( "nPr" );
    t.add( "chinPrG | chinPrL" );
    t.endOfRow();

    t.add( "Pmu" );
    t.add( "chinPmuG | chinPmuL" );
    t.endOfRow();

    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t;
    */

  return (0);}
