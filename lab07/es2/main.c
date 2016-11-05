#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodi *link;

typedef struct Data
{
	int n;
	link start;
	link end;

}data;

typedef struct Nodi
{
	char *stringa;
	link next;
	link prev;
}nod;

void alloca(link x, data *d);
void printall(link t);
void save(link t);

int main()
{
	int select=1;
	link x;
	data dati;
	char s[31];
	FILE* f = fopen("stringhe.txt", "r");
	dati.n = 0;
	dati.start = NULL; dati.end = NULL;
	while (fscanf(f, "%s", s) > 0)
	{
		x = malloc(sizeof(nod));
		x->stringa = strdup(s);
		x->next = NULL; x->prev = NULL;
		alloca(x, &dati);
	}
	printall(dati.start);

	while (select != 0)
	{
		printf("digita:\n"
			"1. inserisci nuovo elemento\n"
			"2. salva\n"
			"0. exit\n"); scanf("%d", &select);
	switch (select)
	{
	case 1: printf("inserisci: ");
		scanf("%s", s); x = malloc(sizeof(nod)); x->stringa = strdup(s);
		alloca(x, &dati); break;
	case 2: save(dati.start); break;
	case 0:  exit(0); break;
	default: printf("inserimento non valido\n\n");
	}

	}
	
	return 0;
}

void alloca(link x, data *d)
{
	link t;
	if (d->start == NULL)
	{
		d->start = x;
		d->end = x;
		d->n++;
		return;
	}
	t = d->start;
	while(t != NULL)
	{
		if ((strcmp(t->stringa, x->stringa)) == 0) return;
		if (strcmp(t->stringa, x->stringa) >  0) 
		{
			t->prev->next = x; 
			x->prev = t->prev;
			t->prev = x;
			x->next = t;
			d->n++;
			return;
		}
		if (t->next == NULL)
		{
			t->next = x;
			x->prev = t;
			x->next = NULL;
			d->n++;
			d->end = x;
			return;
		}
		
		t = t->next;
	}
	
	return;
}

void save(link t)
{
	FILE* f = fopen("salvataggio.txt", "w");
	while (t != NULL)
	{
		fprintf(f, "%s\n", t->stringa);
		t = t->next;
	}
	fclose(f);
}

void printall(link t)
{
	while (t != NULL)
	{
		printf("%s\n", t->stringa);
		t = t->next;
	}
	printf("\n\n");
}