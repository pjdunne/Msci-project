class Resolution: public TObject
{
    public:
  
    
       

        Resolution();  
        vector<Particle> ResFunc(vector<Particle> PartVec, float w);
	~Resolution();
};