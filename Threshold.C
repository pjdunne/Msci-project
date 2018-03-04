#include "Threshold.h"
Threshold::Threshold()
{
 
  float threshold = 0.05;

}


float Sigmoid(float x, float m, float Eff){
	return Eff/(1+exp(-((20*x)-m)));}

vector<Particle> Threshold::ThreshFunc(vector<Particle> PartVec, float prot_thresh, float neutron_thresh, float pi_pm_thresh, float pi0_thresh, float Eff){
	

        float En;
	vector<Particle> PartVecAbove;
	PartVecAbove.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
	
		En=Part.GetEnergy();	
	        float pz=Part.GetMomentum();

 	        float r = ((double) rand() / (RAND_MAX));
   		 if (Part.GetPDG() == 111 && r < Sigmoid(En, pi0_thresh, Eff)){
  		    PartVecAbove.push_back(Part);			
  		  }
  		  else if ((Part.GetPDG() == 211 || Part.GetPDG() == -211) && r < Sigmoid(En, pi_pm_thresh, Eff)){
  		    PartVecAbove.push_back(Part);
   		 }
   		 else if (Part.GetPDG() == 2212 && r < Sigmoid(En, prot_thresh, Eff)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (Part.GetPDG() == 2112 && r < Sigmoid(En, neutron_thresh, Eff)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (r<Eff){
   		   PartVecAbove.push_back(Part);
  		  }
					}

return (PartVecAbove);}


vector<Particle> liquidMomThresh(vector<Particle> PartVec){
  Threshold Thresh;		
  float prot_thresh = .2; //2212
  float neutron_thresh = 1.; //2112
  float pi_pm_thresh = 0.059; // +/-211
  float pi0_thresh = .059; //111
  float Eff = .99; //Efficiency
  
  return Thresh.ThreshFunc(PartVec, prot_thresh, neutron_thresh, pi_pm_thresh, pi0_thresh, Eff);
  
}

vector<Particle> gasMomThresh(vector<Particle> PartVec){
  Threshold Thresh;	
  float prot_thresh = .059; //2212
  float neutron_thresh = 1.; //2112
  float pi_pm_thresh = 0.016; // +/-211
  float pi0_thresh = .016; //111
  float Eff = .95; //Efficiency

  return Thresh.ThreshFunc(PartVec, prot_thresh, neutron_thresh, pi_pm_thresh, pi0_thresh, Eff);
}


Threshold::~Threshold(){}





