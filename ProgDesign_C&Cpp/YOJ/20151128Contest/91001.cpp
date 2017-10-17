#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j, k, q, flag;
    float m, src[22][22];
    scanf("%d%f", &n, &m);
    for (i = 2; i <= n; i++) {
        for (j = 1; j < i; j++) {
            flag = 0;
            src[i][j] = static_cast<float>(j) / static_cast<float>(i);
            for (q = 2; q < i; q++) {
                for (k = 1; k < i; k++)
                    if (fabs(src[i][j] - src[q][k]) < 1e-6) {flag = 1; break;}
                if (flag) break;
            }
            if (src[i][j] < m && !flag)
                printf("%d/%d\n", j, i);
        }
    }
    return 0;
}
