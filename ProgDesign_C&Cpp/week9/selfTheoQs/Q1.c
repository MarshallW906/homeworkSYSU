#include <stdio.h>

void prtM(int a[][], int ell) {
    int i, j;
    for (i = 0; i < ell; i++)
        for (j = 0; j < ell; j++)
            printf("%d%c", a[i][j] + 526, j == ell - 1 ? '\n' : ' ');
}

int main() {
    int a[2][2], i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            scanf("%d", &a[i][j]);
    prtM(a, 2);
    return 0;
}
