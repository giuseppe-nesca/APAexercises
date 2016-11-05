#include "lab4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N;
studenti **alfa, **mat, **dat;
extern studenti*acquisizione();

void inizializza(studenti * studente);
void reinizializza(studenti * studente);
void stampavideo(studenti **studente);
studenti *diconome(studenti**studente, char s[], int n);
studenti* dicomatricola(studenti ** studente, int num, int n);
studenti * selettore(studenti * studente);
//void changepoint(int flag, int i);
void sortalfa();
int sortalfa2(char *a, char *i, int flag, int l);
void sortdata();
void sortmatricola();





int main()
{
	studenti *studente = acquisizione("in.txt");
	inizializza(studente);

	studente = selettore(studente);


	
	return 0;
}

void inizializza(studenti * studente )
{
	int i;
	studenti **a= malloc(N*sizeof(studenti*));
	studenti **m= malloc(N*sizeof(studenti*));
	studenti **d= malloc(N*sizeof(studenti*));
	for (i = 0;i < N;i++)
	{
		a[i]=m[i]=d[i]=&studente[i];
	}
	
	alfa = a;
	sortalfa();
	
	mat = m;
	sortmatricola();
	
	dat = d;
	sortdata();
}

void reinizializza(studenti * studente)
{
	int i;
	studenti **a = realloc(alfa, N*sizeof(studenti*));
	studenti **m = realloc(mat, N*sizeof(studenti*));
	studenti **d = realloc(dat, N*sizeof(studenti*));
	for (i = 0;i < N;i++)
	{
		a[i] = m[i] = d[i] = &studente[i];
	}

	alfa = a;
	sortalfa();

	mat = m;
	sortmatricola();

	dat = d;
	sortdata();
}

studenti * selettore(studenti * studente)
{
	studenti *p;
	int selezione,num;
	char s[36];
	printf("\nDigita:\n1. per aggiungere un nuovo studente\n2. per cancellare uno studente in base alla matricola\n3. cancellare uno studente in base al nome\n");
	printf("4. cerca per nome e stampa studente\n5. cerca per matricola e stampa studente\n6. stampa tutto in ordine alfabetico\n7. stampa tutto in ordine per matricola\n");
	printf("0. esci dal programma\n");
	scanf("%d", &selezione);
	switch (selezione)
	{
	case 1: N++; //aggiungi studente
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
		studente[N - 1].sesso = getchar();
		studente[N - 1].flag = 1;
		reinizializza(studente);
		break;
	
	case 2: //rimuovi per matricola
		printf("inserisci matricola da cercare (senza 's') "); scanf("%d", &num);
		p=dicomatricola(mat, num, N);
		p->flag = 0;
		break;

	case 3: //rimuovi studente per nome	
		printf("inserisci cognome da cercare: "); 
		scanf("%s", s);
		p=diconome(alfa, s, N);
		p->flag = 0;
		break;
	case 4: //stampa nome
		printf("inserisci cognome da cercare: "); scanf("%s", s);
		p = diconome(alfa, s, N);
		if (p->flag == 0) printf("studente cancellato.");
		else 	printf("\n\nmatricola: %s\nnome: %s\ncognome: %s\ndata di nascita: %d/%d/%d\nsesso: %c\n\n", p->matricola, p->nome, p->cognome, p->dat.gg, p->dat.mm, p->dat.aaaa, p->sesso);
		break;
	case 5: //stampa matricola
		printf("inserisci matricola da cercare (senza 's') "); scanf("%d", &num);
		p = dicomatricola(mat, num, N);
		if (p->flag == 0) printf("studente cancellato.");
		else 	printf("\n\nmatricola: %s\nnome: %s\ncognome: %s\ndata di nascita: %d/%d/%d\nsesso: %c\n\n", p->matricola, p->nome, p->cognome, p->dat.gg, p->dat.mm, p->dat.aaaa, p->sesso);
		break;
	case 6: //stampa tutto in orinde alfabetico
		stampavideo(alfa);
		break;
	case 7: //stampa tutto in ordine per matricola
		stampavideo(mat);
		break;
	case 0:  exit (0);
		break;
	default: puts("comando non vaildo.");
	}

	return selettore (studente);
}


