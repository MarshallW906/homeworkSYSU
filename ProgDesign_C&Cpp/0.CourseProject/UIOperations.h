/*
    this File consists of the Operations
    which can be easily used & edited & other possible modify
*/

#ifndef UIOperations
#define UIOperations

// void DeleteClass_Whole(const char className[], node *head);
// use remove() from <stdio.h>
// delete target class (and destroy the corresponding list ?)
int OpenClass(const char *className, node *head);
void delClass(const char *className);
// void ExitClass(node *head);
// each operations on the Class won't be saved unless use SaveCHG();
void SaveCHG(const char *className, node *head);
// also must have a module to exit but no need to write a funtions.

// void readClassStu(FILE *fp, node *head);
// void printWholeList(FILE *fp, node *head);

int addStudentInfo(node *head);
// void delStudent(node *head, int No);
// del the first one with the given No.
// void sortClass(node *head);
// sort by GPA, if equal, then by No, ASCENDING.


// BOOL register(const char *username, const char *passwd);
// BOOL delUser(const char *username, const char *supsswd);
// maybe use "system("del xxx")" to simplify the code

#endif  // UIOperations
