#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 2

int stampain(int*p, int S,char in[]);
int main()
{
    char sn[20],sm[20];
    int n[N][N],m[M][M];
    int *p;
    int i,c,r,count=0,count2=0,a=0,b;
    FILE *f;
    printf("inserisci:\n1 per inserire da tastiera le matrici n e m\n2 per caricare le matrici n e m da file\n");
    scanf("%d",&i);
    switch (i)
    {

    case 1:
        //acquisizione n
        puts("inserisci n:");
        p=n;
        for(c=1; c<=(N)*(N); c++)
        {
            scanf("%d",p);
            p=p+1;
        }
        stampain(n,N,"n.txt");

        //acquisizione m
        puts("inserirsci m:");
        p=m;
        for(c=1; c<=(M)*(M); c++)
        {
            scanf("%d",p);
            p=p+1;
        }
        stampain(m,M,"m.txt");
        break;
    case 2:
        puts("inserisci file input n:");
        scanf("%s",sn);
        if((f=fopen(sn,"r"))==NULL)
        {
            puts("errore apertura file input.");
            exit(1);
        }
        else
        {
            p=n;
            for(c=1; c<=(N)*(N); c++)
            {

                fscanf(f,"%d",p);
                p=p+1;

            }
            f=fclose;

        }
        puts("inserisci file input m:");
        scanf("%s",sm);
        if((f=fopen(sm,"r"))==NULL)
        {
            puts("errore apertura file input.");
            exit(1);
        }
        else
        {
            p=m;
            for(c=1; c<=(M)*(M); c++)
            {

                fscanf(f,"%d",p);
                p=p+1;

            }
            f=fclose;
        }
        break;
    }





    //ricerca
    for(r=0; r<N-M; r++)
    {
        for(c=0; c<N-M; c++)
        {
            if(n[r][c]==n[0][0])
            {
                for(a=0; a<M; a++)
                {
                    for(b=0; b<M; b++)
                    {
                        if(n[r+a][c+b]==m[a][b])
                        {
                            count++;
                        }
                        else
                        {
                            count=0;
                            a=N;
                            b=a;
                        }
                    }
                }
                if(count==(M)*(M))
                {
                    count2++;
                    printf("m e' presente in n alle coordinate (%d,%d)\n",r,c);
                }
                count=0;


            }
        }
    }



printf("m presente in n %d volte\n",count2);






system("pause");
return 0;
}

int stampain(int*n, int S,char in[])
{
    FILE *f;
    int c,*p;
    p=n;
    f=fopen(in,"w");
    for(c=1; c<=(S)*(S); c++)
    {

        fprintf(f,"%d ",*p);
        if(c%(S)==0)
            fprintf(f,"\n");

        p=p+1;
    }
    fclose(f);
    return 0;

}
