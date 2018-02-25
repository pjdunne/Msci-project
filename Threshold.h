class Threshold: public TObject
{
    public:
  
    
       

        Threshold();  
        vector<Particle> ThreshFunc(vector<Particle> PartVec, float th);
	~Threshold();
};