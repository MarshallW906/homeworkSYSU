#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isReversal(char str[]);
int isPrime(long num);

int main() {
    int n, p = 0, q = 0;
    long num;
    char numstr[11];
    scanf("%d", &n);
    while (n > 0) {
        scanf("%ld", &num);
        sprintf(numstr, "%ld", num);
        p = isReversal(numstr);
        q = isPrime(num);
        if (p && q) printf("Yes\n");
        else printf("No\n");
        n--;
    }
    return 0;
}

int isReversal(char str[]) {
    int i, length = strlen(str);
    for (i = 0; i < length; i++)
        if (str[i] != str[length - i - 1]) return 0;
    return 1;
}

int isPrime(long num) {
    int i, j;
    if (num == 2) return 1;
    else if (num < 2 || num % 2 == 0) return 0;
    else {
        j = (int)sqrt(num + 1);
        for (i = 3; i <= j; i+=2)
            if (num % i == 0) return 0;
    }
    return 1;
}