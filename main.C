#include "Particle.h"
#include "Particle.C"
#include "Linkdef.h"
#include "TTree.h"
#include "TFile.h"
#include "TBrowser.h"
#include "TROOT.h"
#include "TSystem.h"
#include <vector>

using namespace std;


int main(){

  vector<Particle> *fsp;   //vector of final state particles. Will only hold final state particles of one event at a time.
  int particleID = 0;      //Unique for each particle.
 
  //Variables from tree
  int nfsp;                //number of final state particles
  int pdg[240];
  float px[240];
  float py[240];
  float pz[240];
  float energy[240];
  int mode;
  float Enu_t;
  float coslep;
  float Enu_r;
  float E_diff;

  //Read in tree
  TFile* file = new TFile("/home/hep/pjd12/public_html/teaching/mastersproject17-18/T2K_Ar_numu_fhc_trunk07_Eshita_merge_flat_v3.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);
  //tree->SetBranchAddress("",&Enu_t);  Edit when new tree given
  tree->SetBranchAddress("CosLep",&coslep);

  //Create new tree 
  TFile newfile("newfile.root","RECREATE","A new file to store the particle tree");
  TTree* newtree;
  newtree = new TTree("newtree","A tree to store all particles");
  newtree->Branch("particles","vector<Particle>",&fsp);

  for(unsigned int iEntry=0;iEntry<tree->GetEntries();iEntry++){
    tree->GetEntry(iEntry);
    for(int iVecEntry=0;iVecEntry<nfsp;iVecEntry++){
      particleID++;
      fsp->push_back(Particle(pdg[iVecEntry],px[iVecEntry],py[iVecEntry],pz[iVecEntry],energy[iVecEntry],particleID));
      	
      newtree->Fill();
    }
    fsp->clear();
  }
  newfile.Write();


 // 
  return 0;
}
