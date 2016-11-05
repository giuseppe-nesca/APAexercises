#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[])
{
	int i,c;
	FILE *fr;
	FILE *fw;
	char name[20],v[22];
	
	if ((fr = fopen(argv[1], "r")) == NULL)
	{
		puts("errore: file inserito non esistente.");
		exit(1);
	}
	puts("inserisci nome file output:");
	gets(name);
	fw = fopen(name, "w");
	while ((fscanf(fr, "%s", v)) != EOF)
	{
		i = 0;
		c = 0;
		while (v[i] != '\0')
		{
			if (v[i] == 'A' || v[i] == 'E' || v[i] == 'I' || v[i] == 'O' || v[i] == 'U' || v[i] == 'a' || v[i] == 'e' || v[i] == 'i' || v[i] == 'o' || v[i] == 'u')
			c++;
			i++;
		}
		if (c <= 2)
			fprintf(fw,"%s\n",v);
	}
	fclose(fr);
	fclose(fw);

	return(0);
}