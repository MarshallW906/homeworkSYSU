/*Copyright 2015 MarshallRna Wang*/
#include <stdio.h>
#include <string.h>
#include <time.h>

void prtrow();
void prtcoline();
void prtname(char name[]);
void prtnum(char num[]);
void prtcontact(char contact[]);

typedef struct {
    char name[10];
    char stdnum[9];
    char contact[20];
} Std;
int main() {
    clock_t start, end;
    double duration;
    start = clock();
    int n, i, k = 0;
    printf("Enter the number of students : \n");
    scanf("%d", &n);
    Std stu[n];
    printf("Enter the name(no more than 9 characters)\n");
    printf("ID(no more than 8 digits), contact(no more than 18 digits\n");
    printf("or it won't be printed) of each student one by one : \n");
    printf("Example :\n zhangsan 12345678 zhangsan@fbowl.com \n");
    printf("           lisi 87654321 lisi@fwitter.com\n");
    for (i = 0; i < n; ++i) {
        scanf("%s%s%s", &stu[i].name, &stu[i].stdnum, &stu[i].contact);
    }
    prtrow();
    prtcoline();
    printf("StudID    ");
    prtcoline();
    printf("Student name ");
    prtcoline();
    printf("contact                    |\n");
    prtrow();
    for (i = 0; i < n; ++i) {
        if ((strlen(stu[i].name) < 10) && (strlen(stu[i].stdnum) < 9) &&
        (strlen(stu[i].contact) < 19)) {
        prtcoline();
        prtnum(stu[i].stdnum);
        prtcoline();
        prtname(stu[i].name);
        prtcoline();
        prtcontact(stu[i].contact);
        prtcoline();
        printf("\n");
        k++;
        }
    }
    prtrow();
    printf("\n");
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    printf("%d valid rows in set (%f sec)\n", k, duration);
    return 0;
}

void prtrow() {
    printf("+-----------+--------------+----------------------------+\n");
}

void prtcoline() {
    printf("| ");
}

void prtname(char name[]) {
    printf("%-12s ", name);
}

void prtnum(char num[]) {
    printf("%-9s ", num);
}

void prtcontact(char contact[]) {
    printf("%-26s ", contact);
}

