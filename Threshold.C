#include <TRandom3.h>

float Sigmoid(float x, float m, float Eff, float steep){
	return Eff/(1+exp(-(steep*(x-m))));}

vector<Particle> Threshold(vector<Particle> PartVec, float prot_thresh, float neutron_thresh, float mu_thresh, float pi_pm_thresh, float pi0_thresh, float Eff, float steep, int A){
	
	vector<Particle> PartVecAbove;
	PartVecAbove.clear();
	
	for(unsigned int i=0;i < PartVec.size();i++){
		//TRandom *ra = new TRandom3(); 
		//TRandom *ra1 = new TRandom3();
		//TRandom *ra2 = new TRandom3();
		//TRandom *ra3 = new TRandom3();
		//TRandom *ra4 = new TRandom3();
		Particle Part = PartVec[i];
		int pdg = Part.GetPDG();
		if(A==1){
	        float P=Part.GetMomentum();
 	       // double r = ra->Rndm();
		//double r1 = ra1->Rndm();
		//double r2 = ra2->Rndm();
		//double r3 = ra3->Rndm();
		//double r4 = ra4->Rndm();


		float r = ((double) rand() / (RAND_MAX));
		float r1 = ((double) rand() / (RAND_MAX));
		float r2 = ((double) rand() / (RAND_MAX));
		float r3 = ((double) rand() / (RAND_MAX));
		float r4 = ((double) rand() / (RAND_MAX));

   		 if (pdg == 111 && r < Sigmoid(P, pi0_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);			
  		  }
  		 else if (abs(pdg) == 211  && r1 < Sigmoid(P, pi_pm_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2212 && r2 < Sigmoid(P, prot_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2112 && r3 < Sigmoid(P, neutron_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 13 && r2 < Sigmoid(P, mu_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);}
   		 if (pdg != 111 && abs(pdg) != 211 && pdg != 2212 && pdg != 2112 && pdg != 13){
   		   PartVecAbove.push_back(Part);}
		}

		else{
		float P = Part.GetEnergy();
 	        float r = ((double) rand() / (RAND_MAX));
		float r1 = ((double) rand() / (RAND_MAX));
		float r2 = ((double) rand() / (RAND_MAX));
		float r3 = ((double) rand() / (RAND_MAX));
		float r4 = ((double) rand() / (RAND_MAX));

   		 if (pdg == 111 && r < Sigmoid(P, pi0_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);			
  		  }
  		 else if (abs(pdg) == 211  && r1 < Sigmoid(P, pi_pm_thresh, Eff, steep)){
  		    PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2212 && r2 < Sigmoid(P, prot_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 else if (pdg == 2112 && r3 < Sigmoid(P, neutron_thresh, Eff, steep)){
   		   PartVecAbove.push_back(Part);
   		 }
   		 if (pdg != 111 && abs(pdg) != 211 && pdg != 2212 && pdg != 2112){
   		   PartVecAbove.push_back(Part);}
		}

					}
return (PartVecAbove);}


vector<Particle> liquidMomThresh(vector<Particle> PartVec){
  float prot_liq_thresh = .32; //2212
  float neutron_thresh = 4.; //2112
  float pi_pm_thresh = 0.059; // +/-211
  float pi0_thresh = .059; //111
  float Eff = 1.; //Efficiency
  float mu_thresh = 0.05; //13
  float steep = 90.;
  int A=1;
  
  return Threshold(PartVec, prot_liq_thresh, neutron_thresh, mu_thresh, pi_pm_thresh, pi0_thresh, Eff,steep, A);
  
}

vector<Particle> gasMomThresh(vector<Particle> PartVec){
  float prot_gas_thresh = .058; //2212
  float neutron_thresh = 4.; //2112
  float pi_pm_thresh = 0.016; // +/-211
  float pi0_thresh = .016; //111
  float Eff = 1.; //Efficiency
  float mu_thresh = 0.0; //13

  float steep = 90.;
  int A=1;
  return (Threshold(PartVec, prot_gas_thresh, neutron_thresh, mu_thresh, pi_pm_thresh, pi0_thresh, Eff,steep, A));
  
}





