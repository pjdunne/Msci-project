#include "TRandom.h"
#include <cmath> 

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
        float pmag = Part.GetMomMag();
        float unitx = px/pmag;
        float unity = py/pmag;
        float unitz = pz/pmag;
        float mass = 0. ; //in units of GeV/ c^2
        // assign diff resolutions for each particle
        // try 1% as ideal, 2,5,10 with leptons as better resolution than hadrons

        //muon
        if (abs(Part.GetPDG())== 13){ 
        	mass = 0.1057;
        }

        //electron
        else if (abs(Part.GetPDG())== 11){ 
        	mass = 0.000511;
        }

        //muon neutrino
        else if (abs(Part.GetPDG())== 14){ 
        	cout<<"This is a muon neutrino"<<endl;
        }
        //electron neutrino
        else if (abs(Part.GetPDG()) == 12){ 
        	cout<<"This is an electron neutrino"<<endl;
        }
 		//proton
        else if (abs(Part.GetPDG()) == 2212){
        	mass = 0.93827;
        }
        //neutron
        else if (abs(Part.GetPDG()) == 2112){
        	mass = 0.93957;
        }
        //eta
        else if (abs(Part.GetPDG())== 221){
        	mass = 0.54786;
        }
        //lambda
        else if (abs(Part.GetPDG())== 3122){
        	mass = 1.1156;
        }
        //K+/-
        else if (abs(Part.GetPDG())== 321){
        	mass = 0.493677;
        }
        //gamma
        else if (abs(Part.GetPDG())== 22){
        	mass = 0.0;
        }
        //K0 (S)
        else if (abs(Part.GetPDG())== 130){
        	mass = 0.497611; //check if S/L are diff
        }
        //K0 (L)
        else if (abs(Part.GetPDG())== 310){
        	mass = 0.497611;
        }
        //pi0
        else if (abs(Part.GetPDG())== 111){
        	mass = 0.13497;
        }
        //pi+/-
        else if (abs(Part.GetPDG())== 211){
        	mass = 0.13957;
        }

        else {
        	cout<<"Particle type not detected: "<< Part.GetPDG() <<endl;
        }

        //float sig = w; //this makes 1std dev = w
        float sig = w* En; //or 1std dev = w fraction of the original energy

        float En2 = (r0->Gaus(En,sig));
        float pmag2 = sqrt( pow(En,2) - pow(mass,2)); //assuming c= 1
        float px2 = unitx * pmag2;
        float py2 = unity * pmag2;
        float pz2 = unitz * pmag2;
        Particle Part2 = Particle(Part.GetPDG(), px2, py2, pz2, En2, Part.GetID()); 
		PartDet.push_back(Part2);
	}			                        					
return (PartDet);

}
