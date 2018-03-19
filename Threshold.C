
float Sigmoid(float pz, float momThresh, float Eff){
  return Eff/(1+exp(-((5*(pz-momThresh)))));
}
    
vector<Particle> threshold(vector<Particle> PartVec, float prot_thresh, float neutron_thresh, float pi_pm_thresh, float pi0_thresh, float Eff){

  vector<Particle> PartVecAbove;
  PartVecAbove.clear();
  float pmag;
  int pdg;
    
  for(unsigned int i=0;i < PartVec.size();i++){
    Particle Part = PartVec[i];
    pmag=Part.GetMomMag();
    pdg = Part.GetPDG();
    
    float r = ((double) rand() / (RAND_MAX));
        
    if (pdg == 111 && r < Sigmoid(pmag,pi0_thresh,Eff)){
      PartVecAbove.push_back(Part);
    }
    else if (abs(pdg) == 211 && r < Sigmoid(pmag,pi_pm_thresh,Eff)){
      PartVecAbove.push_back(Part);
    }
    else if (abs(pdg) == 2212 && r < Sigmoid(pmag, prot_thresh,Eff)){
      PartVecAbove.push_back(Part);
    }
    else if (abs(pdg) == 2112 && r< Sigmoid(pmag, neutron_thresh, Eff)){
      PartVecAbove.push_back(Part);
    }
    else if (abs(pdg) != 111 && abs(pdg) != 211 && abs(pdg) != 2212 && abs(pdg) != 2112 && abs(pdg) != 12 && abs(pdg) != 14 && r < Sigmoid(pmag, 0, Eff)) {
      PartVecAbove.push_back(Part);     
    }
    
  }
  
  return (PartVecAbove);
} 

vector<Particle> liquidMomThresh(vector<Particle> PartVec){
	
  float prot_thresh = 0.2; //2212
  float neutron_thresh = 4.0; //2112
  float pi_pm_thresh = 0.059; // +/-211
  float pi0_thresh = 0.059; //111
  float Eff = 0.90; //Efficiency
  
  return threshold(PartVec, prot_thresh, neutron_thresh, pi_pm_thresh, pi0_thresh, Eff);
  
}

vector<Particle> gasMomThresh(vector<Particle> PartVec){
	
  float prot_thresh = 0.058; //2212
  float neutron_thresh = 4.; //2112
  float pi_pm_thresh = 0.016; // +/-211
  float pi0_thresh = 0.016; //111
  float Eff = .90; //Efficiency

  return threshold(PartVec, prot_thresh, neutron_thresh, pi_pm_thresh, pi0_thresh, Eff);
}
