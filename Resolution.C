#include "TRandom2.h"
#include <cmath> 
#include <random>


vector<Particle> ResFunc(vector<Particle> PartVec, float w){
	TRandom2 *r0 = new TRandom2();
 	float En;
	vector<Particle> PartDet;
	PartDet.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];

		float px=Part.GetPx();
		float py=Part.GetPy();
         	float pz=Part.GetPz();
		float pmag = Part.GetMomentum();
	     
		En=Part.GetEnergy();	

		

                Part.SetEnergy(En+(r0->Gaus(0,w*En)));
		Part.SetPx(px+(r0->Gaus(0,w*px)));
		Part.SetPx(py+(r0->Gaus(0,w*py)));
		Part.SetPz(pz+(r0->Gaus(0,w*pz)));

		PartDet.push_back(Part);
		}			
 			
		
                        					
return (PartDet);}

//Resolution::~Resolution(){}



