#include <stdio.h>

int main() {
    int n, x, y, i, flag, step;
    scanf("%d%d%d", &n, &x, &y);
    int a[60];
    flag = n;
    for (i = 0; i < n; a[i++] = 1) {;}
    for (i = x;;) {
        a[i] = 0;
        printf("%d ", i);
        if (--flag == 0) break;
        for (step = 0; step < y;) {
            i++;
            if (i == n) i -= n;
            if (a[i] != 0) step++;
        }
    }
    puts("");
    return 0;
}
