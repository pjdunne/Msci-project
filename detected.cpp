//
//  detected.C
//  This program writes a vector of detected particles to a ttree file.
//
//  Created by Anisha Kadri on 15/02/2018.

#include "Particle.h"
#include "Particle.C"
#include "Linkdef.h"
#include "TTree.h"
#include "TFile.h"
#include "TBrowser.h"
#include "TROOT.h"
#include "TSystem.h"
#include <vector>

int detected(){
 
  //Variables
  vector<Particle> *PartVec;
  vector<Particle> *DetVec;


  //Reading tree of true particles
  TFile* file = new TFile("newfile.root");
  TTree* tree = (TTree*)file->Get("newtree");

  TBranch *particlesBranch;  
  tree->SetBranchAddress("particles",&PartVec);

  //Creating detected tree 
  TFile newfile("detected.root","RECREATE","A new file to store the particle tree"); 
  TTree* newtree;
  newtree = new TTree("newtree","A tree to store all particles");
  newtree->Branch("particles","vector<Particle>",&detparts);

  //writing to new tree
  for(unsigned int iEntry=0;iEntry< tree->GetEntries();iEntry++){
        
      tree->GetEntry(iEntry);
        
      for(int i=0;i < PartVec[0].size();i++){
        Particle Part = PartVec[0][i];
        En=Part.GetEnergy();
        
        float r = ((double) rand() / (RAND_MAX));
        if (En >= Thresh | r<Eff){
          detparts->push_back(Part); //this should result in a smaller vector of detected particles
      newtree->Fill();


    detparts->clear(); //what effect does this have on the written tree?
  }
  newfile.Write();
  return 0;
}
