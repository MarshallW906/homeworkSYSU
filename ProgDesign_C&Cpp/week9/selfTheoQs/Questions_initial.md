// Question 1:
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

/*
    if the input is " 1 2 3 4\n", then the output is ____.
    a) 1 2
       3 4
    b) 527 528 529 530
    c) Compile error
    d) 527 528
       529 530
*/

// Question 2: (A Dessert)
#include <stdio.h>

int main() {
    int i, n, q, r, src[10000];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        src[i] = src[i + n] = i + 1;
    scanf("%d", &r);
    q = src[r - 1];
    for (i = 0; i < 2 * n; i++)
        q ^= src[i];
    printf("%d\n", q);
    return 0;
}

/*
    if the input is "520520526\n526526\n", then the output is ____,
    a) (Overflow, so the output is junk)
    b) 520526
    c) 526520
    d) 526526
*/

// Question 3:

#include <stdio.h>

int functionhahahahahahah(int n) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    return functionhahahahahahah(n - 1) + functionhahahahahahah(n - 2);
}

int main() {
    printf("%c %d %.0f\n", functionhahahahahahah(10), functionhahahahahahah(functionhahahahahahah(6)), functionhahahahahahah(functionhahahahahahah(functionhahahahahahah(5))));
    return 0;
}

/*
    the output of this code is ______.
    a) 7 21 0
    b) Runtime Error
    c) 54 87 5
    d) Compile Error
*/
