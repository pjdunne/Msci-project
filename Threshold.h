#include "Particle.h"
#include "Particle.C"
class Threshold: public TObject
{
    public:
  
    
       

        Threshold();  
        vector<Particle> ThreshFunc(vector<Particle> PartVec);
	~Threshold();
};