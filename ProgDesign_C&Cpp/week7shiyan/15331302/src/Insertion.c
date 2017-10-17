/*Copyright 2015 Marshall Wang*/
#include <stdio.h>

int main() {
    int num[10000];
    int n;
    int i, j, temp, m;
    scanf("%d", &n);
    while (n > 0) {
        scanf("%d", &m);
        for (i = 0; i < m; i++) {
            scanf("%d", &num[i]);
        }
        for (i = 1; i < m; i++) {
            temp = num[i];
            for (j = i - 1; j >= 0 && num[j] > temp; j--) {
                num[j + 1] = num[j];
            }
            num[j + 1] = temp;
        }
        for (i = 0; i < m - 1; i++) {
            printf("%d ", num[i]);
        }
        printf("%d\n", num[i]);
        n--;
    }
    return 0;
}
