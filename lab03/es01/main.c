#include <stdio.h>
#include <stdlib.h>

int searchrc(int *c,int n);
int *ricerca(int *v,int n);
int sum1sx(int r,int c,int *v,int n);
int sum1dx(int r, int c, int *v,int n);
int sum2sx(int r,int c,int *v,int n);
int sum2dx(int r,int c,int *v,int n);


int main()
{
    int *v,*original;
    FILE *f;
    int n,i,r,c;

    char x='a';
    if((f=fopen("in.txt","r"))==NULL)
    {
        puts("errore file in lettura.");
        exit(1);
    }

    fscanf(f,"%d",&n);
    v=malloc(n*n*(sizeof(int)));


    original=v;
    //v++;

    while((fscanf(f,"%d",v))!=EOF)
    {
        v++;
    }
    fclose(f);

    v=ricerca(original,n);
    c=(v-original);
    r=searchrc(&c,n);
    free(original);
    printf("l'alfiere sara' posizionato in %c%d\n",x+c,n-r);


    return 0;
}

int searchrc(int *c,int n)
{
    int i=0;
    while(*c>n)
    {
        i++;
        *c=*c-n;
    }
    *c--;
    return i;
}

int *ricerca(int *v,int n)
{
    int r,c,*s,max=0,*u,*solution;
    s=malloc(n*n*(sizeof(int)));
    u=s;
    for(r=0;r<n;r++)
    {
        for(c=0;c<n;c++)
        {
            *s=sum1sx(r,c,v,n)+sum1dx(r,c,v,n)+sum2sx(r,c,v,n)+sum2dx(r,c,v,n);
           // *s=*s+sum1dx(r,c,v);
            s++;
        }
    }
    for(r=0;r<n;r++)
    {
        for(c=0;c<n;c++)
        {
            if(u[r*n+c]>max)
                {
                    if(v[r*n+c]==0)
                    {
                      max=u[r*n+c];
                    solution=&v[r*n+c];
                    }
                }
        }
    }
    free(u);
    printf("la somma massima dei numeri percorribili dall'alfiere e' %d\n",max);
    return solution;
}
int sum1sx(int r,int c,int *v,int n)
{
    int sum=v[r*n+c];
    while (c>0 && r>0)
    {
        sum=sum+v[(r-1)*n+c-1];
        r--;
        c--;
    }
    return sum;
}
int sum1dx(int r, int c, int *v,int n)
{
    int sum=0;
    while(c+1<n && r>0)
    {
        sum=sum+v[(r-1)*n+c+1];
        r--;
        c++;
    }
    return sum;
}
int sum2sx(int r,int c,int *v,int n)
{
    int sum=0;
    while(c>0 && r+1<n)
    {
        sum=sum+v[(r+1)*n+c-1];
        r++;
        c--;
    }
    return sum;
}
int sum2dx(int r,int c,int *v,int n)
{
    int sum=0;
    while(c+1<n && r+1<n)
    {
        sum=sum+v[(r+1)*n+c+1];
        r++;
        c++;
    }
    return sum;
}
