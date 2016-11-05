#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct NODE *link;

struct NODE
{
	pitem item;
	link next;
};

struct LIST
{
	link root;
	int N;
};

link NODEnew(pitem i , link next)
{
	link x = malloc(sizeof*x);
	x->item = i;
	x->next = next;
	return x;
}

void LISTinsert(pitem i, plist l)
{
	link t;
	//caso particolare root
	if (l->root == NULL)
	{
		l->root = NODEnew(i, NULL);
		return;
	}

	for (t = l->root;t->next != NULL;t=t->next)
	{
		if (ITEMconf(i, t->next->item) == 1)
		{
			t->next = NODEnew(i, t->next);
			return;
		}
	}
	t->next = NODEnew(i, NULL);
	return;
}

plist LISTinit()
{
	plist x = malloc(sizeof*x);
	x->root = NULL;
	return x;
}

int check(link l, int *tot, int f, int m)
{
	if (ITEMcheck(l->item, f, tot, m) == 1)
	{
		return 1;
	}
	return 0;
}

int find(plist l, int *tot, int f, int m)
{
	link t;
	link tmp=l->root;

	if (check(l->root, tot, f,m) == 1)
	{
		l->root = l->root->next;
		free(tmp);
		return 1;
	}
	for (t = l->root->next;t != NULL;t = t->next)
	{
		if (check(t, tot,f,m) == 1)
		{
			//ITEMstamp(t->item);
			tmp->next = t->next;
			free(t);
			return 1;
		}

		tmp = t;
	}
	return 0;
}

