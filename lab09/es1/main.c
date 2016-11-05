#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main(int argc,char**argv)
{
	int select = 1,N=atoi(argv[1]),x;
	link* start = NULL;

	start = malloc(N*sizeof(link));
	for (x = 0;x < N;x++)
		start[x] = NULL;


	//pt2
	while (select != 0)
	{
		printf("inserisci\n"
			"1. per stampare il numero di dati e i relativi dettagli\n"
			"2. per inserire un nuovo elemento in coda\n"
			"3. per estraarre un elemento dalla coda\n"
			"4. per salvare su file\n"
			"5. per caricare da file\n"
			"0. exit\n");
		scanf("%d", &select);

		switch (select)
		{
		case 1: //stampare n dati e dettagli
			printf("vuoi stampare:\n1. dettagli di una determinata coda\n2. dettagli di tutte le code\n"); scanf("%d", &select);
			switch (select) //switch interna
			{
			case 1:
				printf("inserisci numero lista di cui si vuole stampare i dettagli (x<%d): ", N); scanf("%d", &x);
				print_e(start[x]);
				break;
			case 2:
				for (x = 0;x < N;x++)
				{
					printf("lista[%d]\n", x);
					print_e(start[x]);
					printf("\n");
				}
				break;
			default: printf("inserimento non valido\n");
				break;
			} //fine switch interna
			select = 1;
			break;
		case 2: //inserimento nuov elemento
			
			printf("inserisci lista:\n1. selezione automatica\n2. selezione manuale"); scanf("%d", &select);
			switch (select)
			{
			case 1:
				x = shorter(start, N);
				start[x] = insert_e(start[x]);
				break;
			case 2:
				printf("inserisci numero lista in cui si vuole inserire un nuovo elemento (x<%d): ", N); scanf("%d", &x);
				start[x] = insert_e(start[x]);
				break;
			default: puts("inserimento non valido");
				break;
			}
			select = 2;
			break;
		case 3: //estrazione dalla coda
				printf("inserisci numero lista da cui si vuol estrarre un elemento (x<%d): ", N); scanf("%d", &x);
				if(start[x]!=NULL) start[x] = extract_e(start[x]);
				else printf("start[%d]=NULL\n", x);
			break;
		case 4: // salva 
			printf("inserisci numero lista da salvare (x<%d): ", N); scanf("%d", &x);
			save_e(start[x]);
			break;
		case 5: // acquisisci da file
			printf("inserisci numero lista su cui importare (x<%d): ", N); scanf("%d", &x);
			start[x] = freader_e(start[x]);
			break;
		case 0: exit(1);
			break;
		default: printf("inserimento non valido\n");
			select = 1;
			break;
		}
	}
	return 0;
}