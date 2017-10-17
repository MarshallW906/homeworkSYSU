/*Copyright 2015 Marshall Wang*/
#include <stdio.h>

int main() {
    int num[10000];
    int n, i, j, m;

    scanf("%d", &n);
    while (n > 0) {
        scanf("%d", &m);
        for (i = 0; i < m; i++) {
            scanf("%d", &num[i]);
        }

        for (i = 0; i < m - 1; i++)
            for (j = 0; i + j  + 1 < m; j++)
                if (num[j] > num[j + 1])
                    num[j] ^= num[j + 1] ^= num[j] ^= num[j + 1];

        for (i = 0; i < m; i++)
            printf("%d%c", num[i], i == m - 1 ? '\n' : ' ');
        n--;
    }
    return 0;
}
