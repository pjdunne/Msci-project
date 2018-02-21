#include "Particle.C"
#include "Linkdef.h"

int plotting(){
   Particle part;
  TFile* file = new TFile("/home/hep/al3614/neutrinoproject3/newfile.root");
  TTree* tree = (TTree*)file->Get("newtree");
  //vector<Particle> *DetectedParticles = part.Threshold(PartVec, 0.5);
  vector<float> EVec = part.Threshold(0.7, tree);   
 
  TH1D* hE = new TH1D("hE", "Energy", 100, 0, 5);
  
  for (unsigned int i=0;i< EVec.size();i++){
         float E = EVec[i];
 	 hE->Fill(E);
  }
  
 cout<<EVec.size();
 cout<<"random component"<<EVec[30];
  TCanvas *c = new TCanvas("c", "Energy Plot");
  hE->Draw();
  return(0);
}
