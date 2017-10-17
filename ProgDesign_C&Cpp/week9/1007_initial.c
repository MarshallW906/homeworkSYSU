#include <stdio.h>

void oper1(int length);
void oper2(int x, int length);
long long oper3(int l, int r);

long long num[100000];

int main() {
    int n, m, i, k = 0;
    scanf("%d%d", &n, &m);
    int operations[m];
    for (i = 0; i < n; i++)
        scanf("%lld", &num[i]);
    int flag = 1;
    long long x1 = 0, x2 = 0;

    for (k = 0; k < m; k++) {

        scanf("%d", &operations[k]);

        switch (operations[k]) {
            case 1 : {
                    flag *= -1;
                    break;
                }
            case 2 : {
                    long long x;
                    scanf("%d", &x);
                    if (flag == -1) x2 += x;
                    else x1 += x;
                    break;
                }
            case 3 : {
                    int l, r;
                    scanf("%d%d", &l, &r);
                    int width = r - l + 1;
                    printf("%d\n", oper3(l, r) * flag + width * flag * (x1 - x2));
                    break;
                }
        }
    }
    return 0;
}

void oper1(int length) {
    int q;
    for (q = 0; q < length; q++) {
        num[q] *= -1;
    }
}

void oper2(int x, int length) {
    int q;
    for (q = 0; q < length; q++) {
        num[q] += x;
    }
}

long long oper3(int l, int r) {
    int q;
    long long sum = 0;
    for (q = l; q <= r; q++)
        sum += num[q - 1];
    return sum;
}
