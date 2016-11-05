#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

typedef struct ITEM
{
	float prezzo;
	char *prodotto;
}item_def;

Item ITEMnew()
{
	char s[MAX];
	Item t = malloc(sizeof(item_def));
	printf("inerisci nome e prezzo: ");
	scanf("%s %f", s, &t->prezzo); t->prodotto = strdup(s);
	return t;
}

void stampa_Item(Item t)
{
	printf("\n"
		"\nProdotto : %s"
		"\nPrezzo : %.2f", t->prodotto, t->prezzo);
	return;
}

void ITEMstampF(Item t, FILE *f)
{
	fprintf(f, "%s %f", t->prodotto, t->prezzo);
	return;
}

Item inserimento_item(float p, char *prod)
{
	Item t=malloc(sizeof(item_def));
	t->prezzo = p;
	//strcpy(t->prodotto, prod);
	t->prodotto = strdup(prod);
	return t;
}
Item ITEMsetvoid()
{
	Item t=malloc(sizeof(item_def));
	t->prezzo = -1;
	//strcpy(t->prodotto, "\0");
	t->prodotto = NULL;
	return t;
}
int ITEMless(Item x, Item y)
{
	if (x->prezzo>y->prezzo)
		return 0;
	else
		return 1;
}

float ITEMprice(Item item)
{
	return item->prezzo;
}
char *ITEMproduct(Item item)
{
	return item->prodotto;
}

void ITEMfree(Item t)
{
	free(t);
	return;
}