#include "item.h"
typedef struct NODE *link;
typedef struct NODE
{
	item tab;
	link next;
}node;

node* insert_e(node *start);
void print_e(node*start);
void save_e(node*start);
node* freader_e(node *l);
int calcp_e(node*start);
node* delt_ef(node*l);
node* extract_e(node *l);