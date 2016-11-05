#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct ITEM
{
	char*elaboratore;
	char*rete;
};

p_item ITEMgen(char*e, char*r)
{
	p_item p = malloc(sizeof*p);
	p->elaboratore = strdup(e);
	p->rete = strdup(r);
	return p;
}

int ITEMconf(char *s1, p_item it)
{
	return strcmp(s1, it->elaboratore);
}

void ITEMprint(p_item it)
{
	printf("%s\n", it->elaboratore);
}

int ITEMnetcheck(p_item a, p_item b)
{
	return strcmp(a->rete, b->rete);
}