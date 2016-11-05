#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define C 82


int main()
{
    char s[C],rif[20][C-1],*t;
    int a=0,b=0,flag=0;
    FILE*f1,*f2;
    if((f1=fopen("in.txt","r"))==NULL)
    {
        puts("errore file in lettura.");
        exit (1);
    }
    f2=fopen("ou.txt","w");

    while((fgets(s,C,f1))!=NULL)
    {
        if(s[0]=='$')
        {
            t=strtok(s,"$");
        }
        else
        {
            //fputs(t,f2);
            t=strtok(s,"$");
            fputs(t,f2);
            t=strtok(NULL,"$");
        }
        while(t!=NULL)
        {
            for(b=0; b<=a; b++)
                if(!strncmp(t,rif[b],C))
                {
                    flag++;
                    fprintf(f2,"[%d]",b+1);
                    }
                    if(flag==0)
                    {
                        strcpy(rif[a],t);
                        fprintf(f2,"[%d]",a+1);
                        a++;
                    }
                    else flag=0;

                    t=strtok(NULL,"$");
                    fputs(t,f2);
                    t=strtok(NULL,"$");

        }

    }
    fclose(f1);
    fclose(f2);

    f1=fopen("rif.txt","w");
    for(b=0;b<a;b++)
        {
    fprintf(f1,"[%d] %s\n",b+1,rif[b]);
    }
    fclose(f1);






    return 0;
}

