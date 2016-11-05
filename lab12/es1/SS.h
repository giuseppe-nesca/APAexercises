#include "item.h"
#include "BST.h"
typedef struct SS *pSS;

pSS SSinit(int num_V);
int search(pSS tabs, char *s);
void insert(pSS tabs, char *elaboratore, char*sottorete);

void SSalphaP(pSS tabs);

void SSnumP(pSS tabs, int v);

int SSnetcheck(pSS tabs, int a, int b);