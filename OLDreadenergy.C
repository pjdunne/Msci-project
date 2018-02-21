#include "Particle.C"
#include "Linkdef.h"


#include "TBranch.h" 

int OLDreadenergy(){
  //Particle part;
  TFile* file = new TFile("/home/hep/al3614/neutrinoproject3/newfile.root");
  TTree* tree = (TTree*)file->Get("newtree");
  //vector<Particle> *DetectedParticles = part.Threshold(PartVec, 0.5);
 
 
  TH1D* hE = new TH1D("hE", "Energyplot", 400, 0, 5);

 
 	float energy[240];
        float Thresh = 0.0;
	float En;
	int N;
	float Eff = 10.; //Efficiency

	//vector<Particle> *PartVecAbove;
	vector<Particle> *PartVec;
	vector<float> EVec;
	vector<int> NVec;
	EVec.clear();


       tree->SetBranchAddress("particles",&PartVec);


	Long64_t nentries = tree->GetEntries();
	for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
			tree->GetEntry(iEntry);
	
			for(unsigned int i=0;i < PartVec[0].size();i++){
			Particle Part = PartVec[0][i];
			       
			En=Part.GetEnergy();
			
			
			//hE->Fill(En);
			//EVec.push_back(PartVec[i].GetEnergy());
 				
				float r = ((double) rand() / (RAND_MAX));
				if (En>Thresh| r<Eff){
					//PartVecAbove->push_back(PartVec[iEntry]);
					EVec.push_back(En);
					}}}
  

  
  for (unsigned int i=0;i< EVec.size();i++){
         float E = EVec[i];
 	 hE->Fill(E);
  }


 

  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
   return(0);
}