
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
return (Energy);}

float Particle::GetPx(){
return (Px);}

float Particle::GetPy(){
return (Py);}

float Particle::GetPz(){
return (Pz);}

void Particle::SetEnergy(float E){
	Energy = E;}

void Particle::SetPx(float x){
	Px = x;}
void Particle::SetPy(float y){
	Py = y;}
void Particle::SetPz(float z){
	Pz = z;}

int Particle::GetPDG(){
return (pdgid);}

float Particle::GetMomentum(){
return (sqrt(pow(Px,2)+pow(Py,2)+pow(Pz,2)));}

int Particle::GetID(){
  return Id;
  
}

float maxi(vector<float> Vec){
float Max=0;
for (unsigned int i = 0; i < Vec.size(); i++)
  if (Vec[i] > Max)
    Max = Vec[i];

return Max;}