#include <stdio.h>

int main()
{
	int i,j,n;
	scanf("%d",&n);
	for (i=1; i<n+1; i++)
	{
		for(j=1; j<=i; j++) printf("*");
		for(j=1; j<=(n-i); j++) printf("."); /* 先后输出若干*和 . ，i为当前行数并用以控制输出个数 */
		printf("\n");
	}
	return 0;
}
