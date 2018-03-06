#include "TRandom.h"

vector<Particle> resolution(vector<Particle> PartVec, float w){
	TRandom *r0 = new TRandom();
	vector<Particle> PartDet;
	PartDet.clear();
	for(unsigned int i=0;i < PartVec.size();i++){
		Particle Part = PartVec[i];

		float En=Part.GetEnergy();	
	    float px=Part.GetXMom();
		float py=Part.GetYMom();
        float pz=Part.GetZMom();

        float sig = w; //so 1 std dev = w percent of the original energy

        float En2 = (r0->Gaus(En,sig));
        Particle Part2 = Particle(Part.GetPDG(), px, py, pz, En2, Part.GetID()); 
		PartDet.push_back(Part2);
	}			                        					
return (PartDet);
}
