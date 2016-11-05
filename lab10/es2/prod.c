#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct Tbp
{
	linkprod l;
	int nP;
}tabpr;

typedef struct Prodotti
{
	char *nome; //nome=strdup("stirnga");
	float prezzo;
}prod;




l_tabp aqprod(FILE *f)
{
	int i = 0;
	char s[30];
	l_tabp tab=malloc(sizeof(tabpr));
	linkprod t;
	int N;
	fscanf(f, "%d", &tab->nP);
	N= tab->nP;
	tab->l=malloc(N*sizeof(prod)); //non scrivo la freeprod perchè mi serve fino all exit.
	t = tab->l;
	
	
	

	for (i = 0;i < N;i++)
	{
		fscanf(f,"%s %f", s, &t[i].prezzo);
		t[i].nome = strdup(s);
	}
	
	return tab;
}

int  searchnpr(char *s, l_tabp tp)
{
	linkprod p = tp->l ;
	int N = tp->nP ;
	int i = 0;
	for (i = 0;i < N;i++)
	{
		if (strcmp(s, p[i].nome) == 0) return i;
	}
	//if faild for search
	puts("errore nessuna corrispondenza.");
	system("pause"); exit(1);
}

char* searchpnpr(int i, l_tabp p)
{
	return p->l[i].nome;
}

float price(int i, l_tabp p)
{
	return p->l[i].prezzo;
}