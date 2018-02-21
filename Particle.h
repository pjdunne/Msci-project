#pragma once
#include "TObject.h"
#include <iostream>
#include <string>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include <vector>
using namespace std;
class Particle: public TObject
{
    public:
  
        int pdgid;
        float threshold;
        float eff;
        float Px;
        float Py;
        float Pz;
        float Energy;
		int Id;
        Particle();  
        Particle(int pdg, float px, float py, float pz, float energy, int id);
		~Particle();
		float GetEnergy();
		int GetPDG();
};
