#define _CRTDBG_MAP_ALLOC  

#define BUFSIZE 4096
//#define _BSD_SOURCE



#include <stdlib.h>  
#include <sys/time.h>
#include <stdint.h>
#include <cassert>
#include <iostream>
#include <exception>
#include <new>
#include <stdlib.h> 
#include <cmath>
#include <ctime>
#include <fstream>
#include <chrono>
#include<random>
#include <iterator>
#include <sstream>

//#include "properties.h"
#include "anfis.h"
#include <cstring>
//#include <Windows.h>




unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

// random uniform distributions 

std::default_random_engine Sgen(seed);
std::uniform_int_distribution<int> Signdist(0, 1);
std::default_random_engine randgen(seed);





int main(void) {

	float RMSE = 0;

	int zero_or_one, sign;
	
	int min_value, max_value;
	int consequences_size, premises_size;
	int *consequences, *premises;

	// properties class
 	properties p1;

 	consequences_size = p1.consequences_size;
 	premises_size = p1.premises_size;

 	consequences = new int32_t[consequences_size];
	premises = new int32_t[premises_size];
	memset(consequences, 0, 4 * consequences_size);  // array is 32 bit so we need to multiply size to 4 
	memset(premises, 0, 4 * premises_size);

	// caret random numbers for premise values 

	min_value = 0.01*one; // according to properties.h file one is equal to pow(2,fraction_bits) 
	max_value = 1*one;

	// caret random numbers for premise values 
	std::uniform_int_distribution<int> randdist(min_value, max_value);

	/* we assumed premise parameters order according to mentioned paper
	   premises = [cente1r , center 2, ..... Sigma, sigma, sigma,....]

	   for consequence parameters :
	   consequences = [L01, L11, L21, L31, L41, L02, L12, L22, L32, L42....]

	   first the linear parameters for node number one and then linear 
	   parameters for node number 2 and so on..

	   we arranged parameters like this because it is convenient for randomized evolutionary algorithms
	   like genetic and PSO. there is an example of genetic algorithm in mentioned paper.

	*/

		for (int i = 0; i < premises_size; ++i) {
		
			sign = 1;
			zero_or_one = Signdist(Sgen);
			sign *= zero_or_one ? (1) : (-1); //  in last 3 lines we are trying to generate a random sign
			premises[i] = sign*randdist(randgen);

		
	}

			for (int i = 0; i < consequences_size; ++i) {
		
			sign = 1;
			zero_or_one = Signdist(Sgen);
			sign *= zero_or_one ? (1) : (-1); //  in last 3 lines we are trying to generate a random sign
			consequences[i] = sign*randdist(randgen);

		
	}


	loaddata data(p1);

	ANFIS fis1(p1, data.X,data.Y);

	RMSE = (fis1.outmflayer(consequences, premises))/one;
	cout << "RMSE :" << RMSE << endl;

	//system("pause");

return 0;

}
