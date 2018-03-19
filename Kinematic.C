#include "constants.h"
#include <math.h> 

float kinematic(vector<Particle> PartVec, float coslep)
{

  float E_kin=0;
  float Elep=0;
  float Plep=0;
  
  for (unsigned int i=0;i<PartVec.size();i++){
    Particle Part = PartVec[i];
    int pdg = Part.GetPDG();

    if(pdg==11||pdg==13){
      Elep = Part.GetEnergy();
      Plep = Part.GetMomMag(); 
    }
  }    
  if(Elep != 0 && Plep !=0){
    E_kin = (pow(mproton,2.0)-pow(eff_mass_neutron,2.0)-pow(mmuon,2.0)+(2.0*Elep*eff_mass_neutron))/(2.0*(eff_mass_neutron-Elep+(Plep*coslep)));
  }
  
  return E_kin; 
}

/*float kinematic1pi(vector<Particle> PartVec, float coslep)
{
  float E_kin=0;
  float Elep=0;

  for (unsigned int i=0;i<PartVec.size();i++){
    Particle Part = PartVec[i];
    int pdg = Part.GetPDG();

    if(pdg==11||pdg==13){
      Elep = Part.GetEnergy();
    }
  }    
  if(Elep != 0){
    E_kin = (pow(mproton,2.0)-pow(eff_mass_neutron,2.0)-pow(mmuon,2.0)+(2.0*Elep*eff_mass_neutron))/(2.0*(eff_mass_neutron-Elep+(Plep*coslep)));
  }
  
  return E_kin; 
  } */
