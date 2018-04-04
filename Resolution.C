#include "TRandom3.h"
#include <cmath> 
#include <random>
#include <chrono>

vector<Particle> resolution(vector<Particle> PartVec, float w){
  vector<Particle> PartDet;
  PartDet.clear();
  for(unsigned int i=0;i < PartVec.size();i++){
    
    Particle Part = PartVec[i];
    
    float En=Part.GetEnergy();	
    float px=Part.GetXMom();
    float py=Part.GetYMom();
    float pz=Part.GetZMom();
    float pmag = Part.GetMomMag();
    float unitx = px/pmag;
    float unity = py/pmag;
    float unitz = pz/pmag;
    float mass = 0. ; //in units of GeV/ c^2
    float w = 0.;

    // NEW: assigned diff resolutions for each particle - w reassigned in loop
    //changed lepton width to 2%, CHARGED hadron (e.g. p) to 5%, NEUTRAL to 10%
    // However if we are using all the detectors which measure energy deposition,
    // not just the TPCs
    // Its hard to model their cumulative resolution with a simple estimation
    
    //muon
    if (abs(Part.GetPDG())== 13){ 
      mass = 0.1057;
      w = 0.02;
    }
    
    //electron
    else if (abs(Part.GetPDG())== 11){ 
      mass = 0.000511;
      w = 0.02;
    }
    
    //muon neutrino
    else if (abs(Part.GetPDG())== 14){ 
      //cout<<"This is a muon neutrino"<<endl;
      w = 0.02;
    }
    //electron neutrino
    else if (abs(Part.GetPDG()) == 12){ 
      //cout<<"This is an electron neutrino"<<endl;
      w = 0.02;
    }
    //proton
    else if (abs(Part.GetPDG()) == 2212){
      mass = 0.93827;
      w = 0.05;
    }
    //neutron
    else if (abs(Part.GetPDG()) == 2112){
      mass = 0.93957;
      w = 0.1;
        }
    //eta
    else if (abs(Part.GetPDG())== 221){
      mass = 0.54786;
      w = 0.1;
    }
    //lambda //check charge
    else if (abs(Part.GetPDG())== 3122){
      mass = 1.1156;
      w = 0.1;
    }
    //K+/-
    else if (abs(Part.GetPDG())== 321){
      mass = 0.493677;
      w = 0.05;
    }
    //gamma
    else if (abs(Part.GetPDG())== 22){
      mass = 0.0;
      w = 0.02;
    }
    //K0 (S)
    else if (abs(Part.GetPDG())== 130){
      mass = 0.497611; //check if S/L are diff
      w = 0.1;
    }
    //K0 (L)
    else if (abs(Part.GetPDG())== 310){
      mass = 0.497611;
      w = 0.1;
    }
    //pi0
    else if (abs(Part.GetPDG())== 111){
      mass = 0.13497;
      w = 0.1;
    }
    //pi+/-
    else if (abs(Part.GetPDG())== 211){
      mass = 0.13957;
      w = 0.05;
    }
    
    else {
      cout<<"Particle type not detected: "<< Part.GetPDG() <<endl;
    }
    
    //float sig = w; //this makes 1std dev = w
    float sig = w* En; //or 1std dev = w fraction of the original energy
    

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution (En,w);
    float En2 =  distribution(generator);

    
    float pmag2 = sqrt( pow(En,2.0) - pow(mass,2.0)); //assuming c= 1      //should En be En2 here????
    float px2 = unitx * pmag2;
    float py2 = unity * pmag2;
    float pz2 = unitz * pmag2;
    Particle Part2 = Particle(Part.GetPDG(), px2, py2, pz2, En2, Part.GetID(), Part.GetTrand()); 
    PartDet.push_back(Part2);
  }			                        					
  return (PartDet);
  
}
© 2018 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub
API
Training
Shop
Blog
About
