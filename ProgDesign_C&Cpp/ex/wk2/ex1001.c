#include <stdio.h>

int main()
{
	float a,b;
	scanf("%f%f",&a, &b);
	if (!b) {printf("Error!\n"); return 0;}
/* (!b)����˼��ʵ�� (b!=0) ifֻ�б��ʽֵΪ����ʱ��Ϊtrue */ 
	printf("%.2f\n",a/b);
/* �����ʽ���⣺ %A.Bf A��С����ǰ��λ��B��С�����λ��ǰ����Ҫ��f����������� */
	return 0;
}
