#include "item.h"
#include "BST.h"
typedef struct SS *pSS;

pSS SSinit(int num_V);
int search(pSS tabs, char *s);
void insert(pSS tabs, char *nome, int cost);

void SSalphaP(pSS tabs);

void SSnumP(pSS tabs, int v);

int SSnetcheck(pSS tabs, int a, int b);



char *STsearch(int i, pSS tab);