#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cstdlib>

//# define ( 0		
//# define ) 1		
//# define + 2		
//# define - 3	
//# define * 4		
//# define / 5		
//# define i 6		
//# define # 7		
//# define E 8		
//# define T 9			
//# define F 10

# define S0 0
# define S1 1
# define S2 2
# define S3 3
# define S4 4
# define S5 5
# define S6 6
# define S7 7
# define S8 8
# define S9 9
# define S10 10
# define S11 11
# define S12 12
# define S13 13
# define S14 14
# define S15 15

# define ERROR -1
# define Acc 100

void controller(FILE *fp,FILE *ft,FILE *fw);	// Syntax analysis driver
void push();				
void advance(FILE *fp,FILE *fw);				
void act(int k,FILE *fw);			// Reduction
void change(int x,int y);			// Output the content of token stack
void word(FILE *fp,FILE *fw);		
void readandputall(FILE *fp,FILE *ft);	
