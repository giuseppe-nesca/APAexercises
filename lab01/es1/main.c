#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAX 20

int findb(char v[]);

int main()
{
	char v[MAX] = { "0" }, c;
	int i,b=0, e = MAX - 1,v2[MAX],a=0;
	float v1[MAX];
	float tot=0;
	puts("Inserire numero: ");
	for (i = 0; i < MAX; i++)
	{
		v[i] = getchar();
		if (v[i] == '\n')
		{
			//e = i;
			e = e - MAX+i;
			i = MAX;
		}
	}
	for (i = 1; i < MAX; i++)
	{
		if (v[i] == '+' || v[i] == '-')
		{
			puts("errore formato imput");
			system("pause");
			exit(1);
		}
	}
	
	
	b = findb(v);
	if (b == 0)
	{
		puts("numero inserito nullo.");
		system("pause");
		return(0);
	}
	printf("la base e' %d\n", b);
	
	if (v[0] == '+' || v[0] == '-' || v[MAX-1]=='+' || v[MAX-1]=='-')
		e--;
	for (i = 0; i < MAX; i++)
	{
		if (isdigit(v[i]))
		{
			c = v[i];
			sscanf(&c, "%f", &v1[i]);
			v2[i] = e;
			e--;
		}
		else
		{
			if (v[i] == '.')
			{
				for (a = 0; a < i ;a++)
				{
					if (isdigit(v[a]))
						v2[a] = v2[a]-e-1;
				}
			}
		}
	}
	if (a!=0)
	{
		e = -1;
		for (i = a; i < MAX; i++)
		{
			if (isdigit(v[i]))
			{
				v2[i] = e;
				e--;
			}
		}
	}
	for (i = 0; i < MAX; i++)
	{
		if (isdigit(v[i]))
		{
			v1[i] = v1[i] * (float)pow(b, v2[i]);
			tot = tot + v1[i];
		}
		
	}
	if (v[0] == '-' || v[MAX - 1] == '-')
		tot = tot*(-1);


	

	printf("in base 10  = %f\n", tot);
	system("pause");
	return(0);
}

int findb(char v[])
{
	int i,a=0,b;
	char c;
	for (i = 0; i < MAX; i++)
	{
		if (isdigit(v[i]))
		{
		c = v[i];
		sscanf(&c, "%d", &b);
		if (b > a)
			a = b;
		}
	}
	return(a + 1);
}