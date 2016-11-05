//lab7_1   Le Portate
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Portate
{
	int n;
	char **p;
}portate;

typedef struct Menu
{
	int all;
	int used;
	portate * link;
}menu;

menu acquisizione(menu tbellamenu);
int scelter(int pos, menu t, char **sol, int count);
//void scelte(menu t);
void printall(menu t);

int main()
{
	menu tabm; char **sol; int count=0;
	tabm.all = 5; tabm.used = 0;
	tabm.link = malloc(tabm.all*sizeof(portate));
	tabm = acquisizione(tabm);
	printall(tabm);
	sol = malloc(tabm.used*sizeof(char*));
	count = scelter(0, tabm, sol, 0);
	return 0;
}

menu acquisizione(menu t)
{
	FILE *f; int i=0,n=0,c=0; char s[100];
	if ((f=fopen("piatti.txt", "r")) == NULL)
	{
		puts("errore lettura file");
		exit(1);
	}
	while ((fscanf(f, "%d", &n)) > 0)
	{
		i++;
		while (t.all < i)
		{
			t.all = t.all * 2;
			t.link = realloc(t.link, t.all*sizeof(portate));
		}
		t.link[t.used].n = n;
		t.link[t.used].p = malloc(t.link[t.used].n*sizeof(char*));
		for (c = 0;c < n;c++)
		{
			fscanf(f, "%s", s); //sta un modo con strdup direttamente?
			t.link[t.used].p[c] = strdup(s);
		}
		t.used++;
	}

	fclose(f);
	return t;
}

/*void scelte(menu t)
{
	int i;
	for (i = 0;i < t.used;i++)
	{
		scelter(link[0])
	}
} */

int scelter(int pos,menu t,char **sol,int count)
{ //ho scelto di prendere le varie stringhe e stamparle, potevo anche prenderne la posizione e mano a mano andare a stampare quello che è puntato
	int  i = 0;
	if (pos < t.used)
	{
		for (i = 0;i < t.link[pos].n;i++)
		{
			sol[pos] = strdup(t.link[pos].p[i]);
			count = scelter(pos + 1, t, sol,count);
		}
	}
	else
	{
		for (i = 0;i < t.used;i++) printf("%s\n", sol[i]);
		printf("\n\n");
		return count + 1;
	}
	return count;
}

void printall(menu t)
{
	int a, b;
	for (a = 0;a < t.used;a++)
	{
		printf("portata %d   quantita': %d\n", a,t.link[a].n);
		for (b = 0;b < t.link[a].n;b++)
		{
			printf("%d  %s\n", b, t.link[a].p[b]);
		}
		printf("\n");
	}
}