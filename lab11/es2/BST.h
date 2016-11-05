
#include "item.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
int BSTcount(BST bst);
int BSTempty(BST bst);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
void BSTshow(BST bst, int tipo_ordine);
void BST_find(BST bst);

void BSTexport(BST bst);
void BSTimport(BST bst);

void BSTfree(BST bst);