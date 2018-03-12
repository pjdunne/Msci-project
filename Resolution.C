#include "Resolution.h"
#include "TRandom.h"
Resolution::Resolution()
{
 
  float res = 0.05;

}

vector<Particle> Resolution::ResFunc(vector<Particle> PartVec, float w){
	TRandom *r0 = new TRandom();
 	float En;
	vector<Particle> PartDet;
	PartDet.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];
	
		En=Part.GetEnergy();	
	        float px=Part.GetPx();
		float py=Part.GetPy();
         	float pz=Part.GetPz();

                Part.SetEnergy(En+(r0->Gaus(0,w*En)));
		Part.SetPx(px+(r0->Gaus(0,w*px)));
		Part.SetPx(py+(r0->Gaus(0,w*py)));
		Part.SetPz(pz+(r0->Gaus(0,w*pz)));

		
		
		PartDet.push_back(Part);}			
 			
		
                        					
return (PartDet);}

Resolution::~Resolution(){}




