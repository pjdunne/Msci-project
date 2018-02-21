#include "Particle.h"
#include "Particle.C"
class Threshold: public TObject
{
    public:
  
    
       

        Threshold();  
        vector<float> ThreshFunc(vector<Particle> PartVec, float threshold);
	~Threshold();
};