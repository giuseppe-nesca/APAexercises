typedef struct ITEM *p_item;

p_item ITEMgen(char *elab, char *sret);

int ITEMconf(char *s1,  p_item it);

void ITEMprint(p_item);

int ITEMnetcheck(p_item a, p_item b);