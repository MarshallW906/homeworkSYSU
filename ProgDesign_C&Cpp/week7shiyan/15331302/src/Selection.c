/*Copyright 2015 Marshall Wang*/
#include <stdio.h>

int main() {
    int num[10000];
    int n, m;
    int i, j, temp;
    int min;
    scanf("%d", &n);
    while (n > 0) {
        scanf("%d", &m);
        for (i = 0; i < m; i++)
            scanf("%d", &num[i]);
        for (i = 0; i < m; i++) {
            min = i;
            for (j = i + 1; j < m; j++)
                if (num[min] > num[j]) min = j;
            temp = num[i];
            num[i] = num[min];
            num[min] = temp;
        }

        for (i = 0; i < m - 1; i++) {
            printf("%d ", num[i]);
        }
        printf("%d\n", num[i]);
        n--;
    }
    return 0;
}
