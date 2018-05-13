double Chi(TH1D* N, TH1D* G, int bin){
double chi_squared_total=0;
int b = bin;
double c1=0;
double c2=0;
vector<double> chivec;	
for (int i = 0; i < N->GetXaxis()->GetNbins()+1; ++i) {
    double mc_content = G->GetBinContent(i+1);
    double data_content = N->GetBinContent(i+1);
    
    // Set the error to be the square root of the bin content in one bin (Poisson errors)
    double error = sqrt(mc_content);

    // Calculate a chi2 assuming the probability distribution function is a Gaussian
    //double chi2 = (data_content - mc_content)^2/(error^2);
    // Calculate a chi2 assuming the probability distribution function is a Poisson
   
       // if (mc_content > 0 && data_content > 0){ 
    	if (mc_content + c1 < 200 | data_content + c2 < 200){
    	//if ((data_content+c2)/(mc_content+c1) > 100){

   		b=b-1;
		c1=c1+mc_content;
		c2=c2+data_content;}
			
   	 else{
		
		if(c1 > 0 | c2 >0){
		mc_content=mc_content+c1;	
		data_content=data_content+c2;}


   		double chi2 = mc_content-data_content+data_content*log(data_content/mc_content);
		chivec.push_back(chi2);
    		chi_squared_total = chi_squared_total + chi2;
		c1 =0;
		c2=0;}

    }
   
//cout<<"b:"<<" "<<b<<endl;
//cout<<"last chi2:"<<" "<<chivec[-1]<<endl;
return chi_squared_total/b;}
