#include <stdio.h>

char str[202];

int main()
{
	unsigned int i=0,sum=0;
	scanf("%s",&str);
	do{
		sum+=(str[i++]-48);
	}while (str[i]!='\0');
	printf("%d\n",sum);
	return 0;
}

/* unsigned int 是无符号整数 范围是0-65535 有符号的为-32768~32767，这里为了节省空间就没用long
   录入一个长度最长为201（这里为了防止意外写了202）的字符串，然后用do-while循环分别对每个字符进行计算
   并累加到sum中。字符对应的数值参照ASCII码表的十进制部分 */
/* 扩展题还是需要多看书查新知识，否则想做出来比较吃力 */