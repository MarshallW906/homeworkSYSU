#include "UIshell.h"

void cls() {
    system("cls");
}

void prtLstart() {
    printf(">> ");
}

void prtLine() {
    puts("-----------------------------------------------------------");
}

void prtFrame() {
    printf(" No  |        Name        |Gender|Prog|pml|Calc|LinearA|Eng|Hist| PE| GPA\n");
}

void prtWelcome() {
    printf("------Welcome to Marshall's student management System------\n\n");
}

void prtChoose() {
    printf("\nChoose one and enter :\n");
}

void prtMainUIforTeacher() {
    prtChoose();
    printf("e E : Open/Create an Class[...]\n");
    printf("q Q : Quit the System\n");

    printf("\n[ Notice ] : If choosing to open a class which doesn't exist,\n");
    printf("             then will create a new Class with the name entered.\n");
    printf("\n");
}

void prtClassSubUI() {
    prtChoose();
    printf("r R : List all the students of the current class\n");
    printf("a A : Add students' Info\n");
    printf("x X : Del target student(s)[...]\n");
    printf("d D : sort the students DESCENDING[by GPA]\n");
    printf("c C : sort the students ASCENDING[by GPA]\n");
    printf("f F : Query[...]\n");
    printf("s S : Save all the Changes to files\n");
    printf("q   : Back\n");
    printf("Q   : Quit the System\n");
    printf("\n");
}

void prtQueryUI() {
    prtChoose();
    printf("  N : by No\n");
    printf("  n : by name\n");
    printf("g G : by Gender\n");
    printf("\n");
    printf("  0 : by GPA\n");
    printf("  1 : by ProgDesign\n");
    printf("  2 : by pml\n");
    printf("  3 : by Calculus\n");
    printf("  4 : by LinearAlgebra\n");
    printf("  5 : by English\n");
    printf("  6 : by History\n");
    printf("  7 : by PE\n");
    printf("  q : Back\n");
    printf("  Q : Quit the System\n");
    printf("\n");
}

void prtDelUI() {
    prtChoose();
    printf("  N : by No\n");
    printf("  n : by name\n");
    printf("g G : by Gender\n");
    printf("\n");
    printf("  q : Back\n");
    printf("  Q : Quit the System\n");
    printf("\n");
}
