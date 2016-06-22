/* 
 * CS:APP Data Lab 
 * 
 * <Alec Webb : awebb3>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {

  int to_tmin = 0x00;
  int state   = 0x00;
  int compare = 0x00;
  int neg1    = 0x00;
  int sol     = 0x00;

  to_tmin 	= x + 0x01;	//add 1, if x is tmax then to_tmin will become tmin
  neg1 		= x + to_tmin;	//add to_tmin to x, if x was tmax then the result is -1 (all 1's)  
  state 	= !(to_tmin);	//determine the state of to_tmin, if it was anything but 0, 
				//then should be set to false (all 0's)
  neg1 		= ~(neg1);	//compliment neg1, if neg1 is -1 (all 1's) this will set it to 0 (all 0's)
  compare 	= (neg1 | state); //the only case for the solution to be tmax is when both sol 
				//and state are all 0's
  sol 		= !(compare);	//if that was the case, sol will be set to 1, otherwise set to zero.
	
  return sol;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  int tbit = 0x49; //start with 01001001
  
  tbit = (tbit << 0x09) + tbit;//shift left 9, add original value to copy the bits into those places
  tbit = (tbit << 0x12) + tbit;//repeat to yield  0x49249249 (01001001001001001001001001001001)

  return tbit;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int a   = 0x00;
  int b   = 0x00;
  int sol = 0x00;
  
  a 	= (x & ~(y));		//use De Morgan's law 
  b 	= (~(x) & y);		//(P and notQ) OR (notP and Q)
  sol 	= ~((~a) & (~b));	//reverse the result to use an AND in place of the OR
  
  return sol;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  int y   = 0x00;
  int z   = 0x00;	
  int sol = 0x00;
	
  y 	= (x >> 0x1F);	//shift right to fill all positions with MSB
  z 	= !(!(x));  	//if x is a zero, its initial state is false, by !!x we end up with all zero's 
				//if x is negative, its initial state is true when !! we end up with a 1 in the lsb
				//if x is positive, its initial state is true, we end up with a 1 in the lsb
  sol = (y | z);   	//the or operator can now set the bits to all 0's (0), all 1's(-1), 
				//or all zeros followed by a 1 in the lsb (+1)
				//depending on whether the shift was all 0's (+ or 0) all 1's (-).
	
  return sol; 
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  int sol = 0x00;
	
  sol = (x   << 0x1F);//shift to left to leave only the lsb in the msb position
  sol = (sol >> 0x1F);//shift to right to fill all positions with value of lsb (now the msb)
	
  return sol;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int sol             = 0x00;
  int byte_to_replace = 0x00;

  byte_to_replace = (n << 0x03);		//determine the position of the byte that needs to be replaced
						//which will be n=0:first byte, n=1:second byte, n=2:third byte, n=3:fourth byte
						//with corresponding shifts of 0, 8, 16, 24
  sol = (0xFF << byte_to_replace);		//set 8 bits to all 1's to push across 32 bit space
  sol = ~(sol);					//flip bits to assign shifted bits to 0's, everything else to 1's
  
  c   = c << byte_to_replace;			//move c over to the byte location that needs replacing
  sol = (x & sol); 				//copy the values of x into the correct locations
						//anything & with 1 returns itself. anything anded with zero returns a 0
  sol = (sol | c);				//or the new c, anything or'd with 0 gets replaced.
  
  return sol;
}
