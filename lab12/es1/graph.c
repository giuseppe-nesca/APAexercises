#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define MAX 30

typedef struct node *link;
struct node {
	int v; int wt; link next;
};

struct graph { int V; int E; link *adj; pSS tab; link z; int **mat; };

link NEW(int v,int wt, link next) {
	link x = malloc(sizeof *x);
	x->v = v; x->next = next; x->wt = wt;
	return x;
}


Graph GRAPHinit(int V) {
	int v;
	Graph G = malloc(sizeof *G);
	if (G == NULL) return NULL;
	G->V = V; G->E = 0; G->z = NULL; G->mat = NULL;
	G->adj = malloc(G->V*sizeof(link));
	for (v = 0; v < G->V; v++)
		G->adj[v] = G->z;
	G->tab = SSinit(V);
	if (G->tab == NULL) return NULL;
	return G;
}

void insertE(Graph G, Edge e) {		//solved... i suppose
	int v = e.v, w = e.w, wt = e.wt;
	G->adj[v] = NEW(w, wt, G->adj[v]);
	G->adj[w] = NEW(v, wt, G->adj[w]);
	G->E++;
}

Graph GRAPHread() {
	Graph G;
	char name[MAX], src[MAX], dst[MAX];
	int wt;
	FILE *fin;
	printf("Input file name: "); scanf("%s", name);
	fin = fopen(name, "r");
	if (fin == NULL) exit(-1);

	
	int i;
	fscanf(fin, "%d", &i);
	G = GRAPHinit(i);

	for (i = 0;i < G->V;i++)
	{
		fscanf(fin, "%s %s", src, dst);
		insert(G->tab, src, dst);		//da creare ancora
	}

	while (fscanf(fin, "%s %s %d", src, dst, &wt) == 3) {
		int id1 = search(G->tab, src);
		//	if (id1 == -1) id1 = STinsert(G->tab, src);//
		int id2 = search(G->tab, dst);
		//	if (id2 == -1) id2 = STinsert(G->tab, dst);//
		//	if (id1 < 0 || id2 < 0) continue;//
		insertE(G, EDGEcreate(id1, id2, wt));
	}
	fclose(fin);
	return G;
}

int GRAPH_Vnum(Graph G)
{
	return G->V;
}

void GRAPHalphaP(Graph G)
{
	SSalphaP(G->tab);
}

void GRAPHshowlink(Graph G)
{
	link p;
	int i,count=0;
	char s[MAX];
	printf("Inserisci nome da cercare: "); scanf("%s", s);
	i=search(G->tab, s);
	p =  G->adj[i];
	printf("%s e' collegato a:\n", s);
	while (p != NULL)
	{
		SSnumP(G->tab, p->v);
		count++;
		p = p->next;
	}
	printf("numero dei collegamenti: %d\n", count);
}

void infocopy(int**m, link*l,int V)
{
	int a;
	link p;
	for (a = 0;a < V;a++)
	{
		p = l[a];
		while (p != NULL)
		{
			if (m[a][p->v] == 0) m[a][p->v]=p->wt;
			p = p->next;
		}
	}
}

void GRAPHmatgen(Graph G)
{
	G->mat = malloc(G->V*sizeof (int*));
	int i,c;
	for (i = 0;i < G->V;i++)
	{
		G->mat[i] = malloc(G->V*sizeof(int));
		for (c = 0;c < G->V;c++)
			G->mat[i][c] = 0;
	}
	infocopy(G->mat, G->adj,G->V);

	for (i = 0;i < G->V;i++)
	{
		for (c = 0;c < G->V;c++)
		{
			printf("%d ", G->mat[i][c]);
		}
		printf("\n");
	}
}

void GRAPHwt(Graph G) 
{
	int in = 0, ex = 0;
	int a, b;
	if (G->mat == NULL) GRAPHmatgen(G);
	for (a = 0;a < G->V;a++)
	{
		for (b = a;b < G->V;b++)
		{
			if (SSnetcheck(G->tab, a, b) == 0)
			{
				in += G->mat[a][b];
			}
			else ex += G->mat[a][b];
		}
	}
	printf("flussi interni: %d\nflussi esterni: %d\n", in, ex);
}