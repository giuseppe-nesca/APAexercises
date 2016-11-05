#include <stdio.h>
#include <stdlib.h>
int **alloca2d(int R, int C);
void malloc2dP(int ***m, int R, int C);

int sum1dx(int r, int c, int **v, int R, int C);
int sum2dx(int r, int c, int **v, int R, int C);



int main()
{
	int a, b,somma=0;
	FILE*f;
	f = fopen("in.txt", "r");
	int R, C;
	int**m;
	fscanf(f, "%d%d", &R, &C);
	m = alloca2d(R, C);

	for (a = 0;a < R;a++)
	{
		for (b = 0;b < R;b++)
		{
			fscanf(f, "%d", &m[a][b]);
		}
	}
	for (b = 0;b < C;b++)
	{
		somma = somma + sum2dx(0, b, m, R, C);
	}
	for (b = 0;b < C;b++)
	{
		somma = somma + sum1dx(R - 1, b, m, R, C);
	}

	
		malloc2dP(&m, R, C);

		for (a = 0;a < R;a++)
		{
			for (b = 0;b < R;b++)
			{
				fscanf(f, "%d", &m[a][b]);
			}
		}
	
		for (a = 0;a < R;a++)
		{
			for (b = 0;b < R;b++)
			{
				fscanf(f, "%d", &m[a][b]);
			}
		}
		for (b = 0;b < C;b++)
		{
			somma = somma + sum2dx(0, b, m, R, C);
		}
		for (b = 0;b < C;b++)
		{
			somma = somma + sum1dx(R - 1, b, m, R, C);
		}
	
	return 0;
}
int **alloca2d(int R, int C)
{
	int **m,i;
	m = malloc(R*sizeof(int*));
	for (i = 0;i < R;i++)
	{
		m[i] = malloc(C*sizeof(int));
	}
	return m;
}
void malloc2dP(int ***M, int R, int C)
{ 
	int **m;   
	int i;  
	m = malloc(R*sizeof(int *));   
	for (i = 0; i<R; i++)
	{
		m[i] = malloc(C*sizeof(int));
	}  
	*M = m; 
}


int sum1dx(int r, int c, int **v, int R,int C)
{
	int sum = 0;
	while (c + 1<C && r>0)
	{
		sum = sum + v[(r - 1)][ c + 1];
		r--;
		c++;
	}
	return sum;
}

int sum2dx(int r, int c, int **v, int R,int C)
{
	int sum = 0;
	while (c + 1<C && r + 1<R)
	{
		sum = sum + v[(r + 1)][ c + 1];
		r++;
		c++;
	}
	return sum;
}
