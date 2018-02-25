#include "Threshold.h"
Threshold::Threshold()
{
 
  float threshold = 0.05;

}

vector<Particle> Threshold::ThreshFunc(vector<Particle> PartVec, float th){
	
 	float prot_thresh = th; //2212
 	float pi_minus_thresh = 0.05; // -211
  	float pi0_thresh = th; //111
  	float pi_plus_thresh= 0.05; //211
  	float Eff = 1.1; //Efficiency
        float En;
	vector<Particle> PartVecAbove;
	PartVecAbove.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
	
		En=Part.GetEnergy();	
	        float Mom=Part.GetMomentum();

 	        float r = ((double) rand() / (RAND_MAX));
		if (Part.GetPDG() == 111 && Mom > pi0_thresh && r <Eff){
		  	PartVecAbove.push_back(Part);			
 			}
		else if (Mom > prot_thresh && r <Eff){
			PartVecAbove.push_back(Part);
                        }
					}

return (PartVecAbove);}

Threshold::~Threshold(){}



