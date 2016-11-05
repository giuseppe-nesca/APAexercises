#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LIST *linkl;
typedef struct PRODUCTS *linkp;
typedef struct NODE *linkn;

typedef struct TABP
{
	linkp head, tail;
	int np;
}tabp;

typedef struct TABL
{
	linkl head, tail;
	int nl;
}tabl;

typedef struct PRODUCTS
{
	char *name;
	float price;
	linkp prev, next;	
}products;

typedef struct LIST
{
	linkn pointer;
	linkl prev, next;
	int n;
}list;

typedef struct NODE
{
	linkp pointer;
	int n;
	linkn prev, next;
}node;

void takeproducts(tabp *Tabp);
void takelists(tabl *Tabl,tabp *tp);
linkp ricercas(char*s, tabp*t);
void printsum(linkl t);
void printallprod2(linkl t);
void printtot(linkl t);
void addlist(tabl *t, tabp *tp);
void addnode(tabl *t, tabp *tp);


void printallprod(linkp start, int n);
void printallprod2(linkl t);



int main()
{
	int select=1;
	tabp tp; tabl tl;
	takeproducts(&tp);

	takelists(&tl, &tp);
	
	
	while (select != 0)
	{
	printf("inserisci:\n"
		"1. stampa dettagli\n"
		"2. stampa costo di ogni lista\n"
		"3. stampa costo totale\n"
		"4. aggiungi lista\n"
		"5. aggiungi prodotto a una lista\n"
		"0. exit\n");
	scanf("%d", &select);
		
			switch (select)
			{
			case 1: //stampa dettagli
				printallprod2(tl.head);
				break;
			case 2: //costo di ogni lista
				printsum(tl.head);
				break;
			case 3: //costo totale
				printtot(tl.head);
				break;
			case 4: //aggiuhngi lista
				addlist(&tl, &tp);
				break;
			case 5: //aggiungi prodotto
				addnode(&tl, &tp);
				break;
			}

			//debug only
			//printallprod2(tl.head); //stampa dettagli
	}
	return 0;
		
}

void takeproducts(tabp *t)
{
	FILE *f = fopen("prodotti.txt", "r");
	char s[30];
	int i = 0;
	linkp x;
	if (f == NULL) exit(1);
	fscanf(f, "%d", &t->np);
	for (i = 0;i < t->np;i++)
	{
		x = malloc(sizeof(products));
		fscanf(f, "%s %f", s, &x->price); x->name = strdup(s);
		x->next = NULL;
		if (i == 0)
		{
			x->prev = NULL;
			t->head = x; t->tail = x;
		}
		else { x->prev = t->tail; t->tail->next = x; t->tail = x; }

	}
}

void takelists(tabl *t,tabp *tp)
{
	FILE *f = fopen("liste.txt", "r");
	int a, b;
	linkl x; linkn y,y2=NULL;
	char s[30];

	if (f == NULL) exit(1);
	fscanf(f, "%d", &t->nl);
	for (a = 0;a < t->nl;a++)
	{
		x = malloc(sizeof(list));
		if (a == 0)
		{
			x->prev = NULL; x->next = NULL; t->head = x; t->tail = x;
		}
		else
		{
			x->prev = t->tail; t->tail->next = x; x->next = NULL; t->tail = x;
		}
		fscanf(f, "%d", &x->n);
		for (b = 0;b < x->n;b++)
		{
			
			y = malloc(sizeof(node));
			if (b == 0)
			{
				x->pointer = y;
				y->prev = NULL; y->next = NULL; y2 = y;
			}
			else
			{
				y->next = NULL; y2->next = y; y2 = y;
			}

				fscanf(f, "%s %d", s,&y->n);
				y->pointer = ricercas(s, tp);	//funzione di ricerca di prodotto s

		}
	}

}

linkp ricercas(char*s,tabp*t)
{ 
	int i;
	linkp p=t->head;
	for (i = 0;i < t->np;i++)
	{
		if ((strcmp(s, p->name)) == 0) return p;
		else p = p->next;
	}
	puts("nessuna corrispondenza");
	return p;
}

void printallprod(linkp start,int n)
{
	linkp t = start;
	int i;
	for (i = 0;i < n;i++) {
		printf("%s %f\n", t->name, t->price);
		t = t->next;
	}
	printf("\n\n");
} //debug only

void printallprod2(linkl t)
{
	linkl p=t;
	linkn n;
	int c=0;
	while (p != NULL)
	{
		n = p->pointer;

		printf("%d\n", c);
		while (n != NULL)
		{
			printf("%s %d\n", n->pointer->name, n->n);
			n = n->next;
		}
		printf("\n");
		p = p->next;
		c++;
	}
	printf("\n\n");
}

void printsum(linkl t)
{
	linkl p = t;
	linkn n;
	float sum=0;
	while (p != NULL)
	{
		n = p->pointer;

		while (n != NULL)
		{
			//printf("%s %.2f\n", n->pointer->name, n->pointer->price);
			sum = sum+(n->pointer->price)*(n->n);
			n = n->next;
		}
		printf("%.2f\n",sum);
		sum = 0;
		p = p->next;
	}
	printf("\n\n");
}

void printtot(linkl t)
{
	linkl p = t;
	linkn n;
	float sum = 0;
	while (p != NULL)
	{
		n = p->pointer;

		while (n != NULL)
		{
			//printf("%s %.2f\n", n->pointer->name, n->pointer->price);
			sum = sum + (n->pointer->price)*(n->n);
			n = n->next;
		}
		//printf("%f\n", sum);
		p = p->next;
	}
	printf("%.2f\n\n",sum);
}

void addlist(tabl *t, tabp *tp)
{
	linkl x;
		x = malloc(sizeof(list));
		x->n = 0; x->pointer = NULL;
		if (t->head==NULL)
		{
			x->prev = NULL; x->next = NULL; t->head = x; t->tail = x;
		}
		else
		{
			x->prev = t->tail; t->tail->next = x; x->next = NULL; t->tail = x;
		}
		
		t->nl++;
}

void addnode(tabl *t, tabp *tp)
{
	int num, i,q; char s[30]; linkl point = t->head; linkn p;

	printf("inserisci numero lista a cui aggiungere elemento: "); scanf("%d", &num);
	printf("inserisci quantita' ed elemento: "); scanf("%d %s",&q, s);
	for (i = 0;i < num;i++)
	{
		point = point->next;
	}
	p = point->pointer;
	if (p != NULL) 
	{
		while (p->next != NULL) p = p->next;
		p->next = malloc(sizeof(node));
		p->next->prev = p; p->next->next = NULL;
		p->next->pointer = ricercas(s, tp);
		p->next->n=q;
		p->n++;
	}
	else
	{
		p = malloc(sizeof(node));
		p->prev = p;
		p->next = NULL;
		p->pointer = ricercas(s, tp);
		p->n=q;
		point->pointer = p;
	}
}