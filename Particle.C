#include "Particle.h"

Particle::Particle()
{
  pdgid = 0;
  threshold = 0.7;
  eff = 0.7;
  Px = 0.;
  Py = 0.;
  Pz = 0.;
  Energy = 0.;
  Id = 0;
}

Particle::Particle(int pdg, float px, float py, float pz, float energy, int id)
{
    pdgid = pdg;
    threshold = 0.7;
    eff = 0.7;
    Px = px;
    Py = py;
    Pz = pz;
    Energy = energy;
    Id = id;
}

Particle::~Particle(){}


float Particle::GetEnergy(){
  return (Energy);
}

int Particle::GetPDG(){
  return (pdgid);
}

float Particle::GetXMom(){
  return Px;
}

float Particle::GetYMom(){
  return Py;
}

float Particle::GetZMom(){
  return Pz;
}

float Particle::GetMomMag(){
  return sqrt(pow(Px,2.0)+pow(Py,2.0)+pow(Pz,2.0));
}
