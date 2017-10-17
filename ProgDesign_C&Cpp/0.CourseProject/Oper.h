/*
    this is the function list of the opertions of
    student management.

    the elementary operations of List
    is in StuList.h & StuList.c
*/

typedef unsigned short int BOOL;

#ifndef serviceOperations
#define serviceOperations

void printStu_One(node *current);

#ifndef inputOpertions
#define inputOpertions
void inputStudentInfo(Student *current);

void inputStuNo(Student *current);
void inputStuName(Student *current);
void inputStuGender(Student *current);
void inputStu_Prog(Student *current);
void inputStu_pml(Student *current);
void inputStu_Calculus(Student *current);
void inputStu_LinearA(Student *current);
void inputStu_Eng(Student *current);
void inputStu_Hist(Student *current);
void inputStu_PE(Student *current);

double calcStuGPA(Student *current);
#endif  // inputOpertions

#ifndef QueryOperations
#define QueryOperations
// if (BOOL)needPrint == 1, then
//    functions here all Output the results IMMEDIATELY when find one results.
// else it will just count the number of elements
//                                      according with the requirements.
// if any elements was found,
//    each function will return the number of elements found
// otherwise(no elements was found), it will return 0.

int queryByNo(node *head, int quNo, BOOL needPrint);
// will use strcpy() so <string.h> is needed.
int queryByGender(node *head, int quGender, BOOL needPrint);
int queryByName(node *head, const char *quName, BOOL needPrint);
// will use strcpy() so <string.h> is needed.

// query for Remarks will proceed in ways like "region(lo..hi)"
// specially, when query for a CERTAIN Val, just let lo = hi.
int queryByScore_Prog(node *head, int valfloor, int valceiling, BOOL needPrint);
int queryByScore_pml(node *head, int valfloor, int valceiling, BOOL needPrint);
int queryByScore_Calculus(node *head, int valfloor, int valceiling, BOOL needPrint);
int queryByScore_LinearA(node *head, int valfloor, int valceiling, BOOL needPrint);
int queryByScore_Eng(node *head, int valfloor, int valceiling, BOOL needPrint);
int queryByScore_Hist(node *head, int valfloor, int valceiling, BOOL needPrint);
int queryByScore_PE(node *head, int valfloor, int valceiling, BOOL needPrint);

int queryByScore_GPA(node *head, double valfloor, double valceiling, BOOL needPrint);

int queryAll(node *head, BOOL needPrint);
#endif  // QueryOperations

#ifndef getValOpertions
#define getValOpertions
// just rewrite the elementary RW sentences
int getStu_No(Student *current);
char* getStu_Name(Student *current);
int getStu_Gender(Student *current);

int getStu_Prog(Student *current);
int getStu_pml(Student *current);
int getStu_Calculus(Student *current);
int getStu_LinearA(Student *current);
int getStu_Eng(Student *current);
int getStu_Hist(Student *current);
int getStu_PE(Student *current);

double getStu_GPA(Student *current);
#endif  // getValOpertions

#ifndef DelOperations
#define DelOperations
// if any elements was found,
//    each function will return the number of elements found
// otherwise(no elements was found), it will return 0.

int DelByNo(node *head, int quNo);
int DelByGender(node *head, int quGender);
int DelByName(node *head, const char *quName);
// will use strcpy() so <string.h> is needed.

int DelAll(node *head, BOOL needPrint);
#endif  // QueryOperations

#endif  // serviceOperations
