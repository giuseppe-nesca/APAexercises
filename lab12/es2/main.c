#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define NFASI 4

typedef struct ESERCIZIO
{
	char nome[MAX];
	int kal;
	int nfasi;
	int f[NFASI];
}ESER;

typedef struct str
{
	int N;
	ESER*e;
}STR;

//struct PSSTRUCT {
//	
//};

void PSloader( STR *s, int n, int m);

void checksolution(STR *s, int n, int m);

void FILEaq( STR *s, char*filename)
{
	FILE *f = fopen(filename, "r"); if (f == NULL) { puts("errore lettura file"); system("pause");exit(1); }
	int i,I,tmp;
	fscanf(f, "%d", &s->N);
	s->e = malloc(s->N*sizeof(ESER));
	ESER*e=s->e;
	for (i = 0;i < s->N;i++)
	{
		fscanf(f,"%s %d %d", e[i].nome, &e[i].kal, &e[i].nfasi);
		//e[i].f = malloc(e->nfasi*sizeof(int));
		//for (I = 0;I < e[i].nfasi;I++)
		for (I = 0;I < NFASI;I++)
		{
			//fscanf(f, "%d", &e[i].f[I]);
			e[i].f[I] = 0;
		}
		for (I = 0;I < e[i].nfasi;I++)
		{
			fscanf(f, "%d", &tmp);
			e[i].f[tmp-1]++;
		}

	}

	for (i = 0;i < s->N;i++)
	{
		printf("%s %d %d ", e[i].nome, e[i].kal, e[i].nfasi);
		//for (I = 0;I < e[i].nfasi;I++)
		for (I = 0;I < NFASI;I++)
		{
			if (e[i].f[I]>0)
				printf("%d ", I);
			
			//printf("%d ", e[i].f[I]);
		}
		printf("\n");
	}


	fclose(f);
	return;
}

int main(int argc, char**argv)
{
	int n; //max esercizi per fase
	int m; //massimo calorie per fase
	STR s;
	
	FILEaq(&s,argv[1]);

	printf("inserisci numero massimo di esercizi per fase: "); scanf("%d", &n);
	printf("inserisci numero massimo di calorie per fase: "); scanf("%d", &m);

	PSloader(&s, n, m);

	checksolution(&s, n, m);
	
	system("pause");
	return 0;
}

int totcalc(int *vsum,int *perm, STR *s,int m)
{
	int i;
	int tot=0;

	for (i = 0;i < s->N;i++)
	{
		if (perm[i] >= 0) {
			vsum[perm[i]] += s->e[i].kal;
			tot += s->e[i].kal;
			if (vsum[perm[i]]>m) return -1;
		}
	}
	
	return tot;
	/*for (i = 0;i < NFASI;i++)
	{
		tot += vsum[i];
	}
	return tot;*/
}

void test(STR *s, int m, int *vsumNot, int *perm, int *solution)
{
	static int totmax = 0;
	//static int *solmax = NULL;
	int tot;
	int vsum[NFASI] = {0};
	tot = totcalc(vsum,perm,s,m);
	if (tot > totmax) totmax = tot;
	else return;
	for (tot = 0;tot < s->N;tot++)
	{
		solution[tot] = perm[tot];
	}

}

int permitted(int i, STR *s, int a)
{
	if (s->e[a].f[i]>0) return 0;
	else return 1;
}

void PS( STR *s,int n, int m, int *vsum, int *perm,int *sfasi, int a,int *solution)
{
	int i;
	if (a == s->N) //condizione di terminazione
	{
		test(s, m, vsum, perm, solution);
		return;
	}
	
	PS(s, n, m, vsum, perm, sfasi, a + 1,solution);

	for (i = 0;i < NFASI;i++)
	{
		
		if (permitted(i,s,a)==0)
		{
			perm[a] = i;
			sfasi[i]++;
			if (sfasi[i] <= n)
				PS(s, n, m, vsum, perm, sfasi, a + 1, solution);
			sfasi[i]--;
		}
	}
	perm[a] = -1;

}

void printsolution(int *solution, STR*s,int n)
{
	int i,a;

	for (i = 0;i < NFASI;i++)
	{
		printf("FASE %d:\n", i);
		for (a = 0;a < s->N;a++)
		{
			if (solution[a] == i) printf("%s %d\n", s->e[a].nome, s->e[a].kal);
		}
	}
}

void PSloader( STR *s, int n, int m)
{
	int sfasi[NFASI] = { 0 };
	int i;
	int *perm = malloc(s->N*sizeof*perm);
	for (i = 0;i < s->N;i++)
		perm[i] = -1;
	int vsum[NFASI] = { 0 };
	int *solution = malloc(s->N*sizeof(int));
	for (i = 0;i < s->N;i++) solution[i] = -1;

	PS(s, n, m, vsum, perm, sfasi, 0, solution);

	printsolution(solution,s,n);
}

int itemfind(char*s,STR *str)
{
	if (strcmp(s, "NULL") == 0) return -1;
	int i=0;
	while (i < str->N)
	{
		if (strcmp(s, str->e[i].nome) == 0)return i;
		i++;
	}
	puts("errore: esercizio non valido.");
	exit(1);
}

void solutionreader(int **sol,STR *str,int n,int m)
{
	FILE*f=fopen("sol.txt","r");
	char s[MAX];
	int maxc = 0;
	int *perm = malloc(str->N*sizeof(int));
	int i=0, a=0;
	for (i;i < str->N;i++)
	{
		perm[i] = -1;
	}
	i = 0;
	while (fscanf(f, "%s", s)>0)
	{
		if (i == NFASI) { puts("soluzione non valida: troppe fasi."); return; }
		if (a == n && strcmp(s,"F_TERM")!=0) { puts("soluzione non valida, troppi esercizi in una fase."); return; }
		if (strcmp(s, "F_TERM") == 0) {
			i++; a = 0; maxc = 0;
		}
		else {
			if ((sol[i][a] = itemfind(s, str)) >= 0)
			{
				if (permitted(i, str, sol[i][a]) != 0) { puts("soluzione non valida: esercizio in fase errata."); return; }
			}
			if (perm[sol[i][a]] == -1)
			{
				perm[sol[i][a]] = i;
				maxc += str->e[sol[i][a]].kal;
				if (maxc > m) { puts("soluzione non valida: superato massimo calorie m per fase,"); return; }
			}
			else
			{
				puts("soluzione non valida: esercizio presente più volte."); return;
			}
			a++;
		}
	}
	puts("soluzione valida.");

}

void checksolution(STR *s, int n, int m)
{
	int **sol;
	sol = malloc(NFASI*sizeof(int*));
	int i,a;
	for (i = 0;i < s->N;i++)
	{
		sol[i] = malloc(s->N*sizeof(int));
	}
	solutionreader(sol,s,n,m);
}