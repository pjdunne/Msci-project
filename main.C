#include "Particle.h"
#include "Particle.C"

int main(){
  
  TFile* file = new TFile("Eshita2.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  int nfsp; //number of final state particles
  int pdg[24];
  float px[24];
  float py[24];
  float pz[24];
  float energy[24];
  int mode;
  float Enu_t;
  float coslep;
  float Enu_r;
  float E_diff;

  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);
//tree->SetBranchAddress("",&Enu_t);  Edit when new tree given
  tree->SetBranchAddress("CosLep",&coslep);

  //vector<Particle> *a; //vector
  Particle *a;
 
//Creating new tree
  TFile newfile("newfile.root","RECREATE","A new file to store the particle tree");
  TTree* newtree;
  newtree = new TTree("newtree","A tree to store all particles");
  newtree->Branch("particles","Particle",&a);

  int particleID = 0;
  for(unsigned int iEntry=0;iEntry<200000;iEntry++){
    tree->GetEntry(iEntry);
    for(int iVecEntry=0;iVecEntry<nfsp;iVecEntry++){
      particleID++;
      //a->push_back(Particle(pdg[iVecEntry],px[iVecEntry],py[iVecEntry],pz[iVecEntry],energy[iVecEntry],particleID));   //vectors
      a->pdgid = pdg[iVecEntry];
      a->Px = px[iVecEntry];
      a->Py = py[iVecEntry];
      a->Pz = pz[iVecEntry];
      a->Energy = energy[iVecEntry];
      a->Id = particleID;
      newtree->Fill();
    }
    //a->clear();   //vector
  }
  newfile.Write();
  return 0;
}
