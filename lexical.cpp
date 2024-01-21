#include "lexical.h"
#include "external.h"

int w, n, p, e, d;
int Class;
int ICON;
double FCON;
int ForI = 1000; // Float or Integer flag
static int CurrentState;
char lc1;
char lc2;
char nextcha;
int flag=5000; // Positive or Negative flag
char *stri;
int linec=1;
int c = 0;
int wf  = 1000;

char *KeyWordTable[MAX_KEY_NUMBER]={ "if", "then", "else", "while", "begin", "end" , "int" , "for", "do" , KEY_WORD_END};

void word(FILE *fp,FILE *fw)
{
	memset(TOKEN, 0, sizeof(TOKEN));
	//char con[20];
	wf=0;
	char fir;
	while ((fir = fgetc(fp)) != ';') {
		if(fir==10) {linec++; continue;}
		if (fir == ' '|| fir == '\r'|| fir == '\t'|| fir == '\n') continue; else if(fir!='#') fseek(fp,-1,1);
		if(fir=='#') // delete comment
		{
			while(1)
			{
				fir = fgetc(fp);
				if(fir=='#') 
					break;
			}
			continue;
		}
			scanner_example(fp,fw);
			break;
	}//while
	if(fir==';') as=7;
	if(wf==1) word(fp,fw);// skip error
}

void scanner_example(FILE *fp,FILE *fw)
{
	char ch; int i, c;
	ch = fgetc(fp);
	if (ch>='a'&&ch<='z')  /*it must be an identifer!*/
	{
		TOKEN[0] = ch; ch = fgetc(fp); i = 1;
		while ((ch >= 'a'&&ch <= 'z')|| (ch >= '0'&&ch <= '9'))
		{
			TOKEN[i] = ch; i++;
				ch = fgetc(fp);
		}
		TOKEN[i] = '\0';
		c = lookup(TOKEN);		
		if (c == 0) 
		{
			out(ID, TOKEN,fw);
			strcpy(valuesta[idxofv],TOKEN);idxofv++;
		}else out(c, " ",fw); 	
		if(ch!=EOF)	fseek(fp, -1, 1); /* retract*/
	}
	else
		if(ch == '0') Octa(fp,fw);

		else if ((ch >= '1'&&ch <= '9')||ch == '.')
		{
			ICON=0;
			FCON=0;
			n = 0; p = 0; e = 0; w = 0;
			LEX(fp,fw,ch);
		}
		else

			switch (ch)
			{
			case '<': ch = fgetc(fp);
				if (ch == '=') out(LE, " ",fw);
				else if (ch == '>') out(NE, " ",fw);
				else
				{
					if(ch!=EOF) fseek(fp, -1, 1); 
					out(LT, " ",fw);
				}
				break;
			case ':': fseek(fp, 1, 1); out(IS, " ",fw); break;
			case '=': out(EQ, " ",fw); break;
			case '+': out(PL, " ",fw); break;
			case '*': out(MU, " ",fw); break;
			case '/': out(DI, " ",fw); break;
			case '&': out(AN, " ",fw); break;
			case '|': out(OR, " ",fw); break;
			case '(': out(LFBK, " ",fw); break;
			case ')': out(RTBK, " ",fw); break;
			case '>': ch = fgetc(fp);
				if (ch == '=') out(GE, " ",fw);
				else
				{
					if(ch!=EOF) fseek(fp, -1, 1);
					out(GT, " ",fw);
				}
				break; // determine whether it is a minus sign or a negative sign
			case '-':fseek(fp,-3,1); lc1=fgetc(fp); lc2=fgetc(fp);if(lc2=='='||lc2=='>'||lc2=='<'||lc2=='+'||lc2=='-'||lc2=='*'||lc2=='/'){flag=1; fseek(fp,1,1);ch=fgetc(fp);LEX(fp,fw,ch);} else {fseek(fp,-1,1);out(MI, " ",fw); stri="(MI, )\n"; fputs(stri,fw);} break;
			case';':break;
			default: report_error(); break;
			}
	return;
}

