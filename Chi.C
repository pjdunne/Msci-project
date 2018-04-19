double Chi(TH1D* N, TH1D* G){
double chi_squared_total=0;
for (int i = 0; i < N->GetXaxis()->GetNbins()+1; ++i) {
    // N_Pmu is here the MC proton multiplicity distribution from NEUT
    double mc_content = N->GetBinContent(i+1);

    // nPrG is here_data is the MC proton multiplicity distribution from GENIE
    double data_content = G->GetBinContent(i+1);
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);
    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
    if (mc_content !=0 && data_content !=0){
    double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
    chi_squared_total = chi_squared_total + chi2;}
}


return chi_squared_total/100;}