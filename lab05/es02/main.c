#include <stdio.h>
#include <stdlib.h>
void gray1(char s[], int n);
void gray2(char s[], int n);
int N;
int main() 
{
	int i,n=0;
	scanf("%d", &N);
	char* s = malloc((N+1)*sizeof(char));
	for (i = 0;i < N - 1;i++)
		s[i] = '0';
	s[N] = '\0';
	gray1(s, n);


	return 0;
}

void gray1(char s[],int n)
{
	if (n == N)
	{
		printf("%s\n", s);
		return;
	}
	s[n] = '0';
	gray1(s, n + 1);
	s[n] = '1';
	gray2(s, n + 1);
	return;
}

void gray2(char s[],int n)
{
	if (n == N)
	{
		printf("%s\n", s);
		return;
	}
	s[n] = '1';
	gray1(s, n + 1);
	s[n] = '0';
	gray2(s, n + 1);
	return;
}