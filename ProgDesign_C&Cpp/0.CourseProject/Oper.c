/*
    this is the function list of the opertions of
    student management.

    the elementary operations of List
    is in StuList.h & StuList.c
*/
#include "Oper.h"

void printStu_One(node *current) {
    printf("%5d|%20s|%6d|%4d|%3d|%4d|%7d|%3d|%4d|%3d|%1.3lf\n",
           current->data.No, current->data.name,
           current->data.gender, current->data.ProgDesign,
           current->data.pml, current->data.Calculus,
           current->data.LinearAlgebra,
           current->data.English, current->data.History,
           current->data.PE, current->data.GPA);
}

void inputStudentInfo(Student *current) {
    fflush(stdin);
    inputStuNo(current);
    inputStuName(current);
    inputStuGender(current);

    inputStu_Prog(current);
    inputStu_pml(current);
    inputStu_Calculus(current);
    inputStu_LinearA(current);
    inputStu_Eng(current);
    inputStu_Hist(current);
    inputStu_PE(current);

    current->GPA = calcStuGPA(current);
}

double calcStuGPA(Student *current) {
    double prog, pml, Calc, LA, eng, hist, pe;
    prog = (getStu_Prog(current) - 50) / 10.0;
    pml = (getStu_pml(current) - 50) / 10.0;
    Calc = (getStu_Calculus(current) - 50) / 10.0;
    LA = (getStu_LinearA(current) - 50) / 10.0;
    eng = (getStu_Eng(current) - 50) / 10.0;
    hist = (getStu_Hist(current) - 50) / 10.0;
    pe = (getStu_PE(current) - 50) / 10.0;

    double gpa = (prog * 3 + pml * 2 + Calc * 5 + LA * 2 + eng * 3 + hist * 2
                  + pe * 1) / 18.0;
    return gpa;
}

void inputStuNo(Student *current) {
    scanf("%d", &(current->No));
}
void inputStuName(Student *current) {
    scanf("%s", current->name);
}
void inputStuGender(Student *current) {
    scanf("%d", &(current->gender));
}
void inputStu_Prog(Student *current) {
    scanf("%d", &(current->ProgDesign));
}
void inputStu_pml(Student *current) {
    scanf("%d", &(current->pml));
}
void inputStu_Calculus(Student *current) {
    scanf("%d", &(current->Calculus));
}
void inputStu_LinearA(Student *current) {
    scanf("%d", &(current->LinearAlgebra));
}
void inputStu_Eng(Student *current) {
    scanf("%d", &(current->English));
}
void inputStu_Hist(Student *current) {
    scanf("%d", &(current->History));
}
void inputStu_PE(Student *current) {
    scanf("%d", &(current->PE));
}

// if (BOOL)needPrint == 1, then
//    functions here all Output the results IMMEDIATELY when find one results.
// else it will just count the number of elements
//                                      according with the requirements.
// if any elements was found,
//    each function will return the number of elements found
// otherwise(no elements was found), it will return 0.

int queryByNo(node *head, int quNo, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_No(&rep->data);
        if (tmp == quNo) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
// will use strcpy() so <string.h> is needed.
int queryByGender(node *head, int quGender, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_No(&rep->data);
        if (tmp == quGender) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByName(node *head, const char *quName, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int count = 0;
    while (rep != NULL) {
        if (strcmp(quName, getStu_Name(&rep->data)) == 0) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
// will use strcpy() so <string.h> is needed.

// query for Remarks will proceed in ways like "region(lo..hi)"
// specially, when query for a CERTAIN Val, just let lo = hi.
int queryByScore_Prog(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_Prog(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByScore_pml(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_pml(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByScore_Calculus(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_Calculus(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByScore_LinearA(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_LinearA(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByScore_Eng(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_Eng(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByScore_Hist(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_Hist(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}
int queryByScore_PE(node *head, int valfloor, int valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int tmp, count = 0;
    while (rep != NULL) {
        tmp = getStu_PE(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}

int queryByScore_GPA(node *head, double valfloor, double valceiling, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))
        return 0;
    node *rep = head->next->next;
    int count = 0;
    double tmp;
    while (rep != NULL) {
        tmp = getStu_GPA(&rep->data);
        if (tmp >= valfloor && tmp <= valceiling) {
            count++;
            if (needPrint) printStu_One(rep);
        }
        rep = rep->next;
    }
    return count;
}

int queryAll(node *head, BOOL needPrint) {
    if ((NULL == head) || (NULL == head->next))
        return 0;
    node *rep = head->next;
    int count = 0;
    while (rep != NULL) {
        count++;
        if (needPrint) printStu_One(rep);
        rep = rep->next;
    }
    return count;
}


int getStu_No(Student *current) {
    return current->No;
}
char* getStu_Name(Student *current) {
    return current->name;
}
int getStu_Gender(Student *current) {
    return current->gender;
}

int getStu_Prog(Student *current) {
    return current->ProgDesign;
}
int getStu_pml(Student *current) {
    return current->pml;
}
int getStu_Calculus(Student *current) {
    return current->Calculus;
}
int getStu_LinearA(Student *current) {
    return current->LinearAlgebra;
}
int getStu_Eng(Student *current) {
    return current->English;
}
int getStu_Hist(Student *current) {
    return current->History;
}
int getStu_PE(Student *current) {
    return current->PE;
}

double getStu_GPA(Student *current) {
    return current->GPA;
}



int DelByNo(node *head, int quNo) {
    if ((NULL == head) || (NULL == head->next))
        return 0;
    node *rep, *req;
    rep = head;
    req = head->next;
    int tmp, count = 0;
    while (req != NULL) {
        tmp = getStu_No(&req->data);
        if (tmp == quNo) {
            count++;
            erase(rep);
        }
        rep = req;
        req = req->next;
    }
    return count;
}
// will use strcpy() so <string.h> is needed.
int DelByGender(node *head, int quGender) {
    if ((NULL == head) || (NULL == head->next))
        return 0;
    node *rep, *req;
    rep = head;
    req = head->next;
    int count = 0;
    int tmp;
    while (req != NULL) {
        tmp = getStu_Gender(&req->data);
        if (tmp == quGender) {
            count++;
            erase(rep);
        }
        rep = req;
        req = req->next;
    }
    return count;
}
int DelByName(node *head, const char *quName) {
    if ((NULL == head) || (NULL == head->next))
        return 0;
    node *rep, *req;
    rep = head;
    req = head->next;
    int count = 0;
    char *tmp;
    while (req != NULL) {
        tmp = getStu_Name(&req->data);
        if (strcmp(quName, tmp) == 0) {
            count++;
            erase(rep);
        }
        rep = req;
        req = req->next;
    }
    return count;
}
// will use strcpy() so <string.h> is needed.

int DelAll(node *head, BOOL needPrint) {
    int count = queryAll(head, 0);
    destroyList(head);
    return count;
}
