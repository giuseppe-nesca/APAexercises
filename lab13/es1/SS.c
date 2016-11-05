#include <stdio.h>
#include <stdlib.h>
#include "SS.h"



struct SS
{
	pBST bst;
	p_item *st;
};

p_item *STinit(int V)
{
	p_item *p;
	p = malloc(V*sizeof*p);
	return p;
}

pSS SSinit(int V)
{
	pSS tabs=malloc(sizeof *tabs);
	tabs->st = STinit(V);
	tabs->bst = BSTinit();
	return tabs;
}

int search(pSS tabs, char *s)
{
	int result = BSTsearch(tabs->bst,s);
	return result;
}

int STinsert(p_item *p, p_item i )
{
	static int n = 0;
	p[n] = i;
	n++;
	return n - 1;
}

void insert(pSS tabs, char *nome, int cost)
{
	p_item p = ITEMgen(nome, cost);
	int n=STinsert(tabs->st,p);
	BSTinsertl(tabs->bst, n,nome,p);
}

void SSalphaP(pSS tabs)
{
	BSTprint(tabs->bst);
}

void STprint(p_item*st,int v)
{
	ITEMprint(st[v]);
}

void SSnumP(pSS tab, int v)
{
	STprint(tab->st, v);
}
//
//int SSnetcheck(pSS tabs, int a, int b)
//{
//	return ITEMnetcheck(tabs->st[a], tabs->st[b]);
//}


char *STsearch(int i, pSS tab)
{
	return ITEMnamereturn(tab->st[i]);
}