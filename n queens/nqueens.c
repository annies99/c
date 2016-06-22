/*
 * nqueens.c
 *
 *  Created on: Sep 23, 2014
 *      Author: Alec Webb
 *  solves the N-queens chess problem through permutations
 */
#include <stdlib.h>
#include <stdio.h>
#include "nqueens_lib.c"
#include "nqueens.h"

int main()
{
//declare function variables
int i,k,j,l;
int n=0;
int pass=0;

double numArray[];
int minout[ARRAYLEN];
int maxout[ARRAYLEN];
double meanout[ARRAYLEN];
double ntimesn[ARRAYLEN];
double nfacout[ARRAYLEN];

double mean=0;
double sizesquare=0;
double nfactorial, nsq;

//seed the generator
srandom(RNG_SEED);

//introduction message
printf("Project 1, Created by: Alec Webb, Description: Solves the nqueens problem using permutations\n");
printf("---------------------------------------------------------------\n");

for(j=4; j<=ARRAYLEN; j++){ 			//start n loop
	int solutionFound=0;	//used to determine first run or not
	int nCounter=0;			//used to count number of runs for 10 solutions
	int pncount=0;				//used to calulate current number of runs for max min functions
	int current=0;				//for max min functions
	int minimum=0;			//for max min comparisons
	int maximum=0;			//for max min comparisons

	n=j;								//set size of array
	nsq=j; 							//set size for calculations

	for(k=0; k<LOOPTIME; k++){ 								//find 10 solutions
		pass=0; 															//to continue after a first match is found
		pncount = nCounter; 										//for maxmin calc
			while(pass==0)
			{
				InitializeArray(numArray, n);						//call initialize method
				randperm(numArray, n);							//call randperm function
				pass = checkboard(numArray, n);			//check the permutation
				nCounter++;												//total# of runs
			}
		current = nCounter-pncount;  							//for max min,current run time

		if(pncount==0)													//to account for a run that has not occured
		{																		//avoids min being set to 0
			minimum = maximum = current;
		}
		else
		{
			minimum = min(minimum, current);				//compare
			maximum = max(maximum, current);				//compare
		}

		solutionFound++; 											 //indicate first solution has been found
		if(solutionFound <=1)										//handles the first and only first solution
		{
		displayboard(numArray, n);								//print the solution found

		printf("---------------------------------------------------------------\n");
		printf(" ");
		for(i=0; i<n; i++){												//print the numerical solution found
			printf("%-3.0lf", numArray[i]);
		}
		printf(": Solution for board size %d\n", n);
		printf("---------------------------------------------------------------\n");
		}
}
//calculate and store relevent values
mean = nCounter/10;											//determine mean
sizesquare = nsquared(nsq,n);								//determine n^n
nfactorial = factorial(n);											//determine n!

//stores the values for printing
minout[j-4] = minimum;
maxout[j-4] = maximum;
meanout[j-4] = mean;
ntimesn[j-4] = sizesquare;
nfacout[j-4] = nfactorial;

}//end n loop

//the following prints out the results of the 10 runs for each n
printf("size      min        max         mean     size**size      size!\n");
printf("---------------------------------------------------------------\n");
for(l=0; l<NUMBEROFBOARDS; l++)
{
	printf("%4d %8d %10d %12.1e %12.1e %12.1e\n", (l+4), minout[l], maxout[l], meanout[l], ntimesn[l], nfacout[l]);
}
return 0;
}//end main
