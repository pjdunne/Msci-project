TFile* file = new TFile("Eshita2.root");
TTree* tree = (TTree*)file->Get("FlatTree_VARS");

int nfsp; //number of final state particles
int pdg[24];
float px[24];
float py[24];
float pz[24];
float energy[24];
int mode;
float Enu_t;
float costhetalep;
float Enu_r;
float E_diff;

tree->SetBranchAddress("nfsp",&nfsp);
tree->SetBranchAddress("pdg",&pdg);
tree->SetBranchAddress("px",&px);
tree->SetBranchAddress("py",&py);
tree->SetBranchAddress("pz",&pz);
tree->SetBranchAddress("E",&energy);
tree->SetBranchAddress("Mode",&mode);
tree->SetBranchAddress("Enu_QE",&Enu_t);
tree->SetBranchAddress("CosLep",&costhetalep);

for(unsigned iEntry=0;iEntry<tree->GetEntries();iEntry++){
  tree->GetEntry(iEntry);
  for(int iVecEntry=0;iVecEntry<nfsp;iVecEntry++){
    Particle a = new Particle(pdg[iVecEntry],px[iVecEntry],py[iVecEntry],pz[iVecEntry],energy[iVecEntry]);
