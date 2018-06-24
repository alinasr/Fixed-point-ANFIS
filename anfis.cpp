
#include "anfis.h"

using namespace std;


// standard guassian fuction for membership layer

int32_t ANFIS::gaussmf(int32_t x, int32_t sigma, int32_t center) {



	float temp1;
	int32_t temp2;

	temp1 = pow(((float)(x - center) / (float)sigma),2.0);
	
	temp2 = exp(-0.5*temp1)*pow(2, fraction_bits);
	
	return temp2;

	
}
 

// a fast and fully integer approximation for guassian function that

int ANFIS::gaussmf2(int32_t x, int32_t sigma, int32_t center) {
	int64_t temp1, temp2;


	temp1 = sigma;
	temp1 = temp1 << 2;
	temp2 = x;
	temp2 = temp2 - center;
	temp2 = temp2 << 2;
	temp2 = (temp1 <<fraction_bits)/ (temp1 + temp2);

	return temp2;
}




// main function for calculating RMSE for a set of data

int32_t ANFIS::outmflayer(int32_t *consequences, int32_t *premises)
{
	// defining required pointers
	int32_t *Y;
	int64_t *F, *outmf;

	int32_t *UX, *WX, *wbar;
	int64_t total_wights; // its for storing total sum of wieghts to calculate the normalised wights
	int64_t out;
	int64_t error;

	total_wights = 0, out = 0;

	// members ship layer nodes
	UX = new int32_t[member_layer];
	memset(UX, 0, 4 * member_layer);

	// wieghts layer nods
	WX = new int32_t[nods];
	memset(WX, 0, 4 * nods);

	// normailised wieght layer nodes
	wbar = new int32_t[nods];
	memset(wbar, 0, 4 * nods);

	// output layer node
	outmf = new int64_t[nods];
	memset(outmf, 0, 8 * nods);

	// final outputs array
	Y = new int32_t[data_len];
	memset(Y, 0, 4 * data_len);

	// linear functio layer node
	F = new int64_t[nods];
	memset(F, 0, 8 * nods);


	// some temporary valuse that needed in calculation
	int64_t temp;
	int64_t temp2;
	temp = 0, temp2 = 0, error = 0;

/*
 in fixed point calculation the sigma in guasssian fuction shoud'y be less than 4096
 if it is less than 4096 the fuction will be return the worst(biggesst possible) RMSE
 and how we check just sigma in permises array? pleas check the documnation that how organized the 
 this values in arrays in main file and also the mentioned papaer
*/

for(int k = 0; k<(member_layer/2); ++k){

	if (abs(premises[k + number_of_inputs*number_of_mffunc]) < 4096) {
		return worst_cost; 
	}


}

	for (int data = 0; data < data_len; ++data) {

		

		for (int i = 0; i < number_of_inputs; ++i) {
			for (int j = 0; j < number_of_mffunc; j++) {

				// calculating echa nods of first layer(membership layer)
				// note that  sigma = premises[j + i*number_of_mffunc + number_of_inputs*number_of_mffunc]
				// and center  = premises[j + i*number_of_mffunc]
				UX[i*number_of_mffunc + j] = gussM(X[data*number_of_inputs + i], premises[j + i*number_of_mffunc + number_of_inputs*number_of_mffunc], premises[j + i*number_of_mffunc]);


			}
		}

		// calculating function layer expect multyplying final normalised wieghts to these nods
		// pleas refer to how ANFIS work 

		for (int i = 0; i < nods; ++i) {

			F[i] = consequences[i];
		}

		for (int i = 1; i < number_of_inputs + 1; ++i) {

			for (int j = 0; j < nods; ++j) {

				mult(temp, X[data*number_of_inputs + i - 1], consequences[j + i*nods]);
				F[j] += temp;
				
			}
		}

		

		// weight calculation
		// total_wights is for storing total sum of wieghts to calculate the normalised wights

		for (int i = 0; i < nods; ++i) {
			WX[i] =one;
			for (int j = 0; j < number_of_inputs; ++j) {
				int k;

				k = rule_list[i * number_of_inputs + j];

				mult(WX[i], WX[i], UX[k]);


			}
			total_wights += WX[i];
			

		}


		if (total_wights == 0)  // in xase of zerotrap we assign one( in fixed point) to avid zero deivision
			total_wights = one;


		// normalising weights and applying it to functin layer


		for (int i = 0; i < nods; ++i) {


			divide(wbar[i], WX[i], total_wights);

			mult(outmf[i], wbar[i], F[i]);
			out += outmf[i];

		}

	


		Y[data] = out;

		pow2(temp, (Target[data] - Y[data]));
		error += temp;
		
		// reseting all variables and arrays
		memset(F, 0, 8 * nods);
		memset(WX, 0, 4 * nods);
		memset(wbar, 0, 4 * nods);
		memset(outmf, 0, 8 * nods);
		out = 0;
		total_wights = 0;
		temp = 0;
		temp2 = 0;
		//X = X + number_of_inputs;
	}

	// freeing memory
	delete[] UX;
	delete[] WX;
	delete[] wbar;
	delete[] outmf;
	delete[] F;
	delete[] Y;
	
	// return final RMSE value
	return (fixsqrt((error/ data_len)));
}






