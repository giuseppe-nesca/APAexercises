#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

typedef struct BSTnode* link;

typedef struct BSTnode
{
	Item item;
	link p;
	link l;
	link r;
	int N;
}BSTnode_def;

struct binarysearchtree
{
	link head;
	int N;
	link z;
};

void BST_show_IN(link root);
void BST_show_PRE(link root);
void BST_show_POST(link root);
void BST_find_key(link root, char *key);
void salva_su_file(link root, FILE *f);


link NEW(Item item, link p, link l, link r, int N)
{
	link x = malloc(sizeof *x);
	x->item = item;
	x->p = p;
	x->l = l;
	x->r = r;
	x->N = N;
	return x;
}
BST BSTinit()
{
	Item a = ITEMsetvoid();
	BST bst = malloc(sizeof *bst);
	bst->N = 0;
	bst->head = (bst->z = NEW(a, NULL, NULL, NULL, 0));
	return bst;
}
int BSTcount(BST bst)
{
	return bst->N;
}
int BSTempty(BST bst)
{
	if (BSTcount(bst) == 0) return 1;
	else return 0;
}
link insertR(link h, Item x, link z)
{
	if (h == z)
		return NEW(x, z, z, z, 1);
	if (ITEMless(x, h->item))
	{
		h->l = insertR(h->l, x, z);
		h->l->p = h;
	}
	else
	{
		h->r = insertR(h->r, x, z);
		h->r->p = h;
	}
	(h->N)++;
	return h;
}
void BSTinsert_leafR(BST bst, Item x)
{
	bst->head = insertR(bst->head, x, bst->z);
	bst->N++;
}

link rotL(link h)
{
	link x = h->r;
	h->r = x->l;
	x->l->p = h;
	x->l = h;
	x->p = h->p;
	h->p = x;
	x->N = h->N;
	h->N = h->l->N + h->r->N + 1;
	return x;
}
link rotR(link h)
{
	link x = h->l;
	h->l = x->r;
	x->r->p = h;
	x->r = h;
	x->p = h->p;
	h->p = x;
	x->N = h->N;
	h->N = h->r->N + h->l->N + 1;
	return x;
}

link insertT(link h, Item x, link z)
{
	if (h == z) return NEW(x, z, z, z, 1);
	if (ITEMless(x, h->item))
	{
		h->l = insertT(h->l, x, z);
		h = rotR(h);
		h->N++;
	}
	else
	{
		h->r = insertT(h->r, x, z);
		h = rotL(h);
		h->N++;
	}
	return h;
}
void BSTinsert_root(BST bst, Item x)
{
	bst->head = insertT(bst->head, x, bst->z);
	bst->N++;
}

Item minR(link h, link z)
{
	if (h == z) return ITEMsetvoid();
	if (h->l == z) return (h->item);
	return minR(h->l, z);
}
Item BSTmin(BST bst)
{
	return minR(bst->head, bst->z);
}
Item maxR(link h, link z)
{
	if (h == z) return ITEMsetvoid();
	if (h->r == z) return (h->item);
	return maxR(h->r, z);
}
Item BSTmax(BST bst)
{
	return maxR(bst->head, bst->z);
}

void BSTshow(BST bst, int tipo_ordine)
{
	link root = bst->head;
	if (tipo_ordine <= 0 || tipo_ordine>3)
	{
		printf("\nValore non consentito!");
		return;
	}
	switch (tipo_ordine)
	{
	case 1:
		BST_show_PRE(root);
		break;
	case 2:
		BST_show_IN(root);
		break;
	case 3:
		BST_show_POST(root);
		break;
	}
	return;
}
void BST_show_IN(link root)
{
	if (ITEMprice(root->item) == -1)
		return;
	BST_show_IN(root->l);
	stampa_Item(root->item);
	BST_show_IN(root->r);
	return;
}
void BST_show_PRE(link root)
{
	if (ITEMprice(root->item) == -1 )
		return;
	stampa_Item(root->item);
	BST_show_PRE(root->l);
	BST_show_PRE(root->r);
	return;
}
void BST_show_POST(link root) //
{
	if (ITEMprice(root->item) == -1)
		return;
	//BST_show_POST(root->r);
	//stampa_Item(root->item);
	BST_show_POST(root->l);
	BST_show_POST(root->r);
	stampa_Item(root->item);

	return;
}

void BST_find(BST bst)
{
	link root = bst->head;
	char key[MAX];
	printf("inserisci chiave da cercare: "); scanf("%s", key);
	BST_find_key(root, key);
	return;
}
void BST_find_key(link root, char *key)
{
	if (ITEMprice(root->item) == -1)
		return;
	BST_find_key(root->l, key);
	if (strcmp(ITEMproduct(root->item), key) == 0)
	{
		printf("\nChiave trovata!");
		stampa_Item(root->item);
		return;//
	}
	BST_find_key(root->r, key);
	return;
}


void BSTexportR(link l, FILE*f)
{
	if (ITEMprice(l->item) == -1) return;
	BSTexportR(l->l,f);
	ITEMstampF(l->item,f);
	BSTexportR(l->r, f);
}

void BSTexport(BST bst)
{
	FILE*f;
	char s[MAX];
	printf("inserisci nome file: "); scanf("%s", s);
	f = fopen(s, "w");
	BSTexportR(bst->head, f);
	fclose(f);
}


void BSTimport(BST bst)
{
	FILE*f;
	int N;
	int i;
	char s[MAX];
	float p;
	Item t;
	printf("inserisci nome file: "); scanf("%s", s);
	f = fopen(s, "r"); if (f == NULL) { puts("errore file in lettura"); system("pause"); exit(1); }
	fscanf(f,"%d", &N);
	for (i = 0;i < N;i++)
	{
		fscanf(f, "%s %f", s, &p);
		t = inserimento_item(p, s);
		BSTinsert_leafR(bst, t);
	}
	fclose(f);
	//BSTimportR(bst->head, f);
}

void NODEfree(link l)
{
	if (ITEMprice(l->item) == -1)
	{
		//ITEMfree(l->item);
		return;
	}
	NODEfree(l->l);
	ITEMfree(l->item);
	NODEfree(l->r);
	free(l);
	return;
}

void BSTfree(BST bst)
{
	NODEfree(bst->head);
	free(bst);
}
