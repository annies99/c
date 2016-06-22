/*
 * nqueens.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Alec Webb
 */
#ifndef nqueens_h

#define nqueens_h

//macro definitions
#define RNG_SEED 3049
#define ARRAYLEN 20
#define LOOPTIME 10
#define NUMBEROFBOARDS 17

#define min(a,b) ((a)<(b) ? (a):(b))
#define max(a,b) ((a)>(b) ? (a):(b))

//function prototypes
void InitializeArray(double* numArray, const int arrayLength);
void randperm(double* numArray, const int arrayLength);
int checkboard(double* numArray, const int arrayLength);
double factorial(double input);
double nsquared(double ndouble, int nsize);
void displayboard(double* numArray, const int arrayLength);

#endif


