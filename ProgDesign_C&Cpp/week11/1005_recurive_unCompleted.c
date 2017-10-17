#include <stdio.h>

int judgenum(char c) {
    return c >= 48 && c <= 57;
}
int judgeOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
int getnum(char *e, int *num) {
    *num = 0;
    int m = 0;
    while (judgenum(*e)) {
        *num *= 10;
        *num += *e - 48;
        e++;
        m++;
    }
    return m;
}
int calc(char *expr) {
    if (*expr == '(') {
        calc(*expr + 1);
    }
    int num1 = 0, num2 = 0;

    if (judgenum(*expr)) {
        expr += getnum(*expr, &num1);
    }
    if (*expr == '-') {
        if (judgenum(*expr + 1))
            expr += getnum(*expr + 1, &num1) + 1;
        num1 *= -1;
    }

    if (judgeOp(*expr)) {
        if (!judgenum(*expr))
            switch (*expr) {
                case '+' : {
                        return num1 + num2;
                        break;
                    }
                case '-' : {
                        return num1 - num2;
                        break;
                    }
                case '*' : {
                        return num1 * num2;
                        break;
                    }
                case '/' : {
                        return num1 / num2;
                        break;
                    }
            }
    }
}
