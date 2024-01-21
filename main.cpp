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
		counter=1;
		memset(valuesta, NULL, sizeof(valuesta));
		memset(stacks, NULL, sizeof(stacks));
		memset(stackx, NULL, sizeof(stackx));
		as=0;
		printf("Word/Step\tToken Stack\tRemainder\n"); 
		fseek(p,-1,1);
		controller(p,t,w);c++;
		printf("Success!\n");
	}
	fclose(p);
	fclose(w);
}
