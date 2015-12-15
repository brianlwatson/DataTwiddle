/* 
 * CS:APP Data Lab 
 * 
 * Brian Watson - watsonb
 * Rodolfo Amaya - rodolfoa
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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
   //This function can be done by using DeMorgan's laws
  int result = ~((~x) | (~y));
  return result;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  //Shift the byte to the least significant byte position
 //and it with a high LSB
  int result = (x >> (n << 3)) & 0xFF;
  return result;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  //shift a 1 into the most significant bit
  //shift right and sign extend it so that you can invert it later
  //then shift it back one in the case of a 0 shift
  int result = ((1 << 31) >> n) << 1;
  //and with the inverted version so that the 0's cancel out the sign extended shifts
  return (x >> n) & ~result;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int bits_total, fives_mask, threes_mask, fmask1, fmask2, fmask3; 

  //create the masks
  fives_mask = 0x55;
  fives_mask = (fives_mask << 8) | fives_mask;
  fives_mask = (fives_mask << 16) | fives_mask; //55555555

  threes_mask = 0x33;
  threes_mask = (threes_mask << 8) | threes_mask;
  threes_mask = (threes_mask << 16) | threes_mask; //33333333

  fmask1 = 0x0F;
  fmask1 = (fmask1 << 8) | fmask1;
  fmask1 = (fmask1 << 16) | fmask1; //0F0F0F0F

  fmask2 = 0xFF;
  fmask2 = (0xFF << 16) | fmask2; //00FF00FF

  fmask3 = 0xFF;
  fmask3 = (0xFF << 8) | fmask3; //0000FFFF

  //compare x against each mask by anding it with each mask
  //you get a count for each one and you add them all together
  bits_total = (x & fives_mask) + ((x >> 1) & fives_mask);     //01010101010101010101010101010101
  bits_total = (bits_total & threes_mask) + ((bits_total >> 2) & threes_mask); //00110011001100110011001100110011
  bits_total = (bits_total & fmask1) + ((bits_total >> 4) & fmask1); //00001111000011110000111100001111
  bits_total = (bits_total & fmask2) + ((bits_total >> 8) & fmask2); //00000000111111110000000011111111
  bits_total = (bits_total & fmask3) + ((bits_total >> 16)& fmask3); //00000000000000001111111111111111
  return bits_total;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  x = x | (x >> 16);
  x = x | (x >> 8);
  x = x | (x >> 4);
  x = x | (x >> 2);
  x = x | (x >> 1);
  //Find if bits are set

  //check to see if everything cascaded down to the LSB
  x = x & 0x1;

  //invert the LSB by xor
  return x ^ 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //we know that this is 32 bits, so shift a 1 to the MSB where it will be
  //the most negative.
  int result = 1 << 31;
  return result;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int bits, temp;
  bits = 33 + ~n; //find number of bits to shift, the 33 is because we know one of the bits is a 2's complement
  temp = x << bits; //get rid of 2's complement
  temp = temp >> bits; //get value without 2's complement
  return !(temp ^ x); //Bits should line up, if they don't return 0
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  //Determine a mask for the sign
  int mask = (1 << n) + ~0;
  //printf("MASK %x %x %d \n",mask,x,n);
  //Add 1 for a negative
  //Add 0 for a non-negative
  //mask n bits of shifts
  int result = (x >> 31) & mask;
    return (x + result) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  //invert two's complement number and add 1 
  int result = ~x + 1;
  return result;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  //get the most significant bit
  int result = ((x >> 31) & 0x1) ;
  //and the most significant bit with double inverted value of x (to check if it was zero)
  return (~result & !!x);
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //swap the bits
  int result;
  //xor x and y to swap bits
  int sign = x ^ y;

  //take the difference by negating one
  int difference = y + (~x + 1);
  
  //flip the swapped bits and and it with the notted difference
  //Note that this will be all ones if they are the same. 
  //keep the sign
  result = ((~sign & ~difference) | (sign & x)) & (1 << 31);

  //if result is 1, then it is less
  //!difference will tell us if they were equal or not
  result = (!!result) | (!difference);

  return result; 
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    //make your masks
    int fives_mask, threes_mask, fmask1, fmask2, fmask3; // store the total here

    fives_mask = 0x55;
    fives_mask = (fives_mask << 8) | fives_mask;
    fives_mask = (fives_mask << 16) | fives_mask; //55555555

    threes_mask = 0x33;
    threes_mask = (threes_mask << 8) | threes_mask;
    threes_mask = (threes_mask << 16) | threes_mask; //33333333

    fmask1 = 0x0F;
    fmask1 = (fmask1 << 8) | fmask1;
    fmask1 = (fmask1 << 16) | fmask1; //0F0F0F0F

    fmask2 = 0xFF;
    fmask2 = (0xFF << 16) | fmask2; //00FF00FF

    fmask3 = 0xFF;
    fmask3 = (0xFF << 8) | fmask3; //0000FFFF

    //check to see if there are bytes in each position
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);

    //and the new combination with each mask, shift it and then and it again
    //this is kind of like checking at each lower power and working your way up
    //if it fits in the next highest power, then do the mask and shift it
    //  and then change the value of x to reflect the next highest log.
    x = (x & fives_mask) + ((x >> 1) & fives_mask);
    x = (x & threes_mask) + ((x >> 2) & threes_mask);
    x = (x & fmask1) + ((x >> 4) & fmask1);
    x = (x & fmask2) + ((x >> 8) & fmask2);
    x = (x & fmask3) + ((x >> 16) & fmask3);
    x = x + ~0;
    return x; 
  }
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  
  //divide it up into the two parts. lower 23, upper 9 and sign (disregard)
  unsigned exp = (uf >> 23) & 0xFF; 
  unsigned frac = (uf << 9);  

  //if exponent and the bit mask are the same, then exponents are all high
  // AND fraction part is positive
  if ((!(exp ^ 0xFF) && (frac))) 
  {
    return uf; 
  }

  else 
  {
    //invert the sign to negate
    return uf ^ (0x1 << 31);
  }
}
/*  
 * float_i2f - Return bit-level equivalent of expression (float) x 
 *   Result is returned as unsigned int, but 
 *   it is to be interpreted as the bit-level representation of a 
 *   single-precision floating point values. 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while 
 *   Max ops: 30 
 *   Rating: 4 
 */ 
