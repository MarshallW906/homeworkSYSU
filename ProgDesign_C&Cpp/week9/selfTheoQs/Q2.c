#include <stdio.h>

int main() {
    int i, n, q, r, src[10000];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        src[i] = i + 1;
        src[i + n] = i + 1;
    }
    scanf("%d", &r);
    q = src[r - 1];
    for (i = 0; i < 2 * n; i++)
        q ^= src[i];
    printf("%d\n", q);
    return 0;
}
