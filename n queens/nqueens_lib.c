/*
 * nqueens_lib.c
 *
 *  Created on: Sep 23, 2014
 *      Author: Alec Webb
 */
#include <stdlib.h>
#include <stdio.h>
#include "nqueens.h"

void InitializeArray(double *numArray, const int arrayLength)
{
//declare function variables
	int i;

	for(i=0; i<arrayLength; i++){										//load the array with integers 1 to n
		numArray[i]=i;
	}
}
void randperm(double *numArray, const int arrayLength)
{
	//declare function variables
	int i;
	int j; 																		//holds the random number
	double temp; 															//holds the value of the position to be shuffled

	for(i=arrayLength-1; i>0; i--){									//run the perfect shuffle algorithm
		j = random()%arrayLength;
		temp = numArray[i];
		numArray[i] = numArray[j];
		numArray[j] = temp;
	}
}
void displayboard(double* numArray, const int arrayLength)
{
	//declare function variables
	int i;
	int j;
	double getspot;														//holds the position of the queen

	for(i=0; i<arrayLength;++i){										//print the board
		getspot=numArray[i];
		for(j=0; j<arrayLength; ++j){
			if(j==getspot)													//places the queen on the board
			{
				printf(" * ");
			}
			else																	//indicates a position with no queen
			{
				printf(" - ");
			}
		}
		printf("\n");
	}

}
int checkboard(double* numArray, const int arrayLength)
{
   //declare function variables
   int queenscollide=0;
   int validsolution=0;
   int i;
   int k;
   int yslope;
   double xslope, slope;

   for(i=0; i<arrayLength; i++){										//check if the board has queens that collide
	   k = i;
	   while(k+1<arrayLength && queenscollide==0)
		{
		   yslope = (k+1)-i;													//determine y2-y1
		   xslope = numArray[k+1] - numArray[i];				//determine x2-x1
		   slope = yslope/xslope;										//calculate slope
		   	   if(slope == -1 || slope ==1)								//slope of 1 or negative 1 indicates collision
		   	   {
		   		   queenscollide=1;
		   		   validsolution=0;
		   	   }
		   	   else
		   	   {
		   		   validsolution=1;
		   	   }
		   k++;
		}
   	   }
	   if(validsolution==1)												//return a valid solution or not
	   {
		   return 1;
	   }
	   else
	   {
		   return 0;
	   }
}
double factorial(double input)								//computes the factorial
{
	if(input==0)
	{
		return 1;
	}
	else
	{
	return(input * factorial(input-1));								//recursion
	}

}
double nsquared(double ndouble, int nsize)			//compute n^n for positive n values
{
	//declare function variables
	double answer=1;
	int i;

	for(i=0; i<nsize; i++){
		answer *= ndouble;
	}
	return answer;
}

