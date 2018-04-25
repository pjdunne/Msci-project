#include "Event.h"

Event::Event()
{
  int id = 0;
  float E0 = 0.; //true Energy
  float ECL  = 0.; //Reconstructed Calorimetric Energy, Liquid
  float ECG = 0.; //Reconstructed Calorimetric Energy, Gas
  float EKL = 0.; //Reconstructed Kinematic Energy, Liquid
  float EKG = 0.; //Reconstructed Kinematic Energy, Gas
  int nfsp0 = 0; //True nfsp
  int nfspL = 0; //nfsp after Liquid threshold
  int nfspG = 0; //nfsp after Gas threshold
  int mode = 0; //mode
  int topL = 0; //Liq topology
  int topG = 0; //Gas topology
  
}

Event::Event(int id, float E0, float ECL, float ECG, float EKL, float EKG, int nfsp0, int nfspL, int nfspG, int mode, int topL, int topG);
{
  int id = id;
  float E0 = E0; 
  float ECL  = ECL; 
  float ECG = ECG; 
  float EKL = EKL; 
  float EKG = EKG; 
  int nfsp0 = nfsp0; 
  int nfspL = nfspL; 
  int nfspG = nfspG;
  int mode = mode; 
  int topL = topL; 
  int topG = topG; 
}

Event::~Event(){}


int Event::Getid(){
  return (id);
}

float Event::GetE0(){
  return (E0);
}

float Event::GetECL(){
  return (ECL);
}

float Event::GetECG(){
  return (ECG);
}

float Event::GetEKL(){
  return (EKL);
}

float Event::GetEKG(){
  return (EKG);
}

int Event::Getnfsp0(){
  return (nfsp0);
}

int Event::GetnfspL(){
  return (nfspL);
}

int Event::GetnfspG(){
  return (nfspG);
}

int Event::Getmode(){
  return (mode);
}

int Event::GettopL(){
  return (topL);
}

int Event::GettopG(){
  return (topG);
}




