#include <stdio.h>
#include <stdlib.h>
#define N 100

float coeff(float x1,float x2,float y1,float y2);
int acquisizione(float *v);
int main()
{
    float v[N][3]= {0};
    float *p;
    int i=0, e=0;
    p=v;
    if(acquisizione(p)==-1)
    {
        puts("errore file in lettura.");
        exit (1);
    }
    while(v[i][2]==1)
    {
        while(v[e][2]==1)
        {
            if(v[i][0]-v[e][1]>=-0.01 && v[i][0]-v[e][1]<=0.01)
            {
                puts("esiste almeno una coppia di segmenti paralleli.");
                return 0;
            }
            e++;
        }
        e=0;
        i++;
    }
    puts("non ci sono segmenti paralleli.");


    return 0;
}

int acquisizione(float *v)
{
    FILE *f;
    float x[2][3]= {0},a=0;
    int i=0;

    if((f=(fopen("in.txt","r")))==NULL)
        return -1;

    fscanf(f,"%f%f%f",&x[0][0],&x[0][1],&x[0][2]);

    while((fscanf(f,"%f%f%f",&x[1][0],&x[1][1],&x[1][2]))!=EOF)
    {
        *v=coeff(x[0][0],x[1][0],x[0][1],x[1][1]);
        v++;
        *v=coeff(x[0][0],x[1][0],x[0][2],x[1][2]);
        v++;
        *v=1;
        v++;
        i++;
        if(i==N)
        {
            puts("troppe sezioni da analizzare.");
            exit (1);
        }
        //a=a+area(x[0][0],x[0][1],x[0][2],x[1][0],x[1][1],x[1][2]);
        a=a+((x[0][2]-x[0][1])+(x[1][2]-x[1][1]))*(x[1][0]-x[0][0])/2;
        x[0][0]=x[1][0];
        x[0][1]=x[1][1];
        x[0][2]=x[1][2];
    }
    fclose(f);
    printf("area compresa = %.2f\n",a);

    return 0;
}

float coeff(float x1,float x2,float y1,float y2)
{
    float dx,dy;
    dx=x2-x1;
    dy=y2-y1;
    return dy/dx;
}

