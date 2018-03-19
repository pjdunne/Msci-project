#include <iostream>
#include <cmath> 

#include <ctime>

int main(){
	
	srand(time(0));
	float number= 0.;  //start with a value less than 20000

	for (unsigned int count= 0; count < 5; count++)
      	{
      	number = ((double)rand()/ (RAND_MAX));  
      	std:: cout << "number  " << number << std::endl;
     	}
  
    
    //cout<< "Hi" << endl;

    return 0;
}