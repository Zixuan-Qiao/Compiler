#include "Syntax.h"
#include "External.h"

void main()
{
	FILE *p,*w,*t;
	p=fopen("test.txt", "r");
	w=fopen("out.txt", "w"); 
	t = NULL;
	char fir;
	while ((fir = fgetc(p)) != EOF)	// call syntax analysis controller for each expression
	{
		memset(valuesta, NULL, sizeof(valuesta));
		memset(stacks, -1, sizeof(stacks));
		memset(stackx, -1, sizeof(stackx));
		counter=1; 
		printf("Word/Step\tToken Stack\tRemainder\n"); 
		fseek(p,-1,1);
		controller(p,t,w); 
		printf("Success!\n");
	}
	fclose(p);
	fclose(w);
}
