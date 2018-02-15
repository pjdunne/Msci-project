//
//  calreader.c
//  This reconstructs the energy for elastic events and produces a histogram.
//
//  Created by Anisha Kadri on 31/01/2018.
//
//
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1F.h"
#include <vector>
#include <string>

void calreader(){
    
    std::string filename = "/Users/AnishaKadri/Desktop/cresources/Eshita_flat_v3.root";
    TFile* file=new TFile(filename.c_str());
    TTree* tree=(TTree*)file->Get("FlatTree_VARS");
    TH1F     *hE_part;
    
    
    int nfsp; //Number of final state particles
    int mode; //mode of decay
    float px_vec [200];
    float E_part [200];
    int pdg [200]; // error given here: The pointer type given "Float_t" (5) does not correspond to the type needed "Int_t" (3) by the branch: pdg ??
    
    
    tree->SetBranchAddress("nfsp",&nfsp);
    tree->SetBranchAddress("Mode", &mode);
    tree->SetBranchAddress("px",px_vec);
    tree->SetBranchAddress("E" , E_part);
    tree->SetBranchAddress("pdg", pdg);
    
    // create the TH1F histogram
    hE_part = new TH1F("GeV", "Reconstructed Energy (Calorimetric)", 100, 0, 10);
    // enable bin errors:
    hE_part->Sumw2();
    
    for (int iEntry = 0; iEntry < tree->GetEntries(); iEntry++) {
    //for (int iEntry = 0; iEntry < 10; iEntry++) {
        
        tree->GetEntry(iEntry);
        float E_cal = 0;
        
        //mode selection: elastic & single pi
        if(mode==1 || mode==2 || mode==11 || mode==12 || mode==13){
            //std::cout<< "nfsp" << nfsp<< std::endl;
            
            for(int iVecEntry =0; iVecEntry < nfsp;iVecEntry++){
                if(pdg[iVecEntry] == 2212 || pdg[iVecEntry] == 2112){
                    E_cal += (E_part[iVecEntry] - 0.9382);
                }
                
                else
                {
                    E_cal += E_part[iVecEntry];
                }
                //std::cout<< "particle type" << pdg[iVecEntry]<< "Energy"<<E_part[iVecEntry] << std::endl;
            //hE_part->Fill(E_part[iVecEntry]);
            }
            hE_part->Fill(E_cal);
        }
    }
    
    // Fit the histogram:
    //hE_part->Fit("pol2");
    // and draw it:
    hE_part->Draw("HIST");
}