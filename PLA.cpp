/*
 * PLA.cpp
 *	Author:	Nick Nesbit
 *	Date:	Sep 14, 2017
 *	Description:	Simple implementation of PLA algorithm
 */

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

//Define constants
#define LEARN_RATE 1
#define K_RATE 1
#define MAX_ITERATION 1000000

//Function prototypes
int randomInt();
float randomFloat();
int getSign(float [], int, int);
void updateWeights(float [], int [], int [], int [], int, int, int*);
int getError(float [], int [], int [], int [], int, int);

//Start of program
int main() {
	//Variables
	int x[80];
	int y[80];
	int types[80];
	float weights[3];
	int updates = 0;
	int trainError = 0;
	int testError = 0;
	int itr = 0;

	//Seed number generator
	srand(time(NULL));

	//Class A
	for (int i = 0; i < 40; i++) {
		x[i]= randomInt();
		y[i] = rand()%(100-x[i] + 1) + x[i];
		types[i] = 1;
	}

	//Class B
	for (int i = 40; i < 80; i++) {
		x[i]= randomInt();
		y[i] = rand()%(x[i] + 101) - 100;
		types[i] = -1;
	}

	//Intialize weights
	weights[0] = randomFloat();
	weights[1] = randomFloat();
	weights[2] = randomFloat();

	//Display starting weights
	printf("Starting equation: D = %5.3f + (%5.3fx) + (%5.3fy)\n", weights[0], weights[1], weights[2]);

	//Check innitial training data error
	trainError = getError(weights, types, x, y, 0, 25);
	trainError += getError(weights, types, x, y, 40, 65);

	//PLA loop
	while (itr < MAX_ITERATION && trainError > 0) {
		//Update the weights
		updateWeights(weights, types, x, y, 0, 25, &updates);
		updateWeights(weights, types, x, y, 40, 65, &updates);

		//Update the training data error
		trainError = getError(weights, types, x, y, 0, 25);
		trainError += getError(weights, types, x, y, 40, 65);

		//Increment iterations
		itr++;
	}

	//Check test data error
	testError = getError(weights, types, x, y, 25, 40);
	testError += getError(weights, types, x, y, 65, 80);

	//Display final weights, iterations, updates, and error
	printf("Final equation: D = %5.3f + (%5.3fx) + (%5.3fy)\nIterations: %d\nUpdates: %d\nTraining error: %d/%d\nTest error: %d/%d",
			weights[0], weights[1], weights[2], itr, updates, trainError, 50, testError, 30);

	return 0;
}
//End of program

/************************
                        *
Function definitions    *
				        *
*************************/

//Returns random integer between -100 and 100 inclusive.
int randomInt() {
	return rand()%(201) - 100;
}

//Returns random float between 0 and 100 inclusive.
float randomFloat() {
    return ((float)rand()/(float)(RAND_MAX)) * 100.00;
}

//Returns sign of equation.
int getSign(float weights[], int x, int y) {
	float sum = weights[0] + x * weights[1] + y * weights[2];
	return (sum >= 0) ? 1 : -1;
}

//Updates the weights.
void updateWeights(float weights[], int types[], int x[], int y[], int min, int max, int* updates) {
	for (int i = min; i < max; i++)
		if (types[i] != getSign(weights,x[i],y[i])) {
			weights[0] += LEARN_RATE * types[i] * K_RATE;
			weights[1] += LEARN_RATE * types[i] * x[i];
			weights[2] += LEARN_RATE * types[i] * y[i];
			(*updates)++;
		}

	return;
}

//Checks for misclassification.
int getError(float weights[], int types[], int x[], int y[], int min, int max) {
	int error = 0;
	for (int i = min; i < max; i++)
		if (types[i] != getSign(weights,x[i],y[i]))
			error++;

	return error;
}
