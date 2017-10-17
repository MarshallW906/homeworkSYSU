#include <stdio.h>

int calcc(int b1, int b2, int n);

int main() {
    int a, b, c;
    int n;
    scanf("%d%d%d", &a, &b, &n);
    c = calcc(a, b, n);
    printf("%d\n", c);
    return 0;
}

int calcc(int b1, int b2, int n) {
    if (n == 1) return b1;
    if (n == 2) return b2;
    return (calcc(b1, b2, n - 2) % 10007)
           * (calcc(b1, b2, n - 1) % 10007) % 10007;
}
