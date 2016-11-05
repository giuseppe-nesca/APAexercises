#define DBG 0
#include <stdio.h>
#include <stdlib.h>

void aq();
void gen(int *flag, int **tav, int used);
int insert(int i, int*tav);
void freep(int i, int *tav);
void check(int**tav);
int sum(int*tav);
int sum2(int x, int*tav);
void savet(int **tav);




int N; //numero ospiti
int K; //numero tavoli
int M; //capienza tavoli
int **mat;
int **UMAX=NULL; //umor minimo

int main()
{
	int i,t;
	aq(); //acquisizione da file
	
	gen(NULL, NULL, 0);

	printf("la disposizione migliore e':\n"); //-1 indica posto vuoto
	for (t = 0;t < K;t++)
	{
		printf("tavolo %d:", t);
		for (i = 0;i < M;i++)
		{
			printf(" %d", UMAX[t][i]);
		}
		printf("\n");
	}
	
	system("pause");
	return 0;
}

void aq()
{
	int x,y;
	FILE*f = fopen("banchetto.txt", "r");	if (f == NULL) { puts("errore lettura file."); exit(1); }
	
	
	fscanf(f, "%d %d %d", &N, &K, &M);
	mat = malloc(N*sizeof(int*));
	for (x = 0;x < N;x++)
	{
		mat[x] = malloc(N*sizeof(int));
		for (y = 0;y < N;y++)
		{
			fscanf(f, "%d", &mat[x][y]);
		}
	}
	fclose(f);

#ifdef DBG
	for (x = 0;x < N;x++) {
		for (y = 0;y < N;y++) { printf("%d ", mat[x][y]); }
		printf("\n");
	}
#endif
	return;
}

void gen(int *flag, int **tav,int used)
{
	int i,t,vdbg;

	if (used == N) //terminazione
	{
		//check umor
		check(tav);


#ifdef DBG
		for (t = 0;t < K;t++)
		{
			printf("tavolo %d:", t);
			for (i = 0;i < M;i++)
			{
				printf(" %d",tav[t][i]);
			}
			printf("\n");
		}
#endif
		return;
	}

	if (flag == NULL)
	{
		flag = malloc(N*sizeof(int)); for (i = 0;i < N;i++) flag[i] = -1;
	}
	if (tav == NULL)
	{
		tav = malloc(K*sizeof(int*));
		for (i = 0;i < K;i++)
		{
			tav[i] = malloc(M*sizeof(int));
			for (t = 0;t < M;t++) tav[i][t] = -1;
		}
	}
	//ricordati le free

	for (i = used;i < N;i++)
	{
		if (flag[i] == -1)
		{
			for (t = 0;t < K;t++)
			{
				if (insert(i, tav[t]) == 0)// return; //int insert() da costrurire
				{
					flag[i] = t;
#if DBG 1
					printf("ho inserito %d in %d: flag=%d  tav[%d]= ", i, t, flag[i], t);
					for (vdbg = 0;vdbg < M;vdbg++) printf("%d", tav[t][vdbg]);
					printf("\n");
#endif

					gen(flag, tav, used + 1);
					flag[i] = -1;
					freep(i, tav[t]);
				}
			}
		}
	}

}

int insert(int i, int*tav)
{
	int x = 0;

	for (x = 0;x < M;x++)
	{
		if (tav[x] == -1)
		{
			tav[x] = i;
			return 0;
		}
	}
	return 1;
}

void freep(int i, int *tav)
{
	int x;
	for (x = 0;x < M;x++)
	{
		if (tav[x] == i)
		{
			tav[x] = -1;
			return;
		}
	}
	puts("errore. non trova persona a tavolo da togliere.");
	return;
}

void check(int**tav)
{
	static float max = 0;
	float umor=0;
	int num=0;
	int x = 0;
	for (x = 0;x < K;x++) 
	{
		umor = umor + sum(tav[x]);
		num++;
	}
	umor = umor / num;
	if (umor > max)
	{
		max = umor;
		savet(tav);
	}
}

int sum(int*tav)
{
	int x;
	int s=0;
	for (x = 0;x < M;x++)
	{
		if (tav[x] != -1)
			s = s + sum2(x, tav);
	}
	return s;
}

int sum2(int x, int*tav)
{
	int s = 0;
	int i;
	for (i = 0;i < M;i++)
	{
		if(tav[i]!=-1)
			s = s + mat[tav[x]][tav[i]];
	}
	return s;
}

void savet(int **tav)
{
	int x, y;
	if (UMAX == NULL)
	{
		UMAX = malloc(K*sizeof(int*));
		for (x = 0;x < K;x++)
		{
			UMAX[x] = malloc(M*sizeof(int));
		}
	}
	for (x = 0;x < K;x++)
	{
		for (y = 0;y < M;y++)
		{
			UMAX[x][y] = tav[x][y];
		}
	}
}