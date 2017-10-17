#include <stdio.h>

char a[200];

void outp(int fl3, int fl2);

int main()
{
	scanf("%s", a);
	int sum = 0, i = 0, fl3 = 0, fl2 = 0;
	do{
		sum += (a[i++] - 48);
	}while(a[i] != '\0');
	if (sum % 3 == 0) fl3 = 1;
	if (a[--i] % 2 ==0 ) fl2 = 1;
	outp(fl3, fl2);
	return 0;
}

void outp(int fl3, int fl2){
	if ((fl3 == 0) && (fl2 == 0))
		printf("0\n");
	if ((fl3 == 0) && (fl2 == 1))
		printf("2\n");
	if ((fl3 == 1) && (fl2 == 1))
		printf("1\n");
	if ((fl3 == 1) && (fl2 == 0))
		printf("3\n");
}
