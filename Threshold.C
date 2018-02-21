#include "Threshold.h"

Threshold::Threshold()
{
 
  float threshold = 0.05;

}

vector<float> Threshold::ThreshFunc(vector<Particle> PartVec, float threshold){
	
	float En;
	float Eff  =1.;		       
	vector<float> EVec;
	EVec.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
	
		En=Part.GetEnergy();	
		En=0.9;	
		//EVec.push_back(PartVec[i].GetEnergy());
 				
		float r = ((double) rand() / (RAND_MAX));
		if (En>threshold| r<Eff){
			//PartVecAbove->push_back(PartVec[iEntry]);
			EVec.push_back(En);
					}}
return (EVec);}

Threshold::~Threshold(){}



