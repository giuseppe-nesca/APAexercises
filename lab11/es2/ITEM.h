#define MAX 31
#define MAX2 11

typedef struct ITEM * Item;

void stampa_Item(Item a);
Item inserimento_item(float p, char prod[]);
Item ITEMsetvoid();
int ITEMless(Item x, Item y);

Item ITEMnew();
float ITEMprice(Item item);
char *ITEMproduct(Item item);
void ITEMstampF(Item t, FILE *f);

void ITEMfree(Item t);
