


#ifndef LOADDATA_H_
#define LOADDATA_H_

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
#include "properties.h"
#include<stdint.h>
#include <string>
#include <cstring>
#include <algorithm>  
#include <array> 
#include <vector>       // std::vector     
#include <cstdlib> 
#define _USE_MATH_DEFINES
#include<math.h>
#include <cassert>

using namespace std;
class loaddata {

public:
	
	int number_of_inputs, data_len,test_len;
	int32_t *X;
	int32_t *Y;

	
	

	loaddata(const properties& p)
	{

		number_of_inputs = p.number_of_inputs;
		data_len = p.data_len;
		

		X = new (std::nothrow) int32_t[(data_len)*number_of_inputs];
		if (X == nullptr)
			std::cout << "Error: memory could not be allocated";
		else {
			memset(X, 0, 4 * ((data_len)*number_of_inputs));
		}




		Y = new int32_t[data_len];
		memset(Y, 0, 4 * (data_len));

	}



public:
	void insert_data(void);


};



#endif
