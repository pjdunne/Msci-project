
int id_0pi(vector<Particle> PartVec){
	int counter = 0;

	for (unsigned int i=0;i<PartVec.size();i++){
    	Particle Part = PartVec[i];
    	int pdg = Part.GetPDG();

    	if (abs(pdg) == 211){
    		counter++;
    	}

    	if (abs(pdg)== 111){
    		counter++;
    	}
    }
    
    if (counter == 0){
    	return 1;
    }else {
    	   return 0;
        }

}

int id_1pi(vector<Particle> PartVec){
	int counter = 0;

	for (unsigned int i=0;i<PartVec.size();i++){
    	Particle Part = PartVec[i];
    	int pdg = Part.GetPDG();

    	if (abs(pdg) == 211){
    		counter++;
    	}

    }
    
    if (counter == 1){
    	return 1;
    }else {
    	return 0;
        }
        
}