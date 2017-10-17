/*Copyright 2015 MarshallRna Wang*/
#include <stdio.h>
#include <time.h>
#include <windows.h>

int main() {
    clock_t start, end;
    start = clock();
    double duration;
    int color, i = 0;
    char c;
    for (color = 0; color < 16; color++) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("Hello world!\n");
    }
    printf("Now will print every time\n");
    printf(" you press a key except \'x\'(to exit)\n");
    c = getch();
    while ((c = getch()) != 'x') {
        i++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 16);
        printf("Hello world!\n");
    }
    printf("total lines : %d\n", i + 16);
    end = clock();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
    return 0;
}
