float NL = 4.6276 * pow(10,7); 
float NG = 2.995 * pow(10,5);

TH1D* NormL (TH1D h){
Double_t norm = NL;
Double_t scale = norm/(h->Integral());
h->Scale(scale);
return h;}

TH1D* NormG (TH1D h){
Double_t norm = NG;
Double_t scale = norm/(h->Integral());
h->Scale(scale);
return h;}