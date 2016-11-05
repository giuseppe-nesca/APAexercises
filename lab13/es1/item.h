typedef struct ITEM *p_item;

p_item ITEMgen(char *nome, int cost); //used

int ITEMconf(char *s1,  p_item it);

void ITEMprint(p_item);

//int ITEMnetcheck(p_item a, p_item b);


char *ITEMnamereturn(p_item p);