#include <stdio.h>
#include <stdlib.h>
#define N 3

void stampa(FILE *f,char c,int a);
int main()
{
    FILE *fr,*fw;
    char c1,c2;
    int a=0;
    if((fr=fopen("in.txt","r"))==NULL)
    {
        puts("errore apertura file in lettura");
        exit (1);
    }
    if((fw=fopen("out.txt","w"))==NULL)
    {
        puts("errore apertura file in scrittura");
        exit(1);
    }

    c1=fgetc(fr);
    a++;
    while((c2=fgetc(fr))!=EOF)
    {
        if(c2==c1)
        {
            a++;
        }
        else
        {
            stampa(fw,c1,a);
            c1=c2;
            a=1;
        }
    }
    stampa(fw,c1,a);
    fclose(fr);
    fclose(fw);

    return 0;
}

void stampa(FILE *f,char c,int a)
{
    int i=0;

        if(a<N)
        {
            for(i=0; i<a; i++)
                fprintf(f,"%c",c);
            }
        else
        {
            fprintf(f,"$%d$%c",a,c);
        }
}
