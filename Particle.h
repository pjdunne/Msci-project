#ifndef PARTICLE_H
#DEFINE PARTICLE_H

class Particle{
    public:
  
        int pdgid;
        float threshold;
        float eff;
        float px;
        float py;
        float pz;
        float energy;
        //Particle();
        Particle(int pdg, float px, float py, float pz, float energy);
};

#endif
