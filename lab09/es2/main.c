//questa è la versione funzionante!

#define DBG
#include <stdio.h>
#include <stdlib.h>
#define R 1
#define G 2
#define B 3
#define M R+G+B
#define N 3

void gen(int*v, char*c, int liv);

int main()
{
	int v[N];
	char c[M+1];
	c[M] = '\0';
	v[0] = R;
	v[1] = G;
	v[2] = B;

	gen(v,c,0);

	return 0;
}

void gen(int*v,char*c,int liv)
{
	int i = 0;
	
	if (liv == M) 
	{
		printf("%s\n", c);
		return;
	}

	
	for (i = 0;i < N;i++)
	{
		switch (i)
		{
		case 0: //Red
			//if (liv == M - 1);
			if (liv != 0 && liv != 1 && liv !=M-1) {
				c[liv] = 'R';
				v[i]--;
				if(v[i] >=0) gen(v, c, liv + 1);
				v[i]++;
			}
			break;
		case 1: //Green
			c[liv] = 'G';
			v[i]--;
			if (v[i] >= 0) gen(v, c, liv + 1);
			v[i]++;
			break;
		case 2: //Blue
			c[liv] = 'B';
			v[i]--;
			if (v[i] >= 0) gen(v, c, liv + 1);
			v[i]++;
			break;
#ifdef DBG		
		default: puts("errore: non dovrebbe entrare in default!"); //debug only
#endif
		}
		/*if (liv == N - 1)
		{
			printf("%s", c);
			return;
		}*/
		//gen(v, c, liv + 1);
	}
}