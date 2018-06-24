

#include "loaddata.h"

using namespace std;


// this fuctions read the data from .csv file
void loaddata::insert_data(void) {


	float *x, *y;

	x = new float[number_of_inputs * data_len];
	y = new float[data_len];

	memset(x, 0, number_of_inputs * data_len);
	memset(y, 0, data_len);


	int i;
	i = 0;

	ifstream infile1;
	string line1;
	infile1.open("data.csv", ifstream::in);
	

	std::string input1;
	std::string input2;
	std::string input3;
	std::string input4;
	std::string output;

	if (infile1.is_open())
	{
		while (i<data_len)
		{

			
			std::getline(infile1, input1, ',');
			std::getline(infile1, input2, ',');
			std::getline(infile1, input3, ',');
			std::getline(infile1, input4, ',');
			std::getline(infile1, output, '\n');

			std::string::size_type sz1;
			x[number_of_inputs * i]     = stof(input1, &sz1);
			x[number_of_inputs * i + 1] = stof(input2, &sz1);
			x[number_of_inputs * i + 2] = stof(input3, &sz1);
			x[number_of_inputs * i + 3] = stof(input3, &sz1);
			y[i] = stof(output, &sz1);
			i++;


		}
		infile1.close();
	}
	else
	{
		cout << "Error opening file";
	}




		// convert floating point data to fixed point data by multiplying to pow(2, fraction_bits)

	for (int i = 0;i < data_len ;++i) {
		Y[i] = y[i] * pow(2, fraction_bits);
	}

	for (int i = 0;i < data_len * number_of_inputs;++i) {
		X[i] = x[i] * pow(2, fraction_bits);
	}




}


