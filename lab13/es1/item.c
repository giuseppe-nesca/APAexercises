#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct ITEM
{
	char *nome;
	int cost;
};

p_item ITEMgen(char*e, int c) //used
{
	p_item p = malloc(sizeof*p);
	p->nome = strdup(e);
	p->cost = c;
	return p;
}

int ITEMconf(char *s1, p_item it)
{
	return strcmp(s1, it->nome);
}

void ITEMprint(p_item it)
{
	printf("%s\n", it->nome);
}

//int ITEMnetcheck(p_item a, p_item b)
//{
//	return strcmp(a->rete, b->rete);
//}

char *ITEMnamereturn(p_item p)
{
	return p->nome;
}