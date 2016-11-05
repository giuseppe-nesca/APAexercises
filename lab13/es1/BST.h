#include "item.h"
typedef struct NODE *nlink;
typedef struct NODE
{
	int i;
	p_item item;
	nlink l, r;
}node;

typedef struct BST *pBST;
struct BST
{
	nlink root;
};

pBST BSTinit();
int BSTsearch(pBST,char*);
void BSTinsertl(pBST bst, int n,char*name,p_item);

void BSTprint(pBST bst);

