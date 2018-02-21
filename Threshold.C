#include "Threshold.h"
Threshold::Threshold()
{
 
  float threshold = 0.05;

}

vector<Particle> Threshold::ThreshFunc(vector<Particle> PartVec){
	//TH1D* hE = new TH1D("hE", "Energyplot", 100, 0, 10);
	
 	float prot_thresh = 0.0; //2212
 	float pi_minus_thresh = 0.05; // -211
  	float pi0_thresh = 0.; //111
  	float pi_plus_thresh= 0.05; //211
  	float Eff = 1.; //Efficiency
        float En;
	vector<Particle> PartVecAbove;
	PartVecAbove.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
	
		En=Part.GetEnergy();	
		//En=0.9;	
		//EVec.push_back(PartVec[i].GetEnergy());
 	        float r = ((double) rand() / (RAND_MAX));
		if ((Part.GetPDG() == 111) || (En > pi0_thresh) || (r <Eff)){
		  	PartVecAbove.push_back(Part);
			//hE->Fill(En);
 			}
		else if (En > prot_thresh || r <Eff){
			PartVecAbove.push_back(Part);
			//hE->Fill(En);
                       }
					}
//TCanvas *c = new TCanvas("c", "Energy Plot");
//hE->Draw();
return (PartVecAbove);}

Threshold::~Threshold(){}



