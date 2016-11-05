#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 17 /* 16 + 1 per '\0' */

typedef struct nodo* link;

struct nodo {
  char val[MAXS];
  link left;
  link right;
};

link new_nodo(char *val);
link leggi_nodo(FILE *in);
link leggi_albero(char *filename);
void libera_albero(link root);

// mie fun
void change(int *x, int *y);
int count(link h);
int altezza(link h);
void lettore(link h, int l1, int l2);
//void lettore2(link h, int n);
int verifica(link r1, link r2);


link new_nodo(char *val) {
    link n = malloc(1*sizeof(*n));
    strcpy (n->val,val);
    n->left = NULL;
    n->right = NULL;
    return n;
};


void display_albero(link root) {
    if (root == NULL) return;
    printf("nodo %s\n", root->val);
    display_albero(root->left);
    display_albero(root->right);
}

void libera_albero(link root) {
    if (root == NULL) return;
    libera_albero(root->left);
    libera_albero(root->right);
    free(root);
}

link leggi_nodo(FILE *in) {
    char val[MAXS];
    int l, r;
    if (fscanf(in, "%s %d %d", val, &l, &r) != 3) return NULL;
    link n = new_nodo(val);
    if (l!=0) n->left = leggi_nodo(in);
    if (r!=0) n->right = leggi_nodo(in);
    return n;
}

link leggi_albero(char *filename) {
    FILE *in;
    in = fopen(filename, "r");
    link root = leggi_nodo(in);
    fclose(in);
    return root;
}

int main(int argc, char **argv) {
  link root,root1,root2;
  int h = 0;
  int l1, l2;

  root = leggi_albero(argv[1]);

  /* inserire qui la parte richiesta */
  /* se necessario, dichiarare e leggere un secondo albero */
  printf("sto lavorando con: %s\n\n", argv[1]);
  root1 = root;

  printf("numero nodi con 2 figli: ");
  h=count(root);
  printf("%d\n\n", h);

  //ipotesi 1
  h = altezza(root);
  if (h >= 0) {
  printf("inserisci valori per l1 e l2:  "); scanf("%d%d", &l1, &l2);
  //controllo
  if (l1 > l2) change(&l1, &l2);
  

	  while (l1 > h)
	  {
		  printf("l1 troppo grande. Inserire l1 minore o uguale a %d: ", h); scanf("%d", &l1);
	  }
	  while (l2 > h)
	  {
		  printf("l2 troppo grande. Inserire l2 minore o uguale a %d: ", h); scanf("%d", &l2);
	  }

	  printf("nodi tra l1 e l2: ");lettore(root, l1, l2);printf("\n\n");


  //ipotesi 2: lettore2
  //printf("nodi di l1: ");lettore2(root, 1);printf("\n");
  //printf("nodi di l2: ");lettore2(root, 2);printf("\n\n");
  printf("root1:\n");
  display_albero(root);
  printf("\n\n");
  }
  else 	  puts("attenzione: albero vuoto");
 
  
  //lettura secondo albero
  root = leggi_albero(argv[2]);
  root2 = root;
  printf("sto lavorando con: %s\n\n", argv[2]);

  printf("numero nodi con 2 figli: ");
  h = count(root);
  printf("%d\n\n", h);

  //ipotesi 1
  h = altezza(root);
  if (h >= 0) {
  printf("inserisci valori per l1 e l2:  "); scanf("%d%d", &l1, &l2);
  //controllo
  if (l1 > l2) change(&l1, &l2);
  

	  while (l1 > h)
	  {
		  printf("l1 troppo grande. Inserire l1 minore o uguale a %d: ", h); scanf("%d", &l1);
	  }
	  while (l2 > h)
	  {
		  printf("l2 troppo grande. Inserire l2 minore o uguale a %d: ", h); scanf("%d", &l2);
	  }

	  printf("nodi tra l1 e l2: ");lettore(root, l1, l2);printf("\n\n");

	  printf("root2:\n");
	  display_albero(root);
	  printf("\n\n");

  }
  else 	  puts("attenzione: albero vuoto");

  //verifica isomorfismo
  h=verifica(root1, root2);
  if (h == 0) printf("c'e' un isormorfismo\n");



  //printf("root1:\n");
  //display_albero(root);
  libera_albero(root1);
  libera_albero(root2);
  return 0;
}

int verifica(link r1, link r2)
{
	if (r1 == NULL && r2 == NULL) return 0;
	if (r1 == NULL || r2 == NULL) return 1;
	if (strcmp(r1->val, r2->val)==0)
	{
		if (r1->left != NULL && r2->left != NULL) return verifica(r1->left, r2->left);
		if (r1->right != NULL && r2->right != NULL) return verifica(r1->right, r2->right);
		return 0;
	}
	else return 1;
}

int altezza(link h)
{
	int u, v;
	if (h == NULL) return - 1;
	u = altezza(h->left);
	v = altezza(h->right);
	if (u > v) return u + 1;
	else return v + 1;
}

void lettore(link h,int l1,int l2)
{
	static int l = 0;
	int backup;
	
	/*if (l>=l1 && l<=l2)
	{
		printf("%s ", h->val);
	}*/
	if (l1 == 0 && l == 0) printf("%s ", h->val);
	//printf("\n");
	if (l >= l1 - 1 && l <= l2 - 1)
	{
		if (h->left != NULL) printf("%s ", h->left->val);
		if (h->right != NULL) printf("%s ", h->right->val);
	}
	l++;
	if (l > l2) return;
	backup = l;
	if(h->left !=NULL) lettore(h->left, l1, l2);
	l = backup;
	if(h->right !=NULL) lettore(h->right,l1,l2);
	l = 0;
	return;
}



int count(link h)
{
	if (h == NULL) return 0;
	if(h->left!=NULL && h->right!=NULL) return count(h->left) + count(h->right) + 1;
	return count(h->left) + count(h->right);
}
void change(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
