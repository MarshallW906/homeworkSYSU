#include "UIOperations.h"

int OpenClass(const char *className, node *head) {
    char Fname[60];
    sprintf(Fname, "%s.mwa", className);
    FILE *fp;
    if ((fp = fopen(Fname, "r")) == NULL) {
        printf("File Opening Failed.\n");
        printf("Now will Create and enter a New class named {%s}.\n", Fname);
        fp = fopen(Fname, "w");
        fclose(fp);
        printf("Open %s Succeeded.\n\n", Fname);
        return 0;
    }
    printf("Open %s Succeeded.\n\n", Fname);
    if (feof(fp)) return 0;
    Student temp;
    node *p = head, *q = head;
    int count = 0;
    while (!feof(fp)) {
        fscanf(fp, "%d", &temp.No);
        fscanf(fp, "%s", &temp.name);
        fscanf(fp, "%d", &temp.gender);

        fscanf(fp, "%d", &temp.ProgDesign);
        fscanf(fp, "%d", &temp.pml);
        fscanf(fp, "%d", &temp.Calculus);
        fscanf(fp, "%d", &temp.LinearAlgebra);
        fscanf(fp, "%d", &temp.English);
        fscanf(fp, "%d", &temp.History);
        fscanf(fp, "%d", &temp.PE);

        temp.GPA = calcStuGPA(&temp);
        addNode(head, &temp);
        count++;
        p = q;
        q = q->next;
    }
    erase(p);
    fclose(fp);
    return count;
}

int addStudentInfo(node *head) {
    printf("Enter the information in this way : \n");
    printf("[No](no more than 5 bits)[Name][Gender] [ProgDesign][pml][Calculus][LinearAlgebra][English][History][PE]\n");
    printf("Values are split by spaces.\n");
    int quit = 0, count = 0;
    while (!quit) {
        Student temp;
        printf("> ");
        inputStudentInfo(&temp);
        addNode(head, &temp);
        count++;
        char c;
        fflush(stdin);
        do {
            printf("More Student to add ? [y/n] : ");
            c = getchar();
        } while (!((c == 'y') || (c == 'Y') || (c == 'n') || (c == 'N')));
        switch (c) {
            case 'y' :
            case 'Y' :
                quit = 0;
                break;
            case 'n' :
            case 'N' :
                quit = 1;
                break;
        }
    }
    return count;
}

void SaveCHG(const char *className, node *head) {
    char Fname[60];
    sprintf(Fname, "%s.mwa", className);
    FILE *fp;
    if ((fp = fopen(Fname, "w")) == NULL) {
        printf("File Opening Failed. Unknown error.\n");
        return;
    }
    if ((NULL == head) || (NULL == head->next)) {
        printf("{%s} cleared.\n", Fname);
        fclose(fp);
        return;
    }
    node *p, *q;
    p = head->next;
    while (p != NULL) {
        fprintf(fp, "%d ", p->data.No);
        fprintf(fp, "%s ", p->data.name);
        fprintf(fp, "%d ", p->data.gender);

        fprintf(fp, "%d ", p->data.ProgDesign);
        fprintf(fp, "%d ", p->data.pml);
        fprintf(fp, "%d ", p->data.Calculus);
        fprintf(fp, "%d ", p->data.LinearAlgebra);
        fprintf(fp, "%d ", p->data.English);
        fprintf(fp, "%d ", p->data.History);
        fprintf(fp, "%d\n", p->data.PE);

        p = p->next;
    }
    fclose(fp);
}
