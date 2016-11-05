#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[])
{
	int select = 0;
	Graph G;
	G = GRAPHread();


	
	while (select !=-1)
	{
		printf("digita:"
			"\n1. stampare il numero totale di vertici ed elencarli esplicitamente per nome "
			"\n2. stampare il numero di archi incidenti su un nodo e l'elenco di vertici ad esso connessi "
			"\n3. generare la matrice di adiacenza, SENZA leggere nuovamente il file, a partire dalle liste di adiacenza"
			"\n4. determinare l’ammontare complessivo dei flussi intra-rete ed inter-rete globali"
			// Si noti che per ottenere questi due valori è sufficiente percorrere iterativamente tutti gli archi del grafo.
			"\n0. exit\n");
		scanf("%d", &select);

	switch (select)
	{
	case 1: printf("%d\n", GRAPH_Vnum(G));
		GRAPHalphaP(G);
		break;
	case 2: GRAPHshowlink(G);
		break;
	case 3: GRAPHmatgen(G);
		break;
	case 4: GRAPHwt(G);
		break;
	case 0: select = -1;
		break;
	}
	}

	
	return 0;
}