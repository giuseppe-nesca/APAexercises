#include <stdio.h>
#include <stdlib.h>
#include "graph2.h"

int main()
{
	Graph G = GRAPHread();


	GRAPHmatgen(G);
	GRAPHbfs(G);
	path(G);
	system("pause");

	return 0;
}