#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include <string.h>


 struct ITEM
{
	char *nome;
	int kal;
	int nfasi;
	int f[NFASI];
};

 int ITEMconf(pitem a, pitem b)
 {
	 return (a->kal > b->kal);
 }

 int ITEMcheck(pitem i, int f, int *tot,int m)
 {
	 if (i->f[f] > 0 && (*tot+i->kal<m))
	 {
		 *tot += i->kal;
		 printf("%s %d kal\n", i->nome, i->kal);
		 return 1;
	 }
	 return 0;
 }

 pitem ITEMnew(FILE*f)
 {
	 char s[MAX];
	 pitem p = malloc(sizeof*p);
	 fscanf(f, "%s %d %d", s, &p->kal, &p->nfasi);
	 p->nome = strdup(s);
	 int i;
	 for (i = 0;i < NFASI;i++)
	 {
		 p->f[i] = 0;
	 }
	 int a;
	 for (i = 0;i < p->nfasi;i++)
	 {
		 fscanf(f, "%d", &a);
		 p->f[a-1]++;
	 }

	 return p;
 }