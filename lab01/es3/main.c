#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[])
{
	float media = 0;
	int n = 0;
	int nr, nc,r,c;
	int m[20][20] = { 0 };
	FILE *f;
	if ((f = fopen(argv[1], "r")) == NULL)
	{
		puts("errore file in lettura.");
		exit(1);
	}
	fscanf(f, "%d %d", &nr, &nc);
	for (r = 0; r < nr; r++)
	{
		for (c = 0; c < nc; c++)
		{
			fscanf(f, "%d", &m[r][c]);
		}
	}
	fclose(f);
	
	f = fopen("risulato.txt", "w");
	for (r = 0; r < nr; r++)
	{
		for (c = 0; c < nc; c++)
		{
			n = 0;
			media = 0;
			if (r - 1 >= 0)
			{
				if (c - 1 >= 0)
				{
					media = media + (float)m[r - 1][c - 1];
					n++;
				}
				media = media + (float)m[r - 1][c];
				n++;
				if (c + 1 < nc) {
					media = media + (float)m[r - 1][c + 1];
					n++;
				}
			}
			if (c - 1 >= 0)
			{
				media = media + (float)m[r][c - 1];
				n++;
			}
			if (c + 1 < nc)
			{
				media = media + (float)m[r][c + 1];
				n++;
			}
			if (r + 1 < nr)
			{
				if (c - 1 >= 0)
				{
					media = media + (float)m[r + 1][c - 1];
					n++;
				}
				media = media + (float)m[r + 1][c];
				n++;
				if (c + 1 < nc)
				{
					media = media + (float)m[r + 1][c + 1];
					n++;
				}
			}

			media = (float)media / n;
			fprintf(f, "%.1f ", media);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	return(0);
}

