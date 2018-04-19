float NL = 1720397.562; 
float NG = 18757.51188;

TH1D* NormL (TH1D* h){
Double_t norm = NL;
Double_t scale = norm/(h->Integral());
h->Scale(scale);
return h;}

TH1D* NormG (TH1D* h){
Double_t norm = NG;
Double_t scale = norm/(h->Integral());
h->Scale(scale);
return h;}
