typedef struct Item
{
	int piority;
	char type[31];
	char code[11];
}item;

item insert_i();
void print_i(item*puntatab);
FILE*save_i(FILE*f,item *puntatab);
FILE* freader_i(FILE*f, item*l);
int prio(item*tab);
