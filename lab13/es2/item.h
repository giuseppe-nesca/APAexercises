#define MAX 20
#define NFASI 4
typedef struct ITEM *pitem;

int ITEMcheck(pitem i, int f, int *tot, int m);
int ITEMconf(pitem a, pitem b);
pitem ITEMnew(FILE* f);
