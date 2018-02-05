#ifndef PARTICLE_H
#define PARTICLE_H

class Particle{
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
};

#endif
