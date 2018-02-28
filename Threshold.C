
vector<Particle> threshold(vector<Particle> PartVec, float prot_thresh, float pi_pm_thresh, float pi0_thresh, float Eff){

  vector<Particle> PartVecAbove;
  PartVecAbove.clear();
  float pz;

  for(unsigned int i=0;i < PartVec.size();i++){

    Particle Part = PartVec[i];
    pz=Part.GetZMom();	
    float r = ((double) rand() / (RAND_MAX));

    if (Part.GetPDG() == 111 && pz > pi0_thresh && r <Eff){
      PartVecAbove.push_back(Part);			
    }
    else if ((Part.GetPDG() == 211 || Part.GetPDG() == -211) && pz > pi_pm_thresh && r <Eff){
      PartVecAbove.push_back(Part);
    }
    else if (Part.GetPDG() == 2212 && pz > prot_thresh && r <Eff){
      PartVecAbove.push_back(Part);
    }
    else if (r<Eff){
      PartVecAbove.push_back(Part);
    }
  }

  return (PartVecAbove);
} 

vector<Particle> liquidMomThresh(vector<Particle> PartVec){
	
  float prot_thresh = .9; //2212
  float pi_pm_thresh = 0.059; // +/-211
  float pi0_thresh = .059; //111
  float Eff = .99; //Efficiency
  
  return threshold(PartVec, prot_thresh, pi_pm_thresh, pi0_thresh, Eff);
  
}


vector<Particle> gasMomThresh(vector<Particle> PartVec){
	
  float prot_thresh = .059; //2212
  float pi_pm_thresh = 0.016; // +/-211
  float pi0_thresh = .016; //111
  float Eff = .99; //Efficiency

  return threshold(PartVec, prot_thresh, pi_pm_thresh, pi0_thresh, Eff);
}

 




