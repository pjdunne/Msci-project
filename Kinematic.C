#include "constants.h"
#include <math.h> 

float kinematic(vector<Particle> PartVec, float coslep)
{

  float E_kin=0;

  float Elep;
  float Plep;
  float m;
  for (unsigned int i=0;i<PartVec.size();i++){
    Particle Part = PartVec[i];
    int pdg = Part.GetPDG();

    if(pdg==13 | pdg==11){
      Elep = Part.GetEnergy();
      Plep = Part.GetMomentum(); 
      float m = mmuon;
    }

  }    
  if(Elep != 0 && Plep !=0){
   E_kin = (pow(mproton,2.0)-pow(mneutron,2.0)-pow(mmuon,2.0)+(2.0*Elep*mneutron))/(2.0*(mneutron-Elep+(Plep*coslep)));
   return E_kin; 
}
  
 else{ return 0.123;}


}      