#include "Particle.h"

Particle::Particle(int pdg, float px, float py, float pz, float energy){
    this->pdgid = pdg;
    this->threshold = 0.7;
    this->eff = 0.7;
    this->px = px;
    this->py = py;
    this->pz = pz;
    this->energy = energy;
}
