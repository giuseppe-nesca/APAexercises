//lab5_1 Numeri di bell
#include <stdio.h>
#include <stdlib.h>
long bin(int n, int k);
long fatt(int n);
long bell(int n);

int main()
{
	int n = 0,k=0,b=1;
	printf("inserisci un numero: ");
	scanf("%d", &n);
	
	printf("la soluzione e': %li", bell(n));

	return 0;
}

long bell(int n)
{
	int k = 0;
	long b = 1;
	for (k = 1;k < n;k++)
	{
		b =b+ bin(n - 1, k)*bell(k);
	}
	return b;
}

long bin(int n, int k)
{
	return fatt(n) / (fatt(k)*fatt(n - k));
}

long fatt(int n)
{
	if (n == 0) return 1;
	return n*fatt(n - 1);
}