int GetChar(int j)
{
	int c;
	c = TOKEN[j];
	if (c >= '0'&&c <= '9') { d = c - '0'; return DIGIT;}
	if (c == '.') return POINT;
	if (c == 'E' || c == 'e') return POWER;
	if (c == '+') return PLUS;
	if (c == '-') return MINUS;
	return OTHER;
}
int EXECUTE(int state, int symbol,FILE* fw)
{
	switch (state)
	{
	case 0: switch (symbol)
	{
	case DIGIT:n = 0; p = 0; e = 1; w = d; CurrentState = 1; Class = ClassNo; break;
	case POINT:w = 0; n = 0; p = 0; e = 1; CurrentState = 3; Class = ClassNo; break;
	default: HandleOtherWord(); Class = ClassOther;
		CurrentState = EndState;
	}
			break;
	case 1: switch (symbol)
	{
	case DIGIT:w = w * 10 + d; break;
	case POINT:CurrentState = 2;  break;
	case POWER:CurrentState = 4; break;
	default: ICON = w; CurrentState = EndState; if(flag==1) {ICON*=-1; flag=5000;} printf("(INT,%d)\n", ICON); as=6;  itoa(ICON,valuesta[idxofv],10); idxofv++;  fprintf(fw,"(INT,%d)\n",ICON);
	}
			break;
	case 2: switch (symbol)
	{
	case DIGIT:n++; w = w * 10 + d; break;
	case POWER:CurrentState = 4; break;
	default: FCON = w * pow(10, e*p - n); CurrentState = EndState; if(flag==1) {FCON*=-1; flag=5000;} printf("(REAL,%g)\n", FCON);  as=6; gcvt(FCON,5,valuesta[idxofv]); idxofv++; fprintf(fw,"(REAL,%g)\n",FCON);
	}
			break;
	case 3:switch (symbol)
	{
	case DIGIT:n++; w = w * 10 + d; CurrentState = 2; break;
	default: HandleError(); CurrentState = EndState;
	}
		   break;
	case 4:switch (symbol)
	{
	case DIGIT:p = p * 10 + d; CurrentState = 6; break;
	case MINUS:e = -1; CurrentState = 5; break;
	case PLUS:CurrentState = 5; break;
	default:HandleError(); CurrentState = EndState;
	}
		   break;
	case 5:switch (symbol)
	{
	case DIGIT:p = p * 10 + d; CurrentState = 6; break;
	default:HandleError(); CurrentState = EndState;
	}
		   break;
	case 6:switch (symbol)
	{
	case DIGIT:p = p * 10 + d; break;
	default:FCON = w * pow(10, e*p - n); CurrentState = EndState; if(flag==1) {FCON*=-1; flag=5000;} printf("(REAL,%g)\n", FCON); as=6;  gcvt(FCON,5,valuesta[idxofv]); idxofv++; fprintf(fw,"(REAL,%g)\n",FCON);
	}
		   break;
	}
	return CurrentState;
}
int LEX(FILE *fp,FILE *fw,char cha)
{
	for(int y=0;y<MAX;y++)
	{
		TOKEN[y]='\0';
	}
	int i = 0;
	for (int j = 0;; j++) {
		if ((cha <= '9'&&cha >= '0') || cha=='E'|| cha=='-'|| cha=='.')
		{
			TOKEN[i] = cha;
			i++;
			cha = fgetc(fp);
		}
		else break;
	}
	int ch;
	CurrentState = 0;
	j = 0;
	while (CurrentState != EndState)
	{
		ch = GetChar(j);
		EXECUTE(CurrentState, ch,fw);
		j++;
	}
	if(cha!=EOF)
		fseek(fp, -1, 1);
	return Class;
}

int lookup(char *token)
{
	int n = 0;
	while (strcmp(KeyWordTable[n], KEY_WORD_END)) 
	{
		if (!strcmp(KeyWordTable[n], token)) 
		{
			return n + 1; 
			break;
		}
		n++;
	}
	return 0; 
}

void wordforids(FILE *fp,FILE *fw)
{
	char fir;
	while (1) {					
		fir = fgetc(fp);
		if (fir == ' '|| fir == '\r'|| fir == '\t'|| fir == '\n'||fir == 10) continue; else if(fir!='#') {fseek(fp,-1,1);break;}
		if(fir=='#') 
		{
			while(1)
			{
				fir = fgetc(fp);
				if(fir=='#') 
					break;
			}
			continue;
		}
			break;
	}//while
	char ch; int i;
	ch = fgetc(fp);
	if (ch>='a'&&ch<='z')  /*it must be a identifer!*/
	{
		TOKEN[0] = ch; ch = fgetc(fp); i = 1;
		while ((ch >= 'a'&&ch <= 'z')|| (ch >= '0'&&ch <= '9'))
		{
			TOKEN[i] = ch; i++;
				ch = fgetc(fp);
		}
		TOKEN[i] = '\0';
		if(ch!=EOF)	fseek(fp, -1, 1); /* retract*/
	}
	fprintf(fw,"(ID,%s)\n",TOKEN);
	while (1) {						
		fir = fgetc(fp);
		if (fir == ' '|| fir == '\r'|| fir == '\t'|| fir == '\n'||fir == 10) continue; else {fseek(fp,-1,1); break;}
		if(fir=='#')
		{
			while(1)
			{
				fir = fgetc(fp);
				if(fir=='#') 
					break;
			}
			continue;
		}
			break;
	}
}

