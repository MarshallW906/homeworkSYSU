#include <stdio.h>
#include <string.h>

char num1[301], num2[301];
int main(){
	scanf("%s%s", num1, num2);
	int flag = strcmp(num1,num2);
	if (flag > 0){
		printf(">\n");
		return 0;
	}else if (flag == 0){
		printf("=\n");
		return 0;
	}
	printf("<\n");
	return 0;
}