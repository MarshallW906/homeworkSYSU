/*Copyright 2015 MarshallRna Wang*/
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void setrndcolor();

int main() {
    clock_t start, end;
    start = clock();
    double duration;

    char str[100];
    char *str1 = "MarshallRna";
    char *str2 = "RnaMarshall";
    gets(str);
    setrndcolor();
    puts(str);
    puts(str1);
    puts(str2);

    setrndcolor();
    printf("The length is %d\n", strlen(str));

    setrndcolor();
    int i = strcmp(str1, str2);
    if (i > 0)
        printf("str1 is \'bigger\' than str2.\n");
    else if (i < 0)
        printf("str1 is \'smaller\' than str2.\n");
    else
        printf("str1 is equal to str2.\n");
    setrndcolor();
    strcpy(str, str1);
    printf("%s\n", str);

    setrndcolor();
    strncpy(str, str1, 8);
    printf("%s\n", str);

    setrndcolor();
    strcpy(str, str1);
    strcat(str, str1);
    printf("%s\n", str);

    setrndcolor();
    strcpy(str, str1);
    strnset(str, 'o', 5);
    printf("%s\n", str);

    setrndcolor();
    strcpy(str, str1);
    strrev(str);
    printf("%s\n", str);

    setrndcolor();
    char *dup_str = strdup(str);
    strcat(str, dup_str);
    free(dup_str);
    printf("%s\n", str);

    end = clock();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
    return 0;
}

void setrndcolor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 16);
}
