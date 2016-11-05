//#define DBG 0
#include <stdio.h>
#include <stdlib.h>

typedef struct VINC
{
	int num;
	int *vett;
}vinc;

typedef struct DATA
{
	int N, M;
	vinc *n, *m;
}data;

void aq(data *d, char*filename);
void fun(int **mat, data *d, int X, int Y);
int **allocamat(int N, int M,data*d);
void check(data*d, int **mat);
int checkline(int *v, data*d, int i);
int checkcolumn(int **v, data*d, int i);
void filestamp(int **m, int N, int M);


char *fileout;
#ifdef DBG
	int NUMBER = 0;
#endif
int main(int argc, char**argv)
{
	data d;
	int **mat;
	fileout = argv[2];
	aq(&d, argv[1]);
	mat = allocamat(d.N,d.M,&d);
	fun(mat, &d, -1, 0);

	system("pause");
	return 0;
}

void aq(data *d, char * filename)
{
	FILE*f; int i, c;
	f = fopen(filename, "r"); if (f == NULL) { puts("errore file in lettura"); exit(1); }
	fscanf(f, "%d", &d->N);
	d->n = malloc(d->N*sizeof(vinc));
	for (i = 0;i < d->N;i++)
	{
		fscanf(f, "%d", &d->n[i].num);
		d->n[i].vett = malloc(d->n[i].num*sizeof(vinc));
		for (c = 0;c < d->n[i].num;c++)
		{
			fscanf(f, "%d", &d->n[i].vett[c]);
		}
	}
	fscanf(f, "%d", &d->M);
	d->m = malloc(d->M*sizeof(vinc));
	for (i = 0;i < d->M;i++)
	{
		fscanf(f, "%d", &d->m[i].num);
		d->m[i].vett = malloc(d->m[i].num*sizeof(vinc));
		for (c = 0;c < d->m[i].num;c++)
		{
			fscanf(f, "%d", &d->m[i].vett[c]);
		}
	}
	fclose(f);
#if DBG == 1
	printf("\nN = %d\n", d->N);
	for (i = 0;i < d->N;i++)
	{
		printf("%d  ", d->n[i].num);
		for (c = 0;c < d->n[i].num;c++)
		{
			printf("%d ", d->n[i].vett[c]);
		}
		printf("\n");
	}
	printf("\n\nM = %d\n", d->N);
	for (i = 0;i < d->M;i++)
	{
		printf("%d  ", d->m[i].num);
		for (c = 0;c < d->m[i].num;c++)
		{
			printf("%d ", d->m[i].vett[c]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

int **allocamat(int N, int M, data *d)
{
	int x, y;
	int**mat = malloc(M*sizeof(int*));
	for (y = 0;y < M;y++)
	{
		mat[y] = malloc(N*sizeof(int));
		for (x = 0;x < N;x++)
		{
			mat[y][x] = 0;
		}
	}
#if DBG == 1
	for (y = 0;y < d->M;y++)
	{
		for (x = 0;x < d->N;x++)
		{
			printf("%d ", mat[y][x]);
		}
		printf("\n");
	}
#endif
	return mat;
}

void fun(int **mat,data *d,int X,int Y)
{
	int x, y;

	//if (X == d->N - 1 && Y == d->M - 1)
	{
#ifdef DBG
		NUMBER++;
#endif
#if DBG==1
		
		{
			printf("\n");
			for (y = 0;y < d->M;y++)
			{
				for (x = 0;x < d->N;x++)
				{
					printf("%d ", mat[y][x]);
				}
				printf("\n");
	}
			printf("\n");
}
#endif
	
	}

	check(d,mat);

	for (y = Y;y < d->M;y++)
	{
		for (x = X+1;x < d->N;x++)
		{
			mat[y][x] = 1;
			fun(mat, d, x, y);
			mat[y][x] = 0;
		}
		X = -1;
	}
}

void check(data*d, int **mat)
{
	int y, x;

	for (y = 0;y < d->M;y++)
	{
		if (checkline(mat[y], d, y) == 1) return;
	}
	for (y = 0;y < d->N;y++)
	{
		if (checkcolumn(mat, d, y) == 1) return;
	}
#if DBG == 1
	puts("yeeee");
#endif
#ifdef DBG
	printf("\n");
	for (y = 0;y < d->M;y++)
	{
		for (x = 0;x < d->N;x++)
		{
			printf("%d ", mat[y][x]);
		}
		printf("\n");
	}
	system("pause");
#endif
	filestamp(mat,d->N,d->M);
}

int checkline(int *v,data*d,int i)
{
	int x, flag=0,y=0;
	for (x = 0;x < d->N;x++)
	{
		if (v[x] == 0)
		{
			if (flag == d->n[i].vett[y])
			{
				y++;
			}
			else if (flag > 0) return 1;
			flag = 0;
		}
		if (v[x] == 1)
		{
			flag++;
		}
	}
	if (flag == d->n[i].vett[y])
	{
		y++;
	}
	if (y == d->n[i].num) return 0;
	return 1;
}

int checkcolumn(int **v, data*d, int i)
{
	int x, flag = 0, y = 0;
	for (x = 0;x < d->M;x++)
	{
		if (v[x][i] == 0)
		{
			if (flag == d->m[i].vett[y])
			{
				y++;
			}
			else if (flag > 0) return 1;
			flag = 0;
		}
		if (v[x][i] == 1)
		{
			flag++;
		}
	}
	if (flag == d->m[i].vett[y])
	{
		y++;
	}
	if (y == d->m[i].num) return 0;
	return 1;
}

void filestamp(int **m, int N, int M)
{
	FILE*f = fopen(fileout, "w");
	int x, y;
	for (y = 0;y < M;y++)
	{
		for (x = 0;x < N;x++)
		{
			fprintf(f, "%d ", m[y][x]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
	exit(0);
}