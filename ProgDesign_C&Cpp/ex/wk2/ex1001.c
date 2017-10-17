#include <stdio.h>

int main()
{
	float a,b;
	scanf("%f%f",&a, &b);
	if (!b) {printf("Error!\n"); return 0;}
/* (!b)的意思其实是 (b!=0) if只有表达式值为非零时视为true */ 
	printf("%.2f\n",a/b);
/* 输出格式问题： %A.Bf A是小数点前几位，B是小数点后几位（前提是要用f输出浮点数） */
	return 0;
}
