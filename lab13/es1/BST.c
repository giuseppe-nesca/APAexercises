#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

pBST BSTinit()
{
	pBST bst = malloc(sizeof*bst);
	bst->root = NULL;
	return bst;
}

int BSTsearch(pBST bst,char*s)
{
	int select;
	nlink p = bst->root;
	while (p != NULL)
	{
		select = ITEMconf(s, p->item);
		if (select > 0) p = p->r;
		if (select < 0) p = p->l;
		if (select == 0) 
			return p->i;
	}
	puts("error BST: not found");
	system("pause");
	exit(1);
}

nlink NODEnew(p_item item, int n)
{
	nlink p = malloc(sizeof*p);
	p->i = n;
	p->item = item;
	p->l = p->r = NULL;
	return p;
}

void BSTinsertl(pBST bst, int n, char*s,p_item item)
{
	nlink p = bst->root;
	if (p == NULL) {
		bst->root = NODEnew(item, n); return;
	}
	while (p != NULL)
	{
		int select = ITEMconf(s, p->item);
		if (select > 0)
		{
			if (p->r == NULL) { p->r = NODEnew(item, n); return; }
			p = p->r;
		}
		if (select < 0)
		{
			if (p->l == NULL) { p->l = NODEnew(item, n); return; }
			p = p->l;
		}
		if (select = 0) {
			puts("item già presente"); return;
		}
	}
	//p = NODEnew(item, n);
}

void inorderP(nlink p)
{
	if (p->l != NULL) inorderP(p->l);
	ITEMprint(p->item);
	if (p->r != NULL) inorderP(p->r);
}

void BSTprint(pBST bst)
{
	inorderP(bst->root);
}