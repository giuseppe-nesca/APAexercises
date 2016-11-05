#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Prodotti
{
	char nome[31]; //nome=strdup("stirnga");
	float prezzo;
}prod;
typedef struct Tbp
{
	prod *E;
	int nP;
}tabprod;

typedef struct Elenco
{
	int n;
	prod * link;
}liste;
typedef struct Liste
{
	liste *pr;
	int nM;
	int nL;
}elenco;
typedef struct Tbl
{
	elenco *E;
	int nM;
	int nL;
}tablist;


tabprod aqprod();
tablist aqlist();
prod*ricercaprod(char *s, tabprod t);
void stamplists(tablist t);
float calcolotot(tablist t);
float calcolosing(elenco t);
tablist nuovalista(tablist t,tabprod tabp);
tablist aggiungiprodotto(tablist t, tabprod tabp, int i);


int main()
{
	int quit = 0,selettore,i;
	float s = 0;
	tabprod tabp; tablist tabl;
	tabp = aqprod(); tabl = aqlist(tabp);

	while (quit == 0)
	{
		printf("inserisci:\n"
			"1. stampa a video dei dettagli di tutte le liste\n"
			"2. calcolo del costo per ogni lista della spesa\n"
			"3. calcolo del costo totale per tutti gli acquisti del gruppo\n"
			"4. aggiunta di una nuova lista della spesa\n"
			"5. aggiunta di un prodotto a una certa lista della spesa\n"
			"0. uscita\n");
		scanf("%d", &selettore);
		switch (selettore)
		{
		case 1: //stampa a video dei dettagli di tutte le liste
			stamplists(tabl);
			//for (a = 0;a < tabl.nL;a++) for (b = 0;b<tabl.E[a].nL;b++) printf("%d %d %s\n", a, b, tabl.E[a].pr[b].link->nome);
			puts("");
			break;
		case 2: //calcolo del costo per ogni lista della spesa
			for (i = 0;i < tabl.nL;i++) printf("lista %d  spesa: %.2f\n",i,calcolosing(tabl.E[i]));
			break;
		case 3: //calcolo del costo totale per tutti gli acquisti del gruppo
			s = calcolotot(tabl);
			printf("%.2f\n", s);
			break;
		case 4: //aggiunta di una nuova lista della spesa
			tabl = nuovalista(tabl,tabp);
			break;
		case 5: //aggiunta di un prodotto a una certa lista della spesa
			printf("inserisci numero lista da modificare (numero tra 0 e %d)", tabl.nL - 1);
			scanf("%d", &i);
			aggiungiprodotto(tabl, tabp,i);
			break;
		case 0: quit++;
			break;
		default: puts("comando inserito non valido.");

		}
	}
	
	return 0;
}

tabprod aqprod()
{
	tabprod t;
	FILE *f;
	int i;
	if ((f = fopen("prodotti.txt", "r")) == NULL)
	{
		puts("errore file in lettura.");
		exit(1);
	}
	fscanf(f, "%d", &t.nP);
	t.E = malloc(t.nP*sizeof(prod));
	for (i = 0;i < t.nP;i++) fscanf(f, "%s %f", t.E[i].nome, &t.E[i].prezzo);

	//for (i = 0;i < t.nP;i++) printf("%d %s\n", i, t.E[i].nome);
	//puts("");

	return t;

}

tablist aqlist(tabprod tabp)
{
	int a,b;
	char s[31];
	tablist t;
	FILE *f;
	if ((f = fopen("liste.txt", "r")) == NULL)
	{
		puts("errore file in lettura.");
		exit(1);
	}
	fscanf(f, "%d", &t.nM);
	t.nL = t.nM;
	t.E = malloc(t.nM*sizeof(elenco));
	for (a = 0;a < t.nL;a++)
	{
		fscanf(f, "%d", &t.E[a].nM); t.E[a].nL = t.E[a].nM;
		t.E[a].pr = malloc(t.E[a].nM*sizeof(liste));
		for (b = 0;b < t.E[a].nL;b++)
		{
			fscanf(f, "%s %d", s, &t.E[a].pr[b].n);
			t.E[a].pr[b].link = ricercaprod(s, tabp); //occhio al caso ritorno NULL
		}
	}

	//for (a = 0;a < t.nL;a++) for (b = 0;b<t.E[a].nL;b++) printf("%d %d %s\n", a, b, t.E[a].pr[b].link->nome);

	return t;
}

prod*ricercaprod(char *s, tabprod t)
{
	int i = 0;
	while ((strncmp(s, t.E[i].nome, strlen(s))) != 0) 
	if (i == t.nP)
	{
		printf("'%s' non trovato.\n", s);
		return NULL;
	}
	else i++;
	return &t.E[i];
}

void stamplists(tablist t)
{
	int a, b;
	for (a = 0;a < t.nL;a++) 
		for (b = 0;b<t.E[a].nL;b++) 
			printf("lista %d prodotto %d  n.%d %s\n", a, b, t.E[a].pr[b].n ,t.E[a].pr[b].link->nome);

}

float calcolotot(tablist t)
{ 
	int i;
	float s=0;
	for (i = 0;i < t.nL;i++) s = s + calcolosing(t.E[i]);
	return s;
}

float calcolosing(elenco t)
{
	int i;
	float s = 0;
	for (i = 0;i < t.nL;i++) s = s + t.pr[i].link->prezzo*t.pr[i].n;
	return s;
}

tablist nuovalista(tablist t, tabprod tabp)
{
	int n;
	if (t.nL == t.nM)
	{
		t.nM = t.nM * 2;
		t.E = realloc(t.E, t.nM*sizeof(elenco));
	}
	n = t.nL; t.nL++;
	t.E[n].nM = 10; t.E[n].nL = 0;
	t.E[n].pr = malloc(t.E[n].nM*sizeof(liste));
	
	return t;
}

tablist aggiungiprodotto(tablist t, tabprod tabp,int i)
{
	char s[31];
	int n=t.E[i].nL;
	if (t.E[i].nL == t.E[i].nM)
	{
		t.E[i].nM = t.E[i].nM * 2;
		t.E[i].pr = realloc(t.E[i].pr, t.E[i].nM*sizeof(liste));
	}

	puts("inserisci numero e nome prodotto da inserire: ");
	scanf("%d %s", &t.E[i].pr[n].n, s);
	
	t.E[i].pr[n].link = ricercaprod(s, tabp);
	t.E[i].nL++;

	return t;
}