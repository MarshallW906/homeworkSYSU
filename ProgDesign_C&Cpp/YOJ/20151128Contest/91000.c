#include <stdio.h>

int trans(int n);

int main() {
    int num, tnum;
    scanf("%d", &num);
    do {
        tnum = trans(num);
        printf("%d: %d\n", num, tnum);
        scanf("%d", &num);
    } while (num != 0);
}

int trans(int n) {
    int t, p = 1, sum = 0;
    while (n) {
        t = n % 10;
        if (t > 8) t -= 2;
        else if (t > 3) t -= 1;
        sum += t * p;
        p *= 8;
        n /= 10;
    }
    return sum;
}
