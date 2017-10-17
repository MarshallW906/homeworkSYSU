#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

void insert(node *p, int val) {
    node *t = malloc(sizeof(node));
    t -> data = val;
    t -> next = p -> next;
    p -> next = t;
}
int main() {
    int n, x, y, i;
    scanf("%d%d%d", &n, &x, &y);
    node *head = malloc(sizeof(node)), *q;
    head -> data = 0;
    q = head;
    for (i = 1; i < n; i++) {
        insert(head, i);

    }

}
