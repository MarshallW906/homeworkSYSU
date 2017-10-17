#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UIshell.c"
#include "Stulist.c"
#include "Oper.c"
#include "UIOperations.c"


void MainUI_Teacher(node *list);
void SubUI_Class(node *list, const char *className, int NumberOfStu);
void SubUI_Query(node *list);
void SubUI_Del(node *list);

int main(int argc, char const *argv[]) {
    node *list = CreateList();
    cls();
    prtLine();
    prtWelcome();
    MainUI_Teacher(list);
    if (NULL != list) destroyList(list);
    return 0;
}

void MainUI_Teacher(node *list) {
    BOOL QuitMain = 0;
    int NumberOfStu;
    char className[33];
    while (!QuitMain) {
        prtMainUIforTeacher();
        fflush(stdin);
        prtLstart();
        char cMain = getchar();
        switch (cMain) {
            case 'e' :
            case 'E' :
                //if (NULL != list) destroyList(list);
                list = CreateList();
                printf("Enter the class's name : ");
                scanf("%s", className);
                NumberOfStu = OpenClass(className, list);  // Open an Class
                SubUI_Class(list, className, NumberOfStu);
                break;
            case 'q' :
            case 'Q' :
                QuitMain = 1;  // Quit
                break;
            default :
                break;
        }
    }
}

void SubUI_Class(node *list, const char *className, int NumberOfStu) {
    BOOL QuitClass = 0;
    while (!QuitClass) {
        prtClassSubUI();
        prtLstart();
        fflush(stdin);
        char cClass = getchar();
        switch (cClass) {
            case 'r' :
            case 'R' :
                prtFrame();
                NumberOfStu = queryAll(list, 1);
                printf("%d students in total\n", NumberOfStu);
                ;  // List all the Stu
                break;
            case 'a' :
            case 'A' :
                addStudentInfo(list);
                ;  // Add students' info
                break;
            case 'x' :
            case 'X' :
                SubUI_Del(list);
                ;  // Del student(s)
                break;
            case 'd' :
            case 'D' :
                bubbleSortDES(list);
                ;  // sort DESCENDING
                break;
            case 'c' :
            case 'C' :
                bubbleSortASC(list);
                ;  // sort ASCENDING
                break;
            case 'f' :
            case 'F' :
                SubUI_Query(list);
                ;  // Query
                break;
            case 's' :
            case 'S' :
                SaveCHG(className, list);
                ;  // Save chgs
                break;
            case 'q' :
                QuitClass = 1;  // Back
                break;
            case 'Q' :
                if (NULL != list) destroyList(list);
                exit(0);
                ;  // Quit the system
                break;
        }
    }
}

void SubUI_Query(node *list) {
    BOOL QuitQuery = 0;
    int numberOfQuery;
    double varfloor, varceiling;

    while (!QuitQuery) {
        prtQueryUI();
        fflush(stdin);
        prtLstart();
        char cQuery = getchar();
        switch (cQuery) {
            case 'N' :
                printf("Enter the query No : ");
                prtLstart();
                int quNo;
                scanf("%d", &quNo);
                prtFrame();
                numberOfQuery = queryByNo(list, quNo, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // No
                break;
            case 'n' :
                printf("Enter the query name : ");
                prtLstart();
                char quName[20];
                scanf("%s", quName);
                prtFrame();
                numberOfQuery = queryByName(list, quName, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // name
                break;
            case 'g' :
            case 'G' :
                printf("Enter the query Gender : MALE-1, FEMALE-2\n");
                prtLstart();
                int quGender;
                scanf("%d", &quGender);
                prtFrame();
                numberOfQuery = queryByGender(list, quGender, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // Gender
                break;
            case '0' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_GPA(list, varfloor, varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // GPA
                break;
            case '1' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_Prog(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // ProgDesign
                break;
            case '2' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_pml(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // pml
                break;
            case '3' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_Calculus(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // Calculus
                break;
            case '4' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_LinearA(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // LinearAlgebra
                break;
            case '5' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_Eng(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // English
                break;
            case '6' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_Hist(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // History
                break;
            case '7' :
                printf("Enter the floor and the ceiling value, split by a space\n");
                scanf("%lf%lf", &varfloor, &varceiling);
                prtFrame();
                numberOfQuery = queryByScore_PE(list, (int)varfloor, (int)varceiling, 1);
                printf("%d students displayed.\n", numberOfQuery);
                QuitQuery = 1;
                ;  // PE
                break;
            case 'q' :
                QuitQuery = 1;  //  back
                break;
            case 'Q' :
                if (NULL != list) destroyList(list);
                exit(0);
                ;  // Quit the systme
                break;
        }
    }
}

void SubUI_Del(node *list) {
    BOOL QuitDel = 0;
    int numberOfDelete;
    int quNo, quGender;
    char quName[21];
    while (!QuitDel) {
        prtDelUI();
        prtLstart();
        fflush(stdin);
        char cDel = getchar();
        switch (cDel) {
            case 'N' :
                printf("Enter the No of target Student to delete :\n");
                prtLstart();
                scanf("%d", &quNo);
                numberOfDelete = DelByNo(list, quNo);
                printf("%d students deleted.\n", numberOfDelete);
                QuitDel = 1;
                ;  // No
                break;
            case 'n' :
                printf("Enter the Name of target Student to delete :\n");
                prtLstart();
                scanf("%s", quName);
                numberOfDelete = DelByName(list, quName);
                printf("%d students deleted.\n", numberOfDelete);
                QuitDel = 1;
                ;  // name
                break;
            case 'g' :
            case 'G' :
                printf("Enter the Gender of target Student to delete :\n");
                printf("MALE--1, FEMALE--2,(OR other useless value.. : ");
                prtLstart();
                scanf("%d", &quGender);
                numberOfDelete = DelByGender(list, quGender);
                printf("%d students deleted.\n", numberOfDelete);
                ;  // Gender
                break;
            case 'q' :
                QuitDel = 1;  //  back
                break;
            case 'Q' :
                if (NULL != list) destroyList(list);
                exit(0);
                ;  // Quit the systme
                break;
        }
    }
}
