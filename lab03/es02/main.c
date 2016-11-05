#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 5


void mul (int *v1, int *v2, int n, int *v3);
int main()
{
    int v1[N]= {0},v2[N]= {0},v3[2*N]= {0},i=0,e;
    char c[N+1];
    printf("inserire un numero v1 di massimo %d cifre\n",N);
    scanf("%s",c);

    for(e=strlen(c)-1; e>=0; e--)
    {
        v1[i]=c[e]-'0';
        i++;
    }
    i=0;
    printf("inserire un numero v2 di massimo %d cifre\n",N);
    scanf("%s",c);
    for(e=strlen(c)-1; e>=0; e--)
    {
        v2[i]=c[e]-48;
        i++;
    }
    mul(v1,v2,N,v3);
    return 0;
}

void mul (int *v1, int *v2, int n, int *v3)
{
    int a,b;
    for(a=0; a<n; a++)
    {
        for(b=0; b<n; b++)
        {
            v3[a+b]=v3[a+b]+v2[a]*v1[b];
        }
    }
    for(a=0; a<2*n-1; a++)
    {
        while(v3[a]>9)
        {
            v3[a]=v3[a]-10;
            v3[a+1]++;
        }
    }
    for(a=2*n-1; a>=0*n; a--)
    {
        printf("%d",v3[a]);
    }
}
