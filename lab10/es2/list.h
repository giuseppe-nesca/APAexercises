#include "prod.h"
//typedef struct SLIST *linkls;
//typedef struct PLIST * linkpr;
//typedef struct Prodotti * linkprod;


typedef struct TABL *l_tabls;

l_tabls aqlist(char*filename, l_tabp tabprod); //
//void addlistpr(FILE*f, int remained, linkpr *head, linkpr *tail, linkpr tmp, l_tabp tabprod);
void printall(l_tabls tabl, l_tabp tabp); //
//void printlist(linkls l, l_tabp p);
//void printnode(linkpr l, l_tabp p);
void calcost(l_tabls tabl, l_tabp tabp, float flag); //
//void calcost2(linkls l, l_tabp tabp, float *flag);
//void calcost3(linkpr l, l_tabp tabp, float *flag);
void newslist(l_tabls t); //
void findlist(l_tabls tl, l_tabp tp); //
//linkpr newnode(linkpr p, l_tabp tp);