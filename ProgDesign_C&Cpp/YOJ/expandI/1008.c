#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    int m, n, a[5], b[5], i, sum;
    while (t > 0) {
        scanf("%d%d", &m, &n);
        for (i = 0; i < n; i++) scanf("%d%d", &a[i], &b[i]);
        sum = 0;
        for (i = 0; i < n; i++)
            sum += a[i] * b[i];
        if (sum <= m) printf("%d\n", m - sum);
        else printf("Not enough\n");
        t--;
    }
    return 0;
}
