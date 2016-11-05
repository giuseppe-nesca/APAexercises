//#include "list.h"

typedef struct Prodotti * linkprod;



typedef struct Tbp *l_tabp;

l_tabp aqprod(FILE *f); //
int  searchnpr(char *s, l_tabp tp);
char* searchpnpr(int i, l_tabp p);
float price(int i, l_tabp p);
