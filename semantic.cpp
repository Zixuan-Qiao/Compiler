#include "lexical.h"
#include "syntax.h"
#include "semantic.h"
#include "external.h"

char valuesta[MAX][10] = {'\0'};		
int idxofv=0;				
vaStr ids[MAX];		
int idxofid=0;		
vaStr results[MAX];	
int idxofres=0;		
char res[5];		
int inr='1';		

void subforadd(FILE *fw)
{
	res[1]=inr; 
	inr++; 
	char temp[10];
	printf("Quadruples: (+ , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res); 
	fprintf(fw,"Quadruples: ( + , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res);
	strcpy(results[idxofres].name,res); 
	strcpy(temp,valuesta[idxofv-2]);
	strcat(temp,"+");
	strcat(temp,valuesta[idxofv-1]);
	strcpy(results[idxofres].val,temp); 
	strcpy(valuesta[idxofv-2],res);
	idxofres++;
	idxofv-=1; 
}

void subformin(FILE *fw)
{
	res[1]=inr; 
	inr++; 
	char temp[10];
	printf("Quadruples: ( - , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res); 
	fprintf(fw,"Quadruples: ( - , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res);
	strcpy(results[idxofres].name,res); 
	strcpy(temp,valuesta[idxofv-2]);
	strcat(temp,"-");
	strcat(temp,valuesta[idxofv-1]);
	strcpy(results[idxofres].val,temp); 
	strcpy(valuesta[idxofv-2],res);
	idxofres++;
	idxofv-=1; 
}

void subformul(FILE *fw)
{
	res[1]=inr; 
	inr++; 
	char temp[10];
	printf("Quadruples: ( * , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res); 
	fprintf(fw,"Quadruples: ( * , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res);
	strcpy(results[idxofres].name,res); 
	strcpy(temp,valuesta[idxofv-2]);
	strcat(temp,"*");
	strcat(temp,valuesta[idxofv-1]);
	strcpy(results[idxofres].val,temp); 
	strcpy(valuesta[idxofv-2],res);
	idxofres++;
	idxofv-=1; 
}

void subfordif(FILE *fw)
{
	res[1]=inr; 
	inr++; 
	char temp[10];
	printf("Quadruples: ( / , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res); 
	fprintf(fw,"Quadruples: ( / , %s , %s , %s )\n",valuesta[idxofv-2],valuesta[idxofv-1],res);
	strcpy(results[idxofres].name,res); 
	strcpy(temp,valuesta[idxofv-2]);
	strcat(temp,"/");
	strcat(temp,valuesta[idxofv-1]);
	strcpy(results[idxofres].val,temp); 
	strcpy(valuesta[idxofv-2],res);
	idxofres++;
	idxofv-=1; 
}