#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include <string.h>

typedef struct
{
	int gg, mm, aaaa;
}data;
typedef struct dati
{
	char matricola[8];
	char *nome;
	char *cognome;
	data dat;
	char sesso;
}studenti;

void selettore(studenti *studente, int N);
void sortmat(studenti *studente, int N);
void changestruct(studenti *x, studenti *i);
void sortalfa(studenti *studente, int N);
int sortalphar(char *a, char *i, int flag, int l);
void sortdata(studenti*studente, int N);


int main()
{
	studenti *studente;
	void *punt;
	FILE *f;
	f = fopenr("in.txt");
	int N=0, i;
	char no[36], co[36];
	fscanf(f, "%d", &N);
	studente = malloc(N*sizeof(studenti)); //punt = studente;
	for (i = 0;i < N;i++)
	{
		studente[i].nome = malloc(36 * sizeof(char));
		studente[i].cognome = malloc((36)*sizeof(char));
		if ((fscanf(f, "%s%s%s %d/%d/%d %c", studente[i].matricola, no, co, &studente[i].dat.gg, &studente[i].dat.mm, &studente[i].dat.aaaa, &studente[i].sesso)) != EOF)
		{
			strncpy(studente[i].nome, no, 35);
			strncpy(studente[i].cognome, co, 35);
		}
	}
	fclose(f);

	selettore(studente, N);
	

	for (i = 0;i < N;i++)
	{
		free(studente[i].nome);
		free(studente[i].cognome);
	}
	free(studente);
	system("pause");
	return 0;
}

void selettore(studenti *studente, int N)
{
	int selezione;
	printf("Digita:\n1. per ordinare per numero di matricola\n2. per ordinare per cognome e nome\n3. per ordinare in base alla data di nascita\n");
	scanf("%d", &selezione);
	if (selezione != 1 && selezione != 2 && selezione != 3)
	{
		puts("comando selezionato inesistente.");
		exit(1);
	}
	switch (selezione)
	{
	case 1: sortmat(studente, N);
		break;
	case 2: sortalfa(studente, N);
		break;
	case 3: sortdata(studente, N);
		break;
	}
	
}

void sortmat(studenti *studente,int N)
{
	int flag = -1;
	int i, a;
	int ma, mi;
	for (i = 0;i < N;i++)
	{
		sscanf(studente[i].matricola, "%*c%d", &mi);
		for (a = i+1;a < N;a++)
		{
			sscanf(studente[a].matricola, "%*c%d", &ma);
			if (ma < mi)
			{
				flag=a;
			}
			
		}
		if (flag != -1)
		{
			changestruct(&studente[flag], &studente[i]);
			flag = -1;
		}
	}
}
void changestruct(studenti *x, studenti *i)
{
	studenti temp;
		temp = *x;
		*x = *i;
		*i = temp;
}
void sortalfa(studenti *studente, int N)
{
	int l, a, i, flag = -1;
	
	for (i = 0;i < N;i++)
	{
		for (a = i + 1;a < N;a++)
		{
			if (studente[a].cognome[0] < studente[i].cognome[0])
				flag = a;
			if (studente[a].cognome[0] == studente[i].cognome[0])
			{
				if (strlen(studente[a].cognome) <= strlen(studente[i].cognome))
					l = strlen(studente[a].cognome);
				else l = strlen(studente[i].cognome);
				if (strncmp(studente[a].cognome, studente[i].cognome, l))
				{
					flag=sortalphar(studente[a].nome, studente[i].nome,a,l);
				}
				else flag=sortalphar(studente[a].cognome, studente[i].cognome,a,l);
			}
		}
		if (flag != -1)
		{
			changestruct(&studente[flag], &studente[i]);
			flag = -1;
		}
	}
}
int sortalphar(char *a, char *i,int flag,int l)
{
	int c;
	for (c = 1; c < l; c++)
	{
		if (a[c] > i[c])
			return flag;
		if (a[c] < i[c])
			return -1;
	}
	if (strlen(a) < strlen(i))
		return flag;
	return -1;
}

void sortdata(studenti*studente, int N)
{
	int i, a, flag = -1;

	for (i = 0;i < N; i++)
	{
		for (a = i + 1;a < N;a++)
		{
			if (studente[a].dat.aaaa < studente[i].dat.aaaa)
				flag = a;
			if (studente[a].dat.aaaa == studente[i].dat.aaaa)
			{
				if (studente[a].dat.mm < studente[i].dat.mm)
					flag = a;
				if (studente[a].dat.mm == studente[i].dat.mm)
				{
					if (studente[a].dat.gg < studente[i].dat.gg)
						flag = a;
				}
			}
			if (flag != -1)
			{
				changestruct(&studente[flag], &studente[i]);
				flag = -1;
			}
		}
	}
}