#include "Threshold.h"
Threshold::Threshold()
{
 
  float threshold = 0.05;

}

vector<Particle> Threshold::ThreshFunc(vector<Particle> PartVec){
	
 	float prot_thresh = .05; //2212
 	float pi_minus_thresh = 0.05; // -211
  	float pi0_thresh = .1; //111
  	float pi_plus_thresh= 0.05; //211
  	float Eff = 1.5; //Efficiency
        float En;
	vector<Particle> PartVecAbove;
	PartVecAbove.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
	
		En=Part.GetEnergy();	
	

 	        float r = ((double) rand() / (RAND_MAX));
		if (Part.GetPDG() == 111 && En > pi0_thresh && r <Eff){
		  	PartVecAbove.push_back(Part);			
 			}
		else if (En > prot_thresh && r <Eff){
			PartVecAbove.push_back(Part);
                        }
					}

return (PartVecAbove);}

Threshold::~Threshold(){}



