#include <stdio.h>

int flag=0;
void prtco(int m)
{
	if (flag && m>0) printf("+"); 
	flag=0;
}
/* 用flag和flagg变量控制是否需要输出符号，并在prtco()函数中添加判断是否需要输出+号（因为若系数为负则不需要额外输出一个+号） */

int main()
{
	int a1,a2,b1,b2,a,b,c,flagg=0;
	scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
	a=a1*a2;
	b=a1*b2+a2*b1;
	c=b1*b2;
	if (a) { flagg=1;flag=1; if (a==1) printf("x^2"); else printf("%dx^2",a);}
	
	if (b) { flagg=1;prtco(b);
			if (b==1) printf("x"); else printf("%dx",b); flag=1;}
	
	if (c) { prtco(c); printf("%d",c);}
	if (!flagg) printf("0");
	printf("\n");
	return 0;
}
