#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main(int argc, char **argv)
{
	int select=-1;
	FILE*f;
	l_tabp tabp;
	l_tabls tabl;

	//aquisizione prodotti
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		puts("errore lettura file liste"); 
		system("pause"); 
		exit(1);
	}
	tabp = aqprod(f);
	fclose(f);

	//acquisizione liste
	tabl = aqlist(argv[2], tabp);

	//azioni
	while (select != 0)
	{
		printf("inserisci: \n"
			"1. stampa a video dettagli\n"
			"2. calcola costo di ogni lista della spesa\n"
			"3. calcola costo totale per tutti gli acquisti del gruppo\n"
			"4. aggiungi nuova lista della spesa\n"
			"5. aggiunta di un prodotto a una lista\n"
			"0. quit\n");
		scanf("%d", &select);

		switch (select)
		{
		case 1: //stampa a video dettagli
			printall(tabl, tabp);
			printf("\n\n");
			break;
		case 2: //calcola ocsto di ogni lista della spesa
			calcost(tabl, tabp, -1);
			break;
		case 3: //calocla costo tottale di tutti
			calcost(tabl, tabp, 0);
			break;
		case 4: //aggiungi nuova lista
			newslist(tabl);
			break;
		case 5: //aggiungi un prodotto a una lista
			findlist(tabl, tabp);
			break;
		case 0: //quit
			break;
		default: puts("inserimento non valido.");
			break;
		}
	}
	
	return 0;
}