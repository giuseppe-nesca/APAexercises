#include "lab4_1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fopenr(char nomefile[]);
studenti* selettore2(studenti *studente, int *n);
studenti* ricercalinearenome(studenti *studente, int n);
studenti* ricercalinearecognome(studenti *studente, int N);
studenti* ricercalinearematricola(studenti*studente, int N);

studenti* dicomatricola(studenti * studente, int N,int num);
studenti* diconome(studenti*studente, int N, char s[]);


void change(studenti *x, studenti *i);

int mark = 0;
extern void selettore();


int main()
{
	//richiamo lab4_1
	studenti *studente;
	FILE *f;
	f = fopenr("in.txt");
	int N = 0,M=0, i;
	char no[36], co[36];
	fscanf(f, "%d", &N);
	M = N;
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
	
	selettore(studente, N); //fine parte lab4_1


	studente = selettore2(studente, &N);
	if (N != N) selettore(studente, N);
	for (i = 0;i < N;i++)
	{
		printf("studente %d:\nmatricola: %s\nnome: %s\ncognome: %s\ndata di nascita: %d/%d/%d\nsesso: %c\n\n",i,studente[i].matricola, studente[i].nome, studente[i].cognome, studente[i].dat.gg, studente[i].dat.mm, studente[i].dat.aaaa, studente[i].sesso);
	}
	return 0;
}

studenti* selettore2(studenti *studente, int *n)
{
	int selezione = 0,num, N = *n;
	char s[36];
	studenti*p;
	printf("Digita:\n1. per aggiungere un nuovo studente\n2. per cancellare uno studente in base alla matricola\n3. per cancellare uno studente in base al nome\n");
	scanf("%d", &selezione);
	switch (selezione)
	{
	case 1: N++;
		studente = realloc(studente, N*sizeof(studenti));
		studente[N - 1].nome = malloc(36 * sizeof(char));
		studente[N - 1].cognome = malloc(36 * sizeof(char));

		printf("inserimento nuovo studente\n");
		printf("inserisci matricola: ");
		scanf("%s", studente[N - 1].matricola);
		printf("inserisci nome: ");
		scanf("%s", studente[N - 1].nome);
		printf("inseresci cognome: ");
		scanf("%s", studente[N - 1].cognome);
		printf("inserisci data di nascita (formato gg/mm/aaaa): ");
		scanf("%d/%d/%d", &studente[N - 1].dat.gg, &studente[N - 1].dat.mm, &studente[N - 1].dat.aaaa);
		printf("inserisci sesso: ");
		scanf("%c", &studente[N - 1].sesso);
		*n = N;
		break;
	case 2:if(mark!=1) p = ricercalinearematricola(studente, N);
		   else {
			   printf("inserisci numero matricola da cercare (senza la 's'): ");
			   scanf("%d", &num);
			   change(dicomatricola(studente, N,num),&studente[N-1]);
			   N--;
			   *n = N;
			   studente = realloc(studente, N*sizeof(studenti));
		   }//funzionedicotomicamatricola
		   
		break;
	case 3: if (mark!=2) p= ricercalinearecognome(studente, N);
			else {
				printf("inserisci cognome matricola da cercare: ");
				scanf("%s", s);
				change(diconome(studente, N, s),&studente[N-1]);
				N--;
				*n = N;
				studente = realloc(studente, N*sizeof(studenti));
			}//ricercadicotmicacognome
		break;
	}
	return studente;
}
studenti* diconome(studenti*studente, int N,char s[])
{
	if ((strncmp(s, studente[N / 2].cognome, 35)) < 0)
		return diconome(studente, N/2, s);
	if ((strncmp(s, studente[N / 2].cognome, 35)) > 0)
		return diconome(&studente[N / 2], N - (N / 2), s);
	else return &studente[N / 2];

		
}

studenti* dicomatricola(studenti * studente, int N,int num)
{
	int num1;
	//printf("inserisci matricola da cercare ");
	//scanf("%d", &num);
	sscanf(studente[N / 2].matricola, "%*c%d", &num1);
	//printf("%d\n%d\n%d\n", N/2,atoi(s),atoi(studente[N/2].matricola));
	if (num < num1)
	{
		return dicomatricola(studente, N / 2,num);
	}
	if (num > num1)
	{
		return dicomatricola(&studente[N / 2], N-(N / 2),num);
	}
	else return &studente[N/2];

}

studenti* ricercalinearematricola(studenti*studente, int N)
{
	char s[8];
	int i = 0;
	printf("inserisci matricola: ");
	scanf("%s", s);
	for (i = 0;i < N;i++)
	{
		if (!strncmp(studente[i].matricola, s, 7))
		{
			if (!strncmp(studente[i + 1].matricola, s, 7))
			{
				puts("errore: piu' studenti con la stessa matricola.");
					exit(1);
			}
			return &studente[i];
		}
	}
	puts("nessuna corrispondenza.");
	exit(1);
}

studenti* ricercalinearecognome(studenti *studente, int N)
{
	char s[36];
	int flag = 0, i = 0, x = 0;
	printf("inserire cognome da cercare: ");
	scanf("%s", s);
	for (i = 0;i < N;i++)
	{
		if (!strncmp(studente[i].cognome, s, 35))
		{
			flag++;
			if (!strncmp(studente[i + 1].cognome, s, 35))
			{
				x = i;
				i++;
				while (!strncmp(studente[i].cognome, s, 35))
				{
					i++;
					flag++;
				}
				//chiamo funzione sui nomi
				return ricercalinearenome(&studente[x], flag);
			}
			return &studente[i];
		}
	}
	puts("nessuna corrispondenza");
	exit (1);
	
}
studenti* ricercalinearenome(studenti *studente, int n)
{
	char s[36];
	int i = 0;
	printf("inserire nome per specificare la ricerca: ");
	scanf("%s", s);
	for (i = 0;i < n;i++)
	if (!strncmp(studente[i].nome, s, 35))
	{
		if (!strncmp(studente[i + 1].nome, s, 35))
		{
			puts("impossibile ultimare la ricerca. ci sono casi di omonimia.");
			exit (1);
		}
		return &studente[i];
	}
	puts("nessuna corrispondenza");
	exit(1);
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

void change(studenti *x, studenti *i)
{
	studenti temp;
	temp = *x;
	*x = *i;
	*i = temp;
}