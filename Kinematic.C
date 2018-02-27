#include "constants.h"
#include "Kinematic.h"
#include <math.h> 

Kinematic::Kinematic()
{
  float threshold = 0.05;
}

float Kinematic::KinFunc(vector<Particle> PartVec, float coslep)
{

  float E_kin;
  float Elep;
  float Plep;
  
  vector<Particle> PartVecAbove;
  PartVecAbove.clear();

  for (unsigned int i=0;i<PartVec.size();i++){
  Particle Part = PartVec[i];
  int pdg = Part.GetPDG();

  if(pdg==11||pdg==13){
    Elep = Part.GetEnergy();
    Plep = sqrt(pow(Part.GetXMom(),2)+pow(Part.GetYMom(),2)+pow(Part.GetZMom(),2));
  }
      
  E_kin = (pow(mproton,2.0)-pow(mneutron,2.0)-pow(mmuon,2.0)+(2.0*Elep*mneutron))/(2.0*(mneutron-Elep+(Plep*coslep)));
  }

  return E_kin;
  
}

Kinematic::~Kinematic(){}
      
