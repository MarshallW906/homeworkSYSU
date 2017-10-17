#include "StuList.h"

node* CreateList() {
    node *head = (node *)malloc(sizeof(node));
    memset(head, 0, sizeof(node));
    head->next = NULL;
    return head;
}

void insert(node *p, Student *val) {
    node *new = (node *)malloc(sizeof(node));
    new->data = *val;
    new->next = p->next;
    p->next = new;
}

void erase(node *p) {
    node *toDel = p->next;
    p->next = toDel->next;
    free(toDel);
}

void addNode(node *head, Student *val) {
    if (head == NULL) {
        return;
    }
    node *p = head, *q = head->next;
    while (q != NULL) {
        p = q;
        q = q->next;
    }
    insert(p, val);
    p->next->next = NULL;
}


void destroyList(node *head) {
    if (NULL == head) return;
    if (NULL == head->next) {
        free(head);
        head = NULL;
        return;
    }
    node *p = head->next;
    while (NULL != p) {
        node *tmp = p;
        p = p->next;
        free(tmp);
    }
    free(head);
    head = NULL;  // is it of practical use?
    // will it actually change the real pointer head?
}

void bubbleSortDES(node *head) {
    int len = 0, i, j;
    node *p;
    for (p = head; p != NULL; p = p->next) len++;

    for (i = 1; i < len - 1; i++) {
        p = head->next;
        for (j = 0; j < len - i - 1; j++, p = p->next)
            if (p->data.GPA < p->next->data.GPA) {
                Student tem = p->data;
                p->data = p->next->data;
                p->next->data = tem;
            }
    }
}

void bubbleSortASC(node *head) {
    int len = 0, i, j;
    node *p;
    for (p = head; p != NULL; p = p->next) len++;

    for (i = 1; i < len - 1; i++) {
        p = head->next;
        for (j = 0; j < len - i - 1; j++, p = p->next)
            if (p->data.GPA > p->next->data.GPA) {
                Student tem = p->data;
                p->data = p->next->data;
                p->next->data = tem;
            }
    }
}
