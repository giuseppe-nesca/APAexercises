#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

int main()
{
	int select = 1;
	BST bst=NULL;

	while (select!=0)
	{
		printf("digita:\n"
			"1. creazione di un nuovo BST (vuoto)\n"
			"2. indrserimento in foglia di un nuovo elemento nel BST\n"
			"3. inserimento in radice di un nuovo elemento nel BST\n"
			"4. recerca di un elemento nel BST\n"
			"5. stampa dell'elemento a prezzo massimo e minimo\n"
			"6. stampa a video tutti gli elementi presenti nel BST\n"
			"7. stampa numero totale di nodi dell'albero\n"
			"8. salvatagio del BST su file\n"
			"9. caricamento di un nuovo BST da file mediante inserimenti in foglia\n"
			"0. exit\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1: //creazione di un nuovo BST (vuoto)
			bst = BSTinit();
			break;
		case 2: //inserimento in foglia di un nuovo elemento nel BST
			BSTinsert_leafR(bst, ITEMnew());
			break;
		case 3: //inserimento in radice di un nuovo elemento nel BST
			BSTinsert_root(bst, ITEMnew());
			break;
		case 4: //ricerca di un elemento (specificato per nome dall utente) nel BST
			BST_find(bst);
			break;
		case 5: //stampa dell 'elemento a prezzo minimo o massimo presenti nel BST
			printf("il massimo e':\n"); stampa_Item(BSTmax(bst));
			printf("il minimo e':\n"); stampa_Item(BSTmin(bst));
			break;
		case 6: //stampa a video tutti gli elementi presenti nel BST, alternativamente secondo pre/post/in order (a scelta dell'utente)
			while (select != 1 && select != 2 && select != 3)
			{
				printf("digita:\n"
					"1. stampa in preorder\n"
					"2. stampa in order\n"
					"3. stampa in postorder\n");
				scanf("%d", &select);
				switch (select)
				{
				case 1: //stampa in preorder R,S,D
					BSTshow(bst, select);
					break;
				case 2: //stampa in order S,R,D
					BSTshow(bst, select);
					break;
				case 3: // stampa in post order D,R,S //SDR!
					BSTshow(bst, select);
					break;
				}
			}
			break;
		case 7: //calcolo del numero totale di nodi dell'albero
			printf("Numero di nodi dell'albero: %d", BSTcount(bst));
			break;
		case 8: //salvatagio del BST su file (orinde dei nodi random)
			BSTexport(bst);
			break;
		case 9: //caricamento di un nuovo BST da file mediante una sequenza di inserimenti i nfoglia.
				//ogni riga del file contiene informazioni relative al nodo da inserire nella forma "prezzo nome_prod".
			BSTimport(bst);
			break;
		case 0:
			BSTfree(bst);
			exit(0);
			break;
		}

	}
	return 0;
}