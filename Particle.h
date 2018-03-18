#pragma once

#ifndef Particle_H
#define Particle_H

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
	   
        Particle();  
        Particle(int pdg, float px, float py, float pz, float energy, int id);
	~Particle();
	float GetEnergy();
	int GetPDG();
	float GetXMom();
	float GetYMom();
	float GetZMom();
	float GetMomMag();
    int GetID();

};

#endif
