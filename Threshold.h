class Threshold: public TObject
{
    public:
  
    
       

        Threshold();  
        vector<Particle> ThreshFunc(vector<Particle> PartVec, float prot_thresh, float neutron_thresh, float pi_pm_thresh, float pi0_thresh, float Eff, float steep, int A);
	~Threshold();
};
