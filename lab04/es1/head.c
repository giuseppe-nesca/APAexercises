#include <stdlib.h>
#include <stdio.h>

FILE *fopenr(char nomefile[])
{
	FILE *f;
	if ((f=fopen(nomefile, "r")) == NULL)
	{
		printf("errore apertura in lettura del file '%s'",nomefile);
		exit(1);
	}
	return f;
}

