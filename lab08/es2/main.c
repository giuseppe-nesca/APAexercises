#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxchar 5+1

char**faq(char filename[]);
void strgen(int nconsonanti, int nvocali, int ntot,char**vettorestringhe,int *point,char*arg,int lv);
void check(int I, int J, int K, char** string, int *state,char*arg);
void check2(char*string, int *i, int *j, int *k);
int isfull(int *state);
//3
void groupgen(char**string, int *state, char*arg, int lv);
void checkapp(char **string, int *state, char*arg);
int N = 0;
int GFLAG = 0;

int main(int argc,char **argv)
{
	int i, j, k;
	char **string=faq("stringhe.txt");

//point 1/2
	printf("inserisci i (max consonanti consecutive): "); scanf("%d", &i);
	printf("inserisci j (max vocali consecutive): "); scanf("%d", &j);
	printf("inserisci k (max caratteri tot): "); scanf("%d", &k);
	strgen(i, j, k,string,NULL,argv[1],1);
	
	if (GFLAG > 0) printf("esiste una combinazione che forma la parola '%s'\n", argv[1]);
//point 3
	groupgen(string, NULL, argv[1], 0);
	
	return 0;
}

//funzioni point1/2
char**faq(char filename[])
{
	FILE*f = fopen(filename, "r"); char**string,s[maxchar]; int i = 0;

	if (f == NULL) { puts("errore acquisizione da file"); exit(1); }
	fscanf(f, "%d", &N);
	string = malloc(N*sizeof(char*));
	for (i = 0;i < N;i++)
	{
		fscanf(f, "%s", s);
		string[i] = strdup(s);
	}
	fclose(f);
	return string;
}

void strgen(int i, int j, int k,char**string,int *state,char*arg,int lv)
{
	int x=0;
	if (state == NULL)
	{
		state = malloc(N*sizeof(int));
		for (x = 0;x < N;x++)
		{
			state[x] = -1;
		}
	}
	if (isfull(state)==1) return;


	for (x = 0;x < N;x++)
	{
		if (state[x] < 0)
		{
			state[x] = lv;
			check(i,j,k,string,state,arg); //verifica e stampa
			strgen(i,j,k,string,state,arg,lv+1); //ricorri
			state[x] = -1;
		}
	}
	if (lv == 1) free(state);
}

void check(int I, int J, int K, char** string, int *state, char* arg) //verifica e stampa
{
	char*pointer = arg;//
	int i = 0, j = 0, k = 0;
	int x, y;
	for (x = 0;x < N;x++)
	{
		if (state[x] > 0)
		{
			check2(string[x], /*I,J,K,*/&i, &j, &k);
		}
	}
	if (i <= I && j <= J && k <= K)
	{
		for (x = 1;x <= N;x++)
		{
			for (y = 0;y < N;y++)//
			{
				if (state[y] == x)
				{
					printf("%s", string[y]);
					//printf("%d", strncmp(string[y], pointer));//debug only
					if ((strncmp(string[y], pointer,strlen(string[y]))) == 0) {
						
						pointer = pointer + strlen(string[y]);}
					else(pointer = arg);

					if (strlen(arg) == pointer - arg) {
						GFLAG = 1; pointer = arg;
					}
					break;
				}
			}
		}
		printf("\n");
	}
	else {
		for (x = 1;x <= N;x++) for (y = 0;y < N;y++)//
		{
			if (state[y] == x)
			{
				if ((strncmp(string[y], pointer,strlen(string[y])))==0)
					pointer = pointer + strlen(string[y]);
				else(pointer = arg);

				if (strlen(arg) == pointer - arg) {
					GFLAG = 1; pointer = arg;
					x = 1000000000;
					y = x;
				}
				break;
			}
		}
	}
}

void check2(char*string,int *i,int *j,int *k)
{
	int l = strlen(string);
	int x;
	for (x = 0;x< l;x++)
	{
		if (string[x] != 'a' && string[x] != 'e' && string[x] != 'i' && string[x] != 'o' && string[x] != 'u')
		{
			(*i)++;
		}
		else (*j)++;
		(*k)++;
	}

}

int isfull(int *state)
{
	int i = 0,x;
	for (x = 0;x < N;x++)
	{
		if (state[x] > 0) i++;
	}
	if (i == N) return 1;
	else return -1;
}

//funzioni point3
void groupgen(char**string, int *state, char*arg, int lv)
{
	int x = 0;

	if (state == NULL)
	{
		state = malloc(N*sizeof(int));
		for (x = 0;x < N;x++)
		{
			state[x] = -1;
		}
	}
	
	for (x = lv;x < N;x++)
	{
		state[x] = lv;

		//printf("%d ", x);//debug only

		checkapp(string, state, arg);

		groupgen(string, state, arg, x+1);
		state[x] = -1;
	}
}

void checkapp(char **string, int *state, char*arg) //per il caso facoltativo utilizzo un vettore flag in cui segno i char non disponibili e regolo la stampa grazie a un if(disopnibile) 
{
	int i,control=0,y=0;
	

	for (i = 0;i < N;i++)
	{
		if (state[i] >= 0) {
			y++;
			if (strstr(arg, string[i]) != NULL) control++;
		}	
	}
	if (control == y) {
		printf("gli elementi dell'insieme  "); for (i = 0;i < N;i++) if (state[i] >= 0) printf("%s ", string[i]); printf(" sono contenuti in '%s'\n", arg);
	}
}