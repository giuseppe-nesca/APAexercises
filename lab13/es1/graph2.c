#include <stdio.h>
#include <stdlib.h>
//#include "graph.h"
#include "graph2.h"
#define MAX_INT 1000000


//parte da ADTlistacoda
typedef struct QQ *Q;
typedef struct LISTE *n_link;
struct QQ
{
	n_link head;
	n_link tail;
};
struct LISTE
{
	Edge e;
	n_link next;
};

Q Qinit()
{
	Q q = malloc(sizeof*q);
	q->head = q->tail = NULL;
	return q;
}

Edge Qget(Q q)
{
	Edge e = q->head->e;
	n_link l = q->head->next;
	free(q->head);
	q->head = l;
	return e;
}

void Qput(Q q, Edge e)
{
	n_link l = malloc(sizeof *l);
	l->e = e; l->next = NULL;
	if (q->head == NULL)
	{
		q->tail = q->head = l;
	}
	else
	{
		q->tail->next = l;
		q->tail = l;
	}
	return;
}

int Qempty(Q q)
{
	if (q->head == NULL)
		return 1;
	else return 0; //
}
//end parte listacoda




int bfs(Graph G, Edge e, int *time, int *pre, int *st)
{ 
	int v=0;
	//link l;
	Q q = Qinit();
	//Q q = NULL;
	Qput(q, e);
	while (!Qempty(q))
		if (pre[(e = Qget(q)).w] == -1)
		{
			pre[e.w] = (*time)++;
			st[e.w] = e.v;

			//lavora con matrice delle adiacenze qui sotto
			for (v = 0; v < G->V; v++)
				if (G->mat[e.w][v] != 0) {
					if (pre[v] == -1)
						Qput(q, EDGEcreate(e.w, v, 1));
				}
		}
	v = e.w;
	int cont = 0;
	while (st[v] != v)
	{
		v = st[v]; cont++;
	}
	return cont;
}

void GRAPHbfs(Graph G) 
{
	int v, time = 0, *pre, *st;
	pre = malloc(G->V*sizeof(int));
	st = malloc(G->V*sizeof(int));
	/*for (v = 0; v < G->V; v++)
	{
		pre[v] = -1;
		st[v] = -1;
	}*/
	//bfs(G, EDGEcreate(0, 0, 1), &time, pre, st);
	
	//versione personalizzata
	int i;
	int max = 0;
	int tmp = 0;
	for (i = 0;i < G->V;i++)
	{
		time = 0;
		for (v = 0; v < G->V; v++)
		{
			pre[v] = -1;
			st[v] = -1;
		}
		tmp = bfs(G, EDGEcreate(i, i, 1), &time, pre, st);
		if (tmp > max) max = tmp;

	}
	/*printf("\n Resulting BFS tree \n");
	for (v = 0; v < G->V; v++)
		if (st[v] != -1)
			printf("%s’s parent is: %s\n", STretrieve(G->tab, v), STretrieve(G->tab, st[v]));*/
	printf("diametro: %d\n", max);
}




void allPaths(int pos, Edge* e, int *pesomax, Graph G, int* archi, int peso, Edge* best, int curarchi, int visited[])
{
	int j;
	link t;
	int terminal = 1;

	visited[pos] = 1;

	for (t = G->adj[pos]; t != NULL; t = t->next)
	{

		if (visited[t->v] == 0)
		{

			e[(curarchi)] = EDGEcreate(pos, t->v, t->wt);
			allPaths(t->v, e, pesomax, G, archi, peso + (t->wt), best, curarchi + 1, visited);
			terminal = 0;
		}

	}

	if (terminal == 1)
	{
		if ((peso)>(*pesomax))
		{
			*(pesomax) = (peso);
			(*archi) = curarchi;
			for (j = 0; j<(*archi); j++)
				best[j] = e[j];
		}
	}

	visited[pos] = 0;
}

void GRAPHbestprint(Graph G, Edge e)
{
	printf("%s ---> %s %d\n", STsearch(e.v,G->tab), STsearch(e.w, G->tab), e.wt);
}

void path(Graph G)
{

	Edge* best = malloc(G->E*(sizeof(Edge)));
	Edge* e = malloc(G->E*(sizeof(Edge)));
	int* visited = malloc(G->V*sizeof(int));
	int pesomax = -(MAX_INT);
	int i;
	int archi = 0;

	for (i = 0; i<G->V; i++)
		visited[i] = 0;

	for (i = 0; i<G->V; i++)
	{
		allPaths(i, e, &pesomax, G, &archi, 0, best, 0, visited);
	}
	
	free(visited);
	free(e);
	
	printf("Cammino semplice a peso massimo:%d\n", pesomax);
	
	for (i = 0; i<archi; i++)
	{
		GRAPHbestprint(G, best[i]);
	}

	free(best);

}