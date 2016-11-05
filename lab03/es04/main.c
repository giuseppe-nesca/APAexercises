#include <stdio.h>
#include <stdlib.h>
#define MAXS 20
#define N 5

typedef struct item_s {
int a, b;
char c;
float d;
char s[MAXS];
} Item;

int main()
{
    Item autom[N][N];
    FILE*f;
    int x,y;
    f=fopen("in.txt","r"); //aggiungi controlli

    for(y=0;y<N;y++)
    {
        for(x=0;x<N;x++)
        {
            fscanf(f,"%d%d %c%f%s",&autom[y][x].a,&autom[y][x].b,&autom[y][x].c,&autom[y][x].d,autom[y][x].s);
        }
    }
    fclose(f);
    puts("inserire x:");
    scanf("%d",&x);
    puts("inserire y:");
    scanf("%d",&y);
    printf("periodo produzione 1: %d\nperiodo produzione 2: %d\nclasse: %c\nprezzo: %f\nmodello: %s\n\n",autom[y][x].a,autom[y][x].b,autom[y][x].c,autom[y][x].d,autom[y][x].s);
    printf("indirizzi:\nperiodo produzione 1: %p\nperiodo produzione 2: %p\nclasse: %p\nprezzo: %p\nmodello: %p\n",&autom[y][x].a,&autom[y][x].b,&autom[y][x].c,&autom[y][x].d,autom[y][x].s);
    return 0;
}
