#include "Threshold.h"
Threshold::Threshold()
{
 
  float threshold = 0.05;

}


float Sigmoid(float x, float m, float Eff, float steep){
	return Eff/(1+exp(-(steep*(x-m))));}

vector<Particle> Threshold::ThreshFunc(vector<Particle> PartVec, float prot_thresh, float neutron_thresh, float pi_pm_thresh, float pi0_thresh, float Eff, float steep, int A){
	

        float En;
	vector<Particle> PartVecAbove;
	PartVecAbove.clear();
	
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
		int pdg = Part.GetPDG();
		En=Part.GetEnergy();
		if(A==1){
	        float P=Part.GetMomentum();
 	        float r = ((double) rand() / (RAND_MAX));
		float r1 = ((double) rand() / (RAND_MAX));
		float r2 = ((double) rand() / (RAND_MAX));
		float r3 = ((double) rand() / (RAND_MAX));
		float r4 = ((double) rand() / (RAND_MAX));

   		 if (pdg == 111 && r < Sigmoid(P, pi0_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);			
  		  }
  		 else if (abs(pdg) == 211  && r1 < Sigmoid(P, pi_pm_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2212 && r2 < Sigmoid(P, prot_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2112 && r3 < Sigmoid(P, neutron_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 if (pdg != 111 && abs(pdg) != 211 && pdg != 2212 && pdg != 2112){
   		   PartVecAbove.push_back(Part);}
		}

		else{
		float P = Part.GetEnergy();
 	        float r = ((double) rand() / (RAND_MAX));
		float r1 = ((double) rand() / (RAND_MAX));
		float r2 = ((double) rand() / (RAND_MAX));
		float r3 = ((double) rand() / (RAND_MAX));
		float r4 = ((double) rand() / (RAND_MAX));

   		 if (pdg == 111 && r < Sigmoid(P, pi0_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);			
  		  }
  		 else if (abs(pdg) == 211  && r1 < Sigmoid(P, pi_pm_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2212 && r2 < Sigmoid(P, prot_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2112 && r3 < Sigmoid(P, neutron_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 if (pdg != 111 && abs(pdg) != 211 && pdg != 2212 && pdg != 2112){
   		   PartVecAbove.push_back(Part);}
		}

					}
return (PartVecAbove);}


vector<Particle> liquidMomThresh(vector<Particle> PartVec){
  Threshold Thresh;		
  float prot_thresh = .2; //2212
  float neutron_thresh = 4.; //2112
  float pi_pm_thresh = 0.059; // +/-211
  float pi0_thresh = .059; //111
  float Eff = .95; //Efficiency
  float steep = 90.;
  int A=0;
  
  return Thresh.ThreshFunc(PartVec, prot_thresh, neutron_thresh, pi_pm_thresh, pi0_thresh, Eff,steep, A);
  
}

vector<Particle> gasMomThresh(vector<Particle> PartVec){
  Threshold Thresh;	
  float prot_thresh = .059; //2212
  float neutron_thresh = 4.; //2112
  float pi_pm_thresh = 0.016; // +/-211
  float pi0_thresh = .016; //111
  float Eff = .99; //Efficiency
  float steep = 90.;
  int A=1;
  return Thresh.ThreshFunc(PartVec, prot_thresh, neutron_thresh, pi_pm_thresh, pi0_thresh, Eff,steep, A);
  
}


Threshold::~Threshold(){}



