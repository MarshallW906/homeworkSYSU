#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    n++; m++;
    int plain[n][m], q, sx, sy, tx, ty, i, j;
    for (i = 1; i < n; i++)
        for (j = 1; j < m; j++)
            plain[i][j] = 0;
    for (q = 1; q <= k; q++) {
        scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
        for (i = sx; i <= tx; i++) {
            for (j = sy; j <= ty; j++) {
                plain[i][j]++;
            }
        }
    }
    int max = 0;
    for (i = 1; i < n; i++)
        for (j = 1; j < m; j++)
            if (plain[i][j] > max) max = plain[i][j];
    printf("%d\n", max);
    return 0;
}
