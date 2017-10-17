#include <stdio.h>
#include <string.h>

char a[81],b[81];

void decode_put(char c, int j);

int main()
{
	gets(a);
	int i = 0;
	do{
		decode_put(a[i++], i);
	}while(a[i] != '\0');
	b[i] = '\0';
	printf("%s", b);
	printf("\n");
	return 0;
}

void decode_put(char c, int j){
	if (isupper(c)){
		b[j] = 155 - c;
	}
	b[j] = 219 - c;
	printf("%c", b[j]);
}
