#pragma once


//#ifndef __Particle__
//#define __Particle__
class Particle: public TObject
{
    public:
  
        int pdgid;
        float threshold;
        float eff;
        float Px;
        float Py;
        float Pz;
        float Energy;
	int Id;
	//int Nfsp;
        Particle();  
        Particle(int pdg, float px, float py, float pz, float energy, int id);
	~Particle();
	float GetEnergy();
	int GetPDG();
};

//#endif