unsigned float_i2f(int x) { 
    int i, exp, delta, bitMask; 
    int bits = 0; 
    unsigned bit; 
     
    bit = x & (1 << 31); /* obtain the sign bit*/ 
    exp = (x >> 31) ? 158 : 0; /* INT_MIN */ 
    if (x << 1) // x is not INT_MIN 
    {  
    if (x < 0) 
    { 
              x = -x; // work with positive numbers only  
    } 
          i = 30; // only up to 30 because last bit is sign bit 
          while ( !((x >> i) & 1) ) // As long as there are 1's in x  
    { 
        i--; 
    }  
        exp = i + 127; // i is now the index where the first 0 is  
        x = x << (31 - i); // remove everything above that 0 
        bitMask = (1 << 23) - 1; // 23 is for the number of bits in float
                 // Subtract 1 to obtain the 2's complement 3FFFFF 
        bits = bitMask & (x >> 8); // Put the high 24 bits of x into the variable bits 
        x = x & 0xFF; // overflow control 
        delta = x > 128 || ((x == 128) && (bits & 1)); //value is larger than what is representable by float 
        bits += delta; // if the value was larger than than what float can hold, add 1 
        if(bits >> 23) // if bits has a 1 at the 24 position, there will be overflow 
        { 
           bits &= bitMask; // remove the overflow 
           exp += 1; // acknowledge there was overflow 
        } 
    } 
    bit = bit | (exp << 23); //add the overflowed bit to bit 
    bit = bit | bits; // store the bits in bit 
    return bit; 
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

  int exp,bits;
  unsigned bit;

  exp = (uf >> 23) & 0xFF; // obtain upper bits of uf 
  bits = uf & ((1 << 23) - 1); // obtain the bits from uf 
  bit = uf & (1 << 31); // obtain the sign bit 

  if ((exp ^ 0xFF)) // exp != 255 
  { 
    if (!exp) // exp is 0 
    { 
      bits = bits << 1;
    }
    else       // exp is not 0 
    {
      exp++;
      if (exp == 255) // infinity 
      {
        bits = 0; 
      }
    }
  }
  bit = bit | (exp << 23);
  bit = bit | bits;
  return bit;
}
// Should be 15 puzzles, 2 level 1 puzzles, 5 level 2 puzzles, 3 level 3 puzzles, 5 level 4 puzzles
