

#ifndef PROPERTIES._H_
#define PROPERTIES_H_
#include <iostream>
#include<stdint.h>
#include <sstream>
#include <string>
#include <cmath>

/*
numbers for main calculations are 32bit
and in fixed-point number representation  
fraction_bit define how many bits are for fractional part
Exp: if fraction_bits = 24 then the integer part will be 8 bit 
*/
#define fraction_bits 24
#define one pow(2,fraction_bits)
#define two one*2
#define six one*6



using namespace std;
class properties {

public:


	
	int number_of_inputs, number_of_mffunc,number_of_rules,data_len;

	// variables to hold permsize and consequences arrays size 
	int consequences_size, premises_size;



	properties(){
		 

		number_of_inputs = 0, number_of_mffunc = 0, number_of_rules=0, data_len=0;
		

		// getting some important variables from user 

		cout << "enter number of inputs[default=4]:";

		number_of_inputs = 4;
		std::string input;
		std::getline(std::cin, input);
		if (!input.empty()) {
			std::istringstream stream(input);
			stream >> number_of_inputs;
		}

		cout << "number of input set to :" << number_of_inputs << endl;

		//cin >> number_of_inputs;

		cout << "enter number of membership functions[default=2]:";

		number_of_mffunc = 2;
		//std::string input;
		std::getline(std::cin, input);
		if (!input.empty()) {
			std::istringstream stream(input);
			stream >> number_of_mffunc;
		}

		cout << "number of membership set to :" << number_of_mffunc << endl;

		//cin >> number_of_mffunc;




		cout << "enter number of ruls [default=pow(number_of_mffunc, number_of_inputs)]:";

		number_of_rules = pow(number_of_mffunc, number_of_inputs);
		//std::string input;
		std::getline(std::cin, input);
		if (!input.empty()) {
			std::istringstream stream(input);
			stream >> number_of_rules;
		}

		cout << "number of number_of_rules set to :" << number_of_rules << endl;


		cout << "enter data length[default=297]:";


		data_len = 297;
		//std::string input;
		std::getline(std::cin, input);
		if (!input.empty()) {
			std::istringstream stream(input);
			stream >> data_len;
		}

		cout << "data length set to :" << data_len << endl;


		// pleas refer to ANFIS documentation
		consequences_size = number_of_rules * (number_of_inputs + 1);
		premises_size = number_of_inputs * number_of_mffunc * 2;



	}
};





#endif
