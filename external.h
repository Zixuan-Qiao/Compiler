#define MAX 60

extern char TOKEN[MAX];
extern int stacks[MAX];	// status stack
extern int as;
extern int stackx[MAX];	// token stack
extern int TopStat,InpSym;
extern int leng;		// length of input plus "#"
extern char arr[MAX];
extern int ai;		// index of arr
extern int counter;		// step counter
extern int len;			
extern int x;		// index of token stack
extern int ef;		// error flag
extern int wf;
extern int s;		//index of status stack
extern int fa;
extern int rf;
extern int c;

extern char valuesta[MAX][10];	// value stack
extern int idxofv;			// index of value stack

typedef struct {			// structure for intermediate results
	char name[MAX];
                char val[MAX];
} vaStr;

extern vaStr ids[MAX];	// identifier stack
extern int idxofid;		// index of identifier stack
extern vaStr results[MAX];	// intermediate result stack
extern int idxofres;		// index of intermediate result stack

extern char res[5];
extern int inr;
