#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"


FILE* fopenr(char nomefile[]);

studenti *acquisizione(char nomefile[])
{
	FILE *f;
	studenti *studente;
	f = fopenr(nomefile);
	int i;
	extern N;
	char no[36], co[36];
	fscanf(f, "%d", &N);
	studente = malloc(N*sizeof(studenti)); //punt = studente;
	for (i = 0;i < N;i++)
	{
		studente[i].flag = 1;
		studente[i].nome = malloc(36 * sizeof(char));
		studente[i].cognome = malloc((36)*sizeof(char));
		if ((fscanf(f, "%s%s%s %d/%d/%d %c", studente[i].matricola, no, co, &studente[i].dat.gg, &studente[i].dat.mm, &studente[i].dat.aaaa, &studente[i].sesso)) != EOF)
		{
			strncpy(studente[i].nome, no, 35);
			strncpy(studente[i].cognome, co, 35);
		}
	}
	fclose(f);
	return studente;
}

FILE *fopenr(char nomefile[])
{
	FILE *f;
	if ((f = fopen(nomefile, "r")) == NULL)
	{
		printf("errore apertura in lettura del file '%s'", nomefile);
		exit(1);
	}
	return f;
}

