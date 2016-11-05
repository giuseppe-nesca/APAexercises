#include <stdio.h>
#include <stdlib.h>
#include "list.h"



//void FILEaq(STR *s, char*filename)
//{
//	FILE *f = fopen(filename, "r"); if (f == NULL) { puts("errore lettura file"); system("pause");exit(1); }
//	int i, I, tmp;
//	fscanf(f, "%d", &s->N);
//	s->e = malloc(s->N*sizeof(ESER));
//	ESER*e = s->e;
//	for (i = 0;i < s->N;i++)
//	{
//		fscanf(f, "%s %d %d", e[i].nome, &e[i].kal, &e[i].nfasi);
//		for (I = 0;I < NFASI;I++)
//		{
//			//fscanf(f, "%d", &e[i].f[I]);
//			e[i].f[I] = 0;
//		}
//		for (I = 0;I < e[i].nfasi;I++)
//		{
//			fscanf(f, "%d", &tmp);
//			e[i].f[tmp - 1]++;
//		}
//
//	}
//
//	for (i = 0;i < s->N;i++)
//	{
//		printf("%s %d %d ", e[i].nome, e[i].kal, e[i].nfasi);
//		//for (I = 0;I < e[i].nfasi;I++)
//		for (I = 0;I < NFASI;I++)
//		{
//			if (e[i].f[I]>0)
//				printf("%d ", I);
//
//			//printf("%d ", e[i].f[I]);
//		}
//		printf("\n");
//	}
//
//
//	fclose(f);
//	return;
//}

void solcomp(plist s, int n, int m);

void FILEreader(plist l,char*filename)
{
	FILE *f=fopen(filename,"r");
	int n;
	int i;
	fscanf(f, "%d", &n);
	for (i = 0;i < n;i++)
	{
		LISTinsert(ITEMnew(f), l);
	}
}


int main(int argc, char**argv)
{
	plist lista = LISTinit();
	int m, n;
	FILEreader(lista, argv[1]);

	printf("inserisci numero di esercizi massimo per fase: "); scanf("%d", &n);
	printf("inserisci numero di kalorie bruciate massime per fase: "); scanf("%d", &m);
	
	solcomp(lista, n, m);
	return 0;
}



void solcomp(plist s, int n, int m)
{
	int tot = 0;
	int a = 0, b = 0;

	for (a = 0;a < NFASI;a++)
	{
		tot = 0;
		printf("FASE %d:\n", a + 1);
		for (b = 0;b < n;b++)
		{
			if (find(s,&tot,a,m)==0) b=NFASI;
		}
	}
}