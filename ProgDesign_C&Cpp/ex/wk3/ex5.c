#include <stdio.h>

int alti[100];

int main()
{
	int height,n,i,nout = 0;
	scanf("%d%d", &height, &n);
	for(i = 0; i < n; i++){
		scanf("%d", &alti[i]);
		if (alti[i] <= height) nout++;
	}
	printf("%d\n", nout);
	return 0;
}
