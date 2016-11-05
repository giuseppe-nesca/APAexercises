#include "graph.h"

typedef struct node *link;
struct node {
	int v; int wt; link next;
};

struct graph { int V; int E; link *adj; pSS tab; link z; int **mat; };


void GRAPHbfs(Graph G);
void path(Graph G);
