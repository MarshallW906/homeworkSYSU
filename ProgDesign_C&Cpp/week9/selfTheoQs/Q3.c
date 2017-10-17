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
