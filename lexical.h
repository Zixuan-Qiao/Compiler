#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cstdlib>

# define LETTER	0
# define DIGIT	1
# define POINT	2
# define OTHER	3
# define POWER	4
# define PLUS	5
# define  MINUS	6
# define ClassNo 100 
# define ClassOther 200
# define EndState -1

# define ID 0
# define IF 1
# define THEN 2
# define ELSE 3
# define WHILE 4
# define BEGIN 5
# define END 6
# define INT 7
# define FOR 8
# define DO 9
# define LT 10
# define LE 11
# define EQ 12
# define NE 13
# define GT 14
# define GE 15
# define IS 16
# define PL 17
# define MI 18
# define MU 19
# define DI 20
# define AN 21 
# define OR 22
# define LFBK 23
# define RTBK 24

#define MAX_KEY_NUMBER 20  
#define KEY_WORD_END "waiting for your expansion"  

extern void report_error(void);
void scanner_example(FILE *fp,FILE *fw);
int GetChar(int j);
int EXECUTE(int state, int symbol,FILE* fw);
int LEX(FILE *fp,FILE *fw,char cha);
void report_error();
int lookup(char *token);
void out(int a,char*wordin,FILE *fw);
void Octa(FILE *fp,FILE *fw);
int HandleOtherWord(void);
int HandleError(void);
void word(FILE *fp,FILE *fw);