//FUTOSHIKI

#include <stdio.h>
#include <stdlib.h>
#define DBGs

int *** aq(int *dimension_pointer);
void ps(int **mat, int ***data, int N, int X, int Y, int **ver);
int rapidcheck(int **m, int x, int y, int N, int ***data);
int check(int **mat, int ***data, int N);
int checkc(int **m, int N, int *ver, int x, int ***dat);
int checkoperators(int y, int x, int **m, int*dat);

int FLAG = 2;

int main()
{
	int y, x;
	int N;
	int ***data = aq(&N);
	int **mat;
	//mat allocation n inizialization
	mat = malloc(N*sizeof(int));
	for (y = 0;y < N;y++)
	{
		mat[y] = malloc(N*sizeof(int));
		for (x = 0; x < N; x++)
		{
			mat[y][x] = data[y][x][0];
		}
	}
	//

	//
#ifdef DBG0
	for (y = 0;y < N;y++)
	{
		for (x = 0;x < N;x++)
		{
			printf("%d ", data[y][x][0]);
		}
		printf("\n");
	}
#endif


	ps(mat, data, N, 0, 0, NULL);

	system("pause");
	return 0;
}

int *** aq(int *dim) 
{
	FILE*f = fopen("futoshiki444.txt", "r");
	if (f == NULL) {
		puts("errore lettura file."); 
		system("pause");
		exit(1); }
	int y, x;		//y righe	//x colonne		//data[y][x]
	int i, N;
	int ***data;

	fscanf(f, "%d", &N);
	data = malloc(N*sizeof(int**));
	for (y = 0;y < N;y++)
	{
		data[y] = malloc(N * sizeof(int*));
		for (x = 0;x < N;x++)
		{
			data[y][x] = malloc(5 * sizeof(int));
			fscanf(f, "%d", data[y][x]);
			for (i = 1; i < 5;i++)
				fscanf(f, "%d", &data[y][x][i]);
		}
	}
	fclose(f);
	*dim = N;
	return data;
}

void ps(int **mat, int ***data, int N, int X, int Y, int **ver)
{
	int x, y, i;
	if (ver == NULL)
	{
		ver = malloc(N*sizeof(int*));
		for (y = 0;y < N;y++)
		{
			ver[y] = malloc(N*sizeof(int));
			for (x = 0;x < N;x++)
				ver[y][x] = 0;
		}
	}

#ifdef DBG2
	for (y = 0;y < N;y++)
	{
		for (x = 0;x < N;x++)
			printf("%d ", mat[y][x]);
		printf("\n");
	}
#endif
	if (X == N && Y == N - 1)
	{
#ifdef DBG
		for (y = 0;y < N;y++)
		{
			for (x = 0;x < N;x++)
			{
				printf("%d ", mat[y][x]);
			}
			printf("\n");
		}
		printf("\n");
		
#endif
		check(mat, data, N);
		return;
	}
	for (y = Y;y < N;y++)
	{
		for (x = X;x < N;x++)
		{

			for (i = 0;i < N;i++)
			{
				if (ver[y][i] == 0)
				{
					ver[y][i] = 1;
					mat[y][x] = i + 1;
					ps(mat, data, N, x + 1, y, ver);
					mat[y][x] = 0;
					ver[y][i] = 0;
				}
			}
			return;
		}
		if (rapidcheck(mat, x, y, N, data) == 1) return;
		X = 0;
	}
}

int rapidcheck(int **m, int x, int y, int N, int ***data)
{
	for (x = 0;x < N;x++)
	{
		if (data[y][x][0] != 0)
		{
			if (data[y][x][0] != m[y][x])
			{
#ifdef DBG3
				for (y = 0;y < N;y++)
				{
					for (x = 0;x < N;x++)
					{
						printf("%d ", m[y][x]);
					}
					printf("\n");
				}
				printf("\n");
#endif
				return 1;
			}
		}
		if (check(m, data, N) == 1) {

			return 1;
		}
	}
	return 0;
}

int check(int **mat, int ***data, int N)
{
	int x, y,f;
	static int *ver = NULL;
	if (ver == NULL) ver = malloc(N*sizeof(int));


	//cherckc();
	for (x = 0;x < N;x++)
	{
		f = checkc(mat, N, ver, x, data);
		if (f == 1) return 1;
		if (f == -1) return 0;
	}
	puts("soluzione trovata!");
	for (y = 0;y < N;y++)
	{
		for (x = 0;x < N;x++) printf("%d ", mat[y][x]);
		printf("\n");
	}

	if (FLAG >= 2)
	{
		printf("come si vuole procedere? Digita:\n"
			"0. termina il programma\n"
			"1. trova tutte le soluzioni\n"
			"2. cerca un'altra soluzione\n");
		scanf("%d", &FLAG);
	}
	if (FLAG == 0) exit(0);

	return 0;
}

int checkc(int **m, int N, int *ver, int x, int ***dat)
{
	int i;
	for (i = 0;i < N; i++) ver[i] = 0;
	for (i = 0;i < N;i++)
	{
		if (m[i][x] == 0)
			return -1;
		if (ver[m[i][x] - 1] != 0) return 1;
		if (checkoperators(i, x, m, dat[i][x]) == 1) return 1;
		ver[m[i][x] - 1]++;
	}
	return 0;
}

int checkoperators(int y, int x, int **m, int*dat)
{ //assumo che i dati acquisiti siano veramente corretti, quindi non c'? bisogno di gestire casi di borto in maniera particolare
	int N = dat[1];
	int O = dat[2];
	int S = dat[3];
	int E = dat[4];

	if (N == 1)
	{
		if (m[y][x]>m[y - 1][x]);
		else return 1;
	}
	if (N == -1)
	{

		if (m[y][x]<m[y - 1][x] && m[y - 1][x] != 0); //
		else return 1;
	}
	if (O == 1) if (m[y][x] <= m[y][x - 1]) return 1;
	if (O == -1) if (m[y][x] >= m[y][x - 1] && m[y][x-1]!=0) return 1;

	if (S == 1) if (m[y][x] <= m[y + 1][x]) return 1;
	if (S == -1) if (m[y][x] >= m[y + 1][x] && m[y+1][x]!=0) return 1;

	if (E == 1) if (m[y][x] <= m[y][x + 1]) return 1;
	if (E == -1) if (m[y][x] >= m[y][x + 1] && m[y][x+1]!=0) return 1;

	return 0;
}