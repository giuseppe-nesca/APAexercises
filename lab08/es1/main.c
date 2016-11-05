#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main()
{
	int select=1;
	node *start=NULL;
	
	while (select != 0)
	{
		printf("inserisci\n"
			"1. per stampare il numero di dati in coda e i relativi dettagli\n"
			"2. per inserire un nuovo elemento in coda\n"
			"3. per estraarre un elemento dalla coda\n"
			"4. per salvare su file\n"
			"5. per caricare da file\n"
			"0. exit\n");
			scanf("%d", &select);

			switch (select)
			{
			case 1: //stampare n dati e dettagli
				print_e(start);
				break;
			case 2: //inserimento nuov elemento
				start = insert_e(start); 
				break;
			case 3: //estrazione dalla coda
				start=extract_e(start); //err!!!! serve il doppio pointer // !nelle successive al primo stampa il successivo di quello giusto
				break;
			case 4: // salva 
				save_e(start);
				break;
			case 5: // acquisisci da file
				start=freader_e(start);
				break;
			case 0: exit(1);
			}
		
	}
	
	return 0;
}