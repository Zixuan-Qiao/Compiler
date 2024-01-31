#include "lexical.h"
#include "syntax.h"
#include "semantic.h"
#include "external.h"

int ACTION[16][8]={
	{4,-1,-1,-1,-1,-1,5,-1},
	{-1,-1,6,7,-1,-1,-1,100},
	{-1,23,23,23,8,9,-1,23},
	{-1,26,26,26,26,26,-1,26},
	{4,-1,-1,-1,-1,-1,5,-1,},
	{-1,28,28,28,28,28,-1,28},
	{4,-1,-1,-1,-1,-1,5,-1},
	{4,-1,-1,-1,-1,-1,5,-1},
	{4,-1,-1,-1,-1,-1,5,-1},
	{4,-1,-1,-1,-1,-1,5,-1},
	{-1,15,6,7,-1,-1,-1,-1},
	{-1,21,21,21,8,9,-1,21},
	{-1,22,22,22,8,9,-1,22},
	{-1,24,24,24,24,24,-1,24},
	{-1,25,25,25,25,25,-1,25},
	{-1,27,27,27,27,27,-1,27}
	};

int GOTO[16][3]={
	{1,2,3},
	{-1,-1,-1},
	{-1,-1,-1},
	{-1,-1,-1},
	{10,2,3},
	{-1,-1,-1},
	{-1,11,3},
	{-1,12,3},
	{-1,-1,13},
	{-1,-1,14},
	{-1,-1,-1},
	{-1,-1,-1},
	{-1,-1,-1},
	{-1,-1,-1},
	{-1,-1,-1},
	{-1,-1,-1}
};

char TOKEN[MAX] = {'\0'};
int stacks[MAX] = {0};	
int as = 0;
int stackx[MAX] = {0};	
int TopStat = 0, InpSym = 0;
int leng = 0;			
char arr[MAX] = {'\0'};
int ai=0;			
int counter=1;		
int len=0;			
int x=1;			
int ef=1000;		
int s=0;			
int fa=0;
int rf = 0;

void readandputall(FILE *fp,FILE *ft)		
{
	char getw;
	int fc;		
	fc=0;		
	if(rf==1&&as!=7) fseek(fp,-1,1);	
	while ((getw = fgetc(fp)) != EOF) {
		if(getw==10) fc++;		// in Windows system, new line character (ASCII code=10) takes two positions in a file
		arr[ai]=getw;
		ai++;
		fc++;
	}
	fseek(fp,-fc,1);
	if(rf==1&&as!=7) fseek(fp,1,1);	
	arr[ai]='#';	
	printf("%s\n",arr);
	for(int oo=0;oo<=ai;oo++){		
		arr[oo]='\0';
	}
	ai=0;
}

void controller(FILE *fp,FILE *ft,FILE *fw)		
{	
	ef=100;
	stacks[s]=0;
	TopStat=stacks[s];
	s++;
	word(fp,fw);
	InpSym=as;
	while(ACTION[TopStat][InpSym]!=Acc)
	{
		rf=0;
		if(ACTION[TopStat][InpSym]==ERROR)
		{
			ef=1;
			break;
		}
		else if(ACTION[TopStat][InpSym]<=15&&ACTION[TopStat][InpSym]>=0)
			{
				push();
				change(0,x);
				readandputall(fp,ft);
				advance(fp,fw);
			}
			else if(ACTION[TopStat][InpSym]<=28&&ACTION[TopStat][InpSym]>=21)
				{
					rf=1;
					act(ACTION[TopStat][InpSym]-20,fw);
					change(0,x-1);
					readandputall(fp,ft);
				}
	}
	if(ef==1) { printf("Compilation terminated. \n"); exit(1); }
}

void push()
{
	stacks[s]=ACTION[TopStat][InpSym];
	stackx[x]=InpSym;
}

void advance(FILE *fp,FILE *fw)
{
	TopStat=stacks[s];
	word(fp,fw);
	InpSym=as;
	s++;
	x++;
}

void act(int k,FILE *fw)
{
	res[0]='R';
	switch(k)
	{
		case 1:len=3; x-=len; stackx[x]=8; subforadd(fw); break;//	+
		case 2:len=3; x-=len; stackx[x]=8; subformin(fw); break;//	-
		case 3:len=1; x-=len; stackx[x]=8; break;		//
		case 4:len=3; x-=len; stackx[x]=9; subformul(fw); break;//	*
		case 5:len=3; x-=len; stackx[x]=9; subfordif(fw); break;//	/
		case 6:len=1; x-=len; stackx[x]=9; break;		//
		case 7:len=3; x-=len; stackx[x]=10;break;		//
		case 8:len=1; x-=len; stackx[x]=10;break;		//
	}		

	for(int j=1;j<=len;j++)
	{
		stacks[s-len]=0;
	}
	s=s-len;
	stacks[s]=GOTO[stacks[s-1]][stackx[x]-8];
	TopStat=stacks[s];
	InpSym=as;
	s++;
	x++;
}

void change(int x,int y)
{
	char sta[20];
	for(int ee=0;ee<20;ee++)
	{
		sta[ee]='\0';
	}
	int ta;
	ta=0;
	stackx[x]=7;
	for(ee=x;ee<=y;ee++){
		switch(stackx[ee]){
			case 0:sta[ta]='('; ta++; break;
			case 1:sta[ta]=')'; ta++; break;
			case 2:sta[ta]='+'; ta++; break;
			case 3:sta[ta]='-'; ta++; break;
			case 4:sta[ta]='*'; ta++; break;
			case 5:sta[ta]='/'; ta++; break;
			case 6:sta[ta]='i'; ta++; break;
			case 7:sta[ta]='#'; ta++; break;
			case 8:sta[ta]='E'; ta++; break;
			case 9:sta[ta]='T'; ta++; break;
			case 10:sta[ta]='F'; ta++; break;
		}	
	}
	printf("%d\t\t%s\t\t",counter,sta);
	counter++;
}
