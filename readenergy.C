#include "Particle.C"
#include "Linkdef.h"
#include "TBranch.h" 

int readenergy(){
  TFile* file = new TFile("/home/hep/al3614/neutrinoproject3/newfile.root");
  TTree* tree = (TTree*)file->Get("newtree");

 
  TH1D* hE = new TH1D("hE", "Energyplot", 100, 0, 5);
  
	float energy[240];
        float Thresh = 0.05;
	float En;
	float Eff = 1.; //Efficiency

	vector<Particle> *PartVecAbove;
	vector<Particle> *PartVec;
	vector<float> EVec;
	EVec.clear();
		
	TBranch *particlesBranch;
		
        tree->SetBranchAddress("particles",&PartVec);


	for(unsigned int iEntry=0;iEntry< tree->GetEntries();iEntry++){
				
			tree->GetEntry(iEntry);
				
			for(int i=0;i < PartVec[0].size();i++){
			Particle Part = PartVec[0][i];
			       

			En=Part.GetEnergy();
			
			//EVec.push_back(PartVec[i].GetEnergy());
 				
				float r = ((double) rand() / (RAND_MAX));
				if (En >= Thresh | r<Eff){
					//PartVecAbove->push_back(PartVec[iEntry]);
					EVec.push_back(En);}}}
  
  
  
  
  
  
  for (unsigned int i=0;i< EVec.size();i++){
         float E = EVec[i];
 	 hE->Fill(E);
  }
 
 cout<<EVec.size();
 cout<<"random component"<<EVec[30];
  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
  return(0);
}
