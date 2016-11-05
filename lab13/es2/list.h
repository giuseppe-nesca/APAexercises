#include "item.h"

typedef struct LIST *plist;
//typedef struct NODE *link;


void LISTinsert(pitem i, plist l);
plist LISTinit();
int find(plist l, int *tot, int f, int m);

