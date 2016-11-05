#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct SLIST *linkls;
typedef struct PLIST * linkpr;

typedef struct PLIST
{
	int pcode;
	int q;
	linkpr next;

}plist;

typedef struct SLIST
{
	char * name;
	linkls next;
	int n;
	linkpr head, tail;
}slist;

typedef struct TABL
{
	linkls head, tail;
	int nl;
}tabls;

void addlistpr(FILE*f, int remained, linkpr *head, linkpr *tail, linkpr tmp, l_tabp tabprod);
void printlist(linkls l, l_tabp p);
void printnode(linkpr l, l_tabp p);
void calcost2(linkls l, l_tabp tabp, float *flag);
void calcost3(linkpr l, l_tabp tabp, float *flag);
linkpr newnode(linkpr p, l_tabp tp);

l_tabls aqlist(char*filename, l_tabp tabprod )
{
	FILE*f = fopen(filename, "r"); if (f == NULL) { puts("errore lettura file liste."); exit(1); }
	l_tabls t=malloc(sizeof(tabls));
	int i = 0;
	char s[30];
//	int DBG;
	linkls tmp=NULL,lst = NULL; 

	fscanf(f, "%d", &t->nl);
	for (i = 0;i < t->nl;i++)
	{
		lst = malloc(sizeof(slist));
		if (i == 0) t->head = lst;
		else tmp->next = lst;
		fscanf(f, "%d %s", &lst->n, s); lst->name = strdup(s);
		lst->next = NULL;
		addlistpr(f,lst->n,&lst->head,&lst->tail,NULL,tabprod);
		tmp = lst;
	}
	t->tail = tmp;
	return t;
}

void addlistpr(FILE*f, int remained, linkpr *head, linkpr *tail, linkpr tmp, l_tabp tabprod)
{
	if (remained == 0) { 
		tmp->next = NULL; *tail = tmp;  return; }
	linkpr l=malloc(sizeof(plist));
	char s[30];
	fscanf(f, "%s %d", s, &l->q);
	l->pcode = searchnpr(s,tabprod);
	if (tmp == NULL)
	{
		*head = l;
	}
	else
	{
		tmp->next = l;
	}
	addlistpr(f, remained - 1, head,tail, l, tabprod);
	return;
}

void printall(tabls *tabl, l_tabp  tabp )
{
	linkls lk = tabl->head;
	while (lk != NULL)
	{
		printlist(lk,tabp);
		lk = lk->next;
	}
}

void printlist(linkls l,l_tabp p)
{
	printf("%s:\n", l->name);
	if (l->head != NULL)
	{
		printnode(l->head, p);
		printf("\n");
	}
}

void printnode(linkpr l,l_tabp p)
{
	printf("%d %s\n", l->q, searchpnpr(l->pcode, p));
	if (l->next == NULL) return;
	printnode(l->next, p);
}

void calcost(tabls *tabl, l_tabp tabp,float flag)
{
	linkls lk = tabl->head;
	float summ = 0;
	//while (lk != NULL)
	{
		calcost2(lk,tabp,&flag);
	}
	if (flag >= 0) printf("la spesa complessiva e' di %.2f euro\n", flag);
}

void calcost2(linkls l, l_tabp tabp, float *flag)
{
	if (*flag<0)printf("%s: ", l->name);
	calcost3(l->head,tabp,flag);
	if (l->next == NULL) return;
	else calcost2(l->next,tabp,flag);

}

void calcost3(linkpr l,l_tabp tabp,float *flag)
{
	float sum = 0;
	while (l != NULL)
	{
		sum += l->q*price(l->pcode, tabp);
		l = l->next;
	}
	if (*flag < 0) printf("%.2f\n", sum);
	else *flag += sum;
}

void newslist(l_tabls t)
{
	linkls p;
	p = t->tail;
	char s[30];
	p->next = malloc(sizeof(slist));
	p->next->next = NULL;
	p->next->head = NULL;
	p->next->tail = NULL;
	p->next->n = 0;
	printf("inserisci nome nuova lista: ");
	scanf("%s", s);
	p->next->name = strdup(s);
	t->tail= p->next;
}

void findlist(tabls *tl, l_tabp tp)
{
	linkls l = tl->head;
	char s[30];
	printf("inserisci nome lista su cui inserire: ");
	scanf("%s", s);
	while (l != NULL)
	{
		if (strcmp(s, l->name) == 0)
		{
			if (l->tail != NULL) {
				l->tail->next = newnode(l->tail, tp);
				l->tail = l->tail->next;
			}
			else {
				l->tail = newnode(l->tail, tp);
			}
			if (l->head == NULL) l->head = l->tail;
			return;
		}
		l = l->next;
	}
	puts("nessuna corrispondenza trovata");
	return;
}


linkpr newnode(linkpr p,l_tabp tp)
{
	char s[30];
	if (p != NULL) p = p->next;
	p = malloc(sizeof(slist));
	p->next = NULL;
	
	printf("inserisci nome nuovo prodotto e quantita': ");
	scanf("%s %d", s, &p->q);
	p->pcode = searchnpr(s,tp);
	return p;
}