void out(int a,char*wordin,FILE *fw)	
{
	switch(a)
	{
		case ID:printf("(ID,%s)\n",wordin); as=6; fprintf(fw,"(ID,%s)\n",wordin);break; 
		case LT:printf("(LT,%s)\n",wordin); fprintf(fw,"(LT,%s)\n",wordin);break;
		case LE:printf("(LE,%s)\n",wordin); fprintf(fw,"(LE,%s)\n",wordin);break;
		case EQ:printf("(EQ,%s)\n",wordin); fprintf(fw,"(EQ,%s)\n",wordin);break;
		case NE:printf("(NE,%s)\n",wordin); fprintf(fw,"(NE,%s)\n",wordin);break;
		case GT:printf("(GT,%s)\n",wordin); fprintf(fw,"(GT,%s)\n",wordin);break;
		case GE:printf("(GE,%s)\n",wordin); fprintf(fw,"(GE,%s)\n",wordin);break;
		case IS:printf("(IS,%s)\n",wordin); fprintf(fw,"(IS,%s)\n",wordin);break;
		case PL:printf("(PL,%s)\n",wordin); as=2;  fprintf(fw,"(PL,%s)\n",wordin); break; 
		case MI:printf("(MI,%s)\n",wordin); as=3;  fprintf(fw,"(MI,%s)\n",wordin); break; 
		case MU:printf("(MU,%s)\n",wordin); as=4;  fprintf(fw,"(MU,%s)\n",wordin); break; 
		case AN:printf("(AN,%s)\n",wordin); fprintf(fw,"(AN,%s)\n",wordin);break;
		case OR:printf("(OR,%s)\n",wordin); fprintf(fw,"(OR,%s)\n",wordin);break;
		case DI:printf("(DI,%s)\n",wordin); as=5;  fprintf(fw,"(DI,%s)\n",wordin);break; 
		case IF:printf("(IF,%s)\n",wordin); fprintf(fw,"(IF,%s)\n",wordin);break;
		case THEN:printf("(THEN,%s)\n",wordin); fprintf(fw,"(THEN,%s)\n",wordin);break;
		case ELSE:printf("(ELSE,%s)\n",wordin); fprintf(fw,"(ELSE,%s)\n",wordin);break;
		case WHILE:printf("(WHILE,%s)\n",wordin); fprintf(fw,"(WHILE,%s)\n",wordin);break;
		case BEGIN:printf("(BEGIN,%s)\n",wordin); fprintf(fw,"(BEGIN,%s)\n",wordin);break;
		case END:printf("(END,%s)\n",wordin); fprintf(fw,"(END,%s)\n",wordin);break;
		case INT:printf("(INT,%s)\n",wordin); fprintf(fw,"(INT,%s)\n",wordin);break;
		case FOR:printf("(FOR,%s)\n",wordin); fprintf(fw,"(FOR,%s)\n",wordin);break;
		case DO:printf("(DO,%s)\n",wordin); fprintf(fw,"(DO,%s)\n",wordin);break;
		case LFBK:printf("(LFBK,%s)\n",wordin); as=0; fprintf(fw,"(LFBK,%s)\n",wordin); break; 
		case RTBK:printf("(RTBK,%s)\n",wordin); as=1; fprintf(fw,"(RTBK,%s)\n",wordin); break; 
	}
}

void Octa(FILE *fp,FILE *fw)		
{
	int j=0;
	int i=0;
	int sum=0;
	char cha = fgetc(fp);
	char wordin[20];
	for(j=0;;j++){
		if(cha <= '7' && cha >= '0'){
			wordin[i] = cha-'0';
			cha = fgetc(fp);
			i++;
		}
		else break;
	}
	i--;
	int c=i;
	j=0;
	for(;i>=0;i--){
		wordin[i]*=pow(8,j);
		j++;
	}
	for(i=0;i<=c;i++){
		sum+=wordin[i];
	}
    fprintf(fw,"(OCTAL,%d)\n",sum);
	printf("(OCTAL,%d)\n",sum);
	fseek(fp, -1, 1);
}

void report_error()
{
	printf("Error at line %d\n",linec);
}

int HandleOtherWord(void)
{
	return ClassOther;
}
int HandleError(void)
{
	printf("Error at line %d\n",linec);
	return 0;
}