#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

node* insert_e(node *l)
{
	node*start = l;
	if (l == NULL)
	{
		l = malloc(sizeof(node));
		l->tab = insert_i();
		l->next = NULL;
		return l;
	}

	while (l->next != NULL) l = l->next;
	l->next = malloc(sizeof(node));
	l->next->tab = insert_i();
	l->next->next = NULL;
	return start;
}

node* delt_ef(node*l)
{
	node*x = l;
	l = l->next;
	free(x);
	return l;
}

void delt_e(node*l)
{
	node *x;
	x = l->next;
	l->next = x->next;

	free(x);
	return;
}

void print_e(node*l)
{
	int count = 0;
	while (l != NULL)
	{
		print_i(&l->tab);
		count++;
		l = l->next;
	}
	printf("numero di nodi = %d\n", count);
	return;
}

void save_e(node*l)
{
	node*start = l;
	FILE*f = fopen("list.txt", "w");
	while (l != NULL)
	{
		if(l!=start) fprintf(f, "\n");
		f=save_i(f,&l->tab);
		l = l->next;
	}
	fclose(f);
	return;
}

node* freader_e(node *l)
{
	FILE*f;
	node *start;
	char fname[30];
	printf("inserisci nome file: "); scanf("%s", fname);
	if ((f = fopen(fname, "r")) == NULL)
	{
		puts("errore: nessun dato");
		return l;
	}
	
	while (!feof(f))
	{
		if (l == NULL)
		{
			start = l = malloc(sizeof(node)); 
			f = freader_i(f, &l->tab);
			//l = l->next;
		}
		else
		{
			l->next = malloc(sizeof(node));
			f = freader_i(f, &l->next->tab);
			l = l->next;
		}
	}
	l->next = NULL;
	fclose(f);
	return start;
}

node * extract_e(node *l)
{
	node*x = l;
	int p=calcp_e(l);
	if (p == prio(&l->tab))
	{
		l=delt_ef(l);
		return(l);
	}
	while (l->next != NULL)
	{
		if (p == prio(&l->next->tab))
		{
			delt_e(l);
			return x;
		}
		l = l->next;
	}
	puts("nessun elemento da eliminare trovato.");
	return x;
}

int calcp_e(node*l)
{
	int p=-1;
	if (l != NULL) p=l->tab.piority;
	else { puts("errore: lista vuota."); return -1; }
	while (l->next != NULL)
	{
		//if(l->next->tab.piority>p) p=l->next->tab.piority;
		if (prio(&l->next->tab) < p) p = prio(&l->next->tab);
		l = l->next;
	}
	return p;
}