#include "Particle.C"
#include "Threshold.C"
#include "Linkdef.h"


#include "TBranch.h" 

int backupreadenergy(){
  //Particle part;
  TFile* file = new TFile("/home/hep/al3614/neutrinoproject3/newfile.root");
  TTree* tree = (TTree*)file->Get("newtree");
  //vector<Particle> *DetectedParticles = part.Threshold(PartVec, 0.5);
 
 
  TH1D* hE = new TH1D("hE", "Energyplot", 400, 0, 10);

 
 	float energy[240];
        float Thresh = 0.0;
	float En;
	int N;
	float Eff = 10.; //Efficiency

	vector<Particle> PartVecAbove;
	vector<Particle> *PartVec;
        vector<Particle> ParticleVec;

	vector<float> EVec;
	vector<int> NVec;
	EVec.clear();


       tree->SetBranchAddress("particles",&PartVec);


	Long64_t nentries = tree->GetEntries();
	for(unsigned int iEntry=0;iEntry< nentries;iEntry++){
			tree->GetEntry(iEntry);
        		PartVecAbove.clear();
                        ParticleVec.clear();

			Threshold Thresh;
			for(unsigned int i=0;i < PartVec[0].size();i++){
			Particle Part = PartVec[0][i];
			ParticleVec.push_back(Part);}

        		PartVecAbove=Thresh.ThreshFunc(ParticleVec);
		  	for (unsigned int j=0; j<PartVecAbove.size(); ++j){
				float Energy=PartVecAbove[j].GetEnergy();
				hE->Fill(Energy);}					  

				}
  

  

  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
   return(0);
}