/*
    need the following including :
        #include <stdlib.h>
        #include <string.h>
*/


typedef struct stud {
    int No;  // remember to printf as Format: %5d
    char name[20];
    int gender;
    int ProgDesign;
    int pml;
    int Calculus;
    int LinearAlgebra;
    int English;
    int History;
    int PE;
    double GPA;
} Student;

typedef struct Node {
    Student data;
    struct Node *next;
} node;

#ifndef StudentListOperatiosn
#define StudentListOperation

node* CreateList();
void insert(node *p, Student *val);
void erase(node *p);
void addNode(node *head, Student *val);
node* getNodeByindex(node *head, int index);
// with this you can regard the list as an array
void destroyList(node *head);
void bubbleSortDES(node *head);
void bubbleSortASC(node *head);
void sortList(node *head, int lo, int hi, int mode);
// sort [lo..hi] from Low to High
// mode == 1 : ASCENDING
// mode == 2 : DESCENDING

#endif  // StudentListOperation