studenti* dicomatricola(studenti ** studente, int num,int n)
{
	int num1;
	//printf("inserisci matricola da cercare ");
	//scanf("%d", &num);
	sscanf(studente[n / 2]->matricola, "%*c%d", &num1);
	//printf("%d\n%d\n%d\n", N/2,atoi(s),atoi(studente[N/2].matricola));
	if (num < num1)
	{
		return dicomatricola(studente, num, n / 2);
	}
	if (num > num1)
	{
		return dicomatricola(&studente[n / 2], num, n - (n / 2));
	}
	else return studente[n / 2];

}


studenti *diconome(studenti**studente, char s[],int n)
{
	if ((strncmp(s, (*studente[n / 2]).cognome, 35)) < 0)
		return diconome(studente, s,n / 2);
	if ((strncmp(s, (*studente[n / 2]).cognome, 35)) > 0)
		return diconome(&studente[n / 2], s,n - (n / 2));
	else return studente[n / 2];
}

void stampavideo(studenti **studente)
{
	int i, c = 0;
	for (i = 0;i < N;i++)
	{
		if (studente[i]->flag == 1) {
			printf("studente %d:\nmatricola: %s\nnome: %s\ncognome: %s\ndata di nascita: %d/%d/%d\nsesso: %c\n\n", c, studente[i]->matricola, studente[i]->nome, studente[i]->cognome, studente[i]->dat.gg, studente[i]->dat.mm, studente[i]->dat.aaaa, studente[i]->sesso);
			c++;
		}
	}
}

void sortalfa()
{
	int l, a, i, flag = -1;
	studenti *temp;

	for (i = 0;i < N;i++)
	{
		for (a = i + 1;a < N;a++)
		{
			if (alfa[a]->cognome[0] < alfa[i]->cognome[0])
				flag = a;
			if (alfa[a]->cognome[0] ==alfa[i]->cognome[0])
			{
				if (strlen(alfa[a]->cognome) <= strlen(alfa[i]->cognome))
					l = strlen(alfa[a]->cognome);
				else l = strlen(alfa[i]->cognome);
				if (strncmp(alfa[a]->cognome,alfa[i]->cognome, l))
				{
					flag = sortalfa2(alfa[a]->nome,alfa[i]->nome, a, l);
				}
				else flag = sortalfa2(alfa[a]->cognome,alfa[i]->cognome, a, l);
			}
		}
		if (flag != -1)
		{
			temp = alfa[flag];
			alfa[flag] = alfa[i];
			alfa[i] = temp;
			//changepoint(&(*studente)[flag], &(*studente)[i]);
			flag = -1;
		}
	}
}

int sortalfa2(char *a, char *i, int flag, int l)
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

void sortdata()
{
	studenti *temp;
	int i, a, flag = -1;

	for (i = 0;i < N; i++)
	{
		for (a = i + 1;a < N;a++)
		{
			if (dat[a]->dat.aaaa < dat[i]->dat.aaaa)
				flag = a;
			if (dat[a]->dat.aaaa == dat[i]->dat.aaaa)
			{
				if (dat[a]->dat.mm < dat[i]->dat.mm)
					flag = a;
				if (dat[a]->dat.mm == dat[i]->dat.mm)
				{
					if (dat[a]->dat.gg < dat[i]->dat.gg)
						flag = a;
				}
			}
			if (flag != -1)
			{
				temp = dat[flag];
				dat[flag] = dat[i];
				dat[i] = temp;

				flag = -1;
			}
		}
	}
}

void sortmatricola()
{
	studenti *temp;
	int flag = -1;
	int i, a;
	int ma, mi;
	for (i = 0;i < N;i++)
	{
		sscanf(mat[i]->matricola, "%*c%d", &mi);
		for (a = i + 1;a < N;a++)
		{
			sscanf(mat[a]->matricola, "%*c%d", &ma);
			if (ma < mi)
			{
				flag = a;
			}

		}
		if (flag != -1)
		{
			temp = mat[flag];
			mat[flag] = mat[i];
			mat[i] = temp;
			
			flag = -1;
		}
	}
}






