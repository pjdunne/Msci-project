
float calorimetric(vector<Particle> PartVec){
	
  float En;
  float E_cal;
	
  for(unsigned int i=0;i < PartVec.size(); i++){
    Particle Part = PartVec[i];
	
    En=Part.GetEnergy();	
    int pdg = Part.GetPDG();		
    
    if(pdg == 2212 || pdg == 2112){
      E_cal += (En - 0.9382);
    }
    
    else{
      E_cal += En;
    }
  }
       
return (E_cal);

}
