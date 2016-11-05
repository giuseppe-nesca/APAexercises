#include <stdio.h>
#include <stdlib.h>
#include "item.h"

item insert_i()
{
	item t;
	printf("insert: 'priority' type' 'code'\n");
	scanf("%d %s %s", &t.piority, t.type, t.code);
	return t;
}

void print_i(item*l)
{
	printf("priority: %d  type: %s  client code: %s\n",l->piority,l->type,l->code);
	return;
}

FILE* save_i(FILE*f, item *l)
{
	fprintf(f, "%d %s %s", l->piority, l->type, l->code);
	return f;
}

FILE* freader_i(FILE*f, item*l)
{
	fscanf(f,"%d %s %s",&l->piority,l->type,l->code);
	return f;
}

int prio(item*l)
{
	return l->piority;
}