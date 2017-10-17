#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int data[1000];
    int top;
} StackNum;
void Numpush(StackNum *s, int val) {
    s->data[s->top++] = val;
}
int Numpop(StackNum *s) {
    return s->data[--s->top];
}

typedef struct {
    char data[1000];
    int top;
} StackOp;
void Oppush(StackOp *s, int ops) {
    s->data[s->top++] = ops;
}
char Oppop(StackOp *s) {
    return s->data[--s->top];
}

int calc(char *s);
void trans(char *s);
int calcc(char *src);
int judgeam(char c);
int judgemd(char c);
int judgesloc(char c);
int judgeNum(char c);
int getnum(char *e, int *num);
char s[200], m[200];

int main() {
    int ans = 0;
    while (~scanf("%s", s)) {
        printf("the initial exp is %s\n", s);
        ans = calc(s);
        printf("ans : %d\n", ans);
    }
    return 0;
}

int calc(char *s) {
    trans(s);
    int ans = calcc(m);
    return ans;
}

void trans(char *s) {
    StackNum *s1 = (StackNum *)malloc(sizeof(StackNum));
    StackNum *s2 = (StackNum *)malloc(sizeof(StackNum));
    memset(s1, 0, sizeof(StackNum));
    memset(s2, 0, sizeof(StackNum));
    int i = 0;
    char ch;
    while ((ch = s[i]) != '\0') {
        int num;
        if (judgeNum(ch)) {
            i += getnum(s + i, &num);
            Numpush(s2, num);
            continue;
        } else if (ch == '-' && judgeNum(s[i + 1]) && s[i - 1] == '(') {
            i += getnum(s + i + 1, &num) + 1;
            Numpush(s2, num * -1);
            continue;
        } else if (judgeam(ch) || judgemd(ch)) {
            while (1) {
                if (s1->top == 0 || s1->data[s1->top - 1] == '(') {
                    Numpush(s1, ch);
                    break;
                } else if (judgemd(ch) && judgeam(s1->data[s1->top - 1])) {
                    Numpush(s1, ch);
                    break;
                } else {
                    Numpush(s2, Numpop(s1));
                }

            }
        } else if (judgesloc(ch)) {
            if (ch == '(') {
                Numpush(s1, ch);
            }
            if (ch == ')') {
                char cc;
                while (s1->data[(s1->top) - 1] != '(') {
                    cc = Numpop(s1);
                    Numpush(s2, cc);
                }
                Numpop(s1);
            }
        }
        i++;
    }
    while (s1->top != 0) {
        Numpush(s2, Numpop(s1));
    }
    for (i = s2->top - 1; i >= 0; --i)
        m[i] = Numpop(s2);
}

int calcc(char *m) {
    StackNum *num = (StackNum *)malloc(sizeof(StackNum));
    while (*m != '\0') {
        if (judgeam(*m) || judgemd(*m)) {
            int a, b;
            if (*m == '+') {
                a = Numpop(num);
                b = Numpop(num);
                Numpush(num, a + b);
            }
            if (*m == '-') {
                a = Numpop(num);
                b = Numpop(num);
                Numpush(num, a - b);
            }
            if (*m == '*') {
                a = Numpop(num);
                b = Numpop(num);
                Numpush(num, a * b);
            }
            if (*m == '/') {
                a = Numpop(num);
                b = Numpop(num);
                Numpush(num, a / b);
            }
        } else Numpush(num, *m);
        m++;
    }
    return Numpop(num);
}

int judgeam(char c) {
    return c == '+' || c == '-';
}
int judgemd(char c) {
    return c == '*' || c == '/';
}
int judgesloc(char c) {
    return c == '(' || c == ')';
}
int judgeNum(char c) {
    return c >= 48 && c <= 57;
}

int getnum(char *e, int *num) {
    *num = 0;
    int m = 0;
    while (judgeNum(*e)) {
        *num *= 10;
        *num += *e - 48;
        e++;
        m++;
    }
    return m;
}
