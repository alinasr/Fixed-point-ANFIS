

#ifndef ANFIS_H_
#define ANFIS_H_

#include <iostream>
#include <exception>
#include <new>
#include <stdlib.h> 
#include <cmath>
#include <ctime>
#include <fstream>
#include <memory>
#include <iterator>
#include <sstream>
#include <cstring>
#include <cassert>
#include "loaddata.h"

using namespace std;


// defining macro functions for fixed point number representation

#define mult(ans,a,b) ans=((int64_t)a*(int64_t)b)>>fraction_bits
#define divide(ans,a,b) ans=((int64_t)a<<fraction_bits)/b
#define div2(a,b) (((int64_t)a<<fraction_bits)/b)
#define pow2(ans,a) ans=((int64_t)a*(int64_t)a)>>fraction_bits 
#define fixsqrt(a) (sqrt((int64_t)a<<fraction_bits))
#define p2(a) (int64_t)((int64_t)a*(int64_t)a)>>fraction_bits
#define p4(a) p2(p2(a))
#define intpow(a,b) ((int64_t)pow(a,(b>>fraction_bits)))>>((b>>fraction_bits) - 1)*fraction_bits
#define gussM(x,sig,c) (div2((p2(sig)),((p2(sig)) +(p2((x-c))))))

// the worst cost value possible for 32 bit integer  
#define worst_cost 2147483646



// define ANFIS class


class ANFIS {
private:

	int32_t *rule_list,*address;

public:
	// to store target value to compare with calculated  value
	int *X, *Target;

	// ANFIS network numbers of inputs, numbers og membershipe function, number of rules
	int number_of_inputs, number_of_mffunc,number_of_rules;
	int nods,data_len;  // number of nodes in each layer of ANFIS except  first layer
	int member_layer,function_layer;  // 
	                                    

	ANFIS(const properties& p, int32_t *x , int32_t *y) {

		X = x;
		Target = y;

		// saving the adress of start point for input pointer 
		address = X;

		data_len = p.data_len;

		number_of_inputs = p.number_of_inputs;
		number_of_mffunc = p.number_of_mffunc;
		number_of_rules = p.number_of_rules;


		
		member_layer = number_of_mffunc*number_of_inputs;   
		nods = number_of_rules;
		function_layer = (number_of_inputs + 1)*nods;



		//declare rule_list matrix................................................................
		rule_list = new (std::nothrow) int32_t[nods*number_of_inputs];
		if (rule_list == nullptr)
			std::cout << "Error: memory could not be allocated";
		else 
				memset(rule_list, 0, 4 * nods*number_of_inputs);
	
		


		//creating rule list......................................

		for (int i = 0; i < nods; ++i) {
			int temp;
			temp = i;
			for (int j = 0; j < number_of_inputs; ++j) {

				rule_list[i*(number_of_inputs) + j] = (temp%number_of_mffunc) + number_of_mffunc*(number_of_inputs - 1 - j);

				temp = temp / number_of_mffunc;

			}

		}

		



	}
private:
	int32_t gaussmf(int32_t x, int32_t c, int32_t sig);
	int gaussmf2(int32_t x, int32_t sig, int32_t c);

	
public:

	int32_t outmflayer(int32_t *consequences, int32_t *premises);


};

#endif
