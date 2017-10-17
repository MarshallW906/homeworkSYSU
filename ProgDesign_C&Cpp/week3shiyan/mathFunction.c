/*Copyright 2015 MarshallRna Wang*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

int main() {
    double i_pow, j_tri6, k_sqrt_exp, l_log, m, n = 1, duration;
    clock_t time_start, time_end;
    time_start = clock();
    int color;
    printf("Enter a number to choose the basic font color\n");
    scanf("%d", &color);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    int i;
    for (i = 0; i < 10000000; ++i) {
        n = sin(cos(n));
    }
    i_pow = pow(5.26, 19);
    j_tri6 = tan(sin(cos(1.526)+tanh(1.420))+cosh(0.96+sinh(0.526)));
    k_sqrt_exp = sqrt(exp(5.26420));
    l_log = log(log10(5.26));
    m = i_pow * j_tri6 * k_sqrt_exp * tan(k_sqrt_exp) * l_log;
    printf("i_pow = %f\n", i_pow);
    printf("j_tri6 = %f\n", j_tri6);
    printf("k_sqrt_exp = %f\n", k_sqrt_exp);
    printf("l_log = %f\n", l_log);
    printf("m = %f\n", m);
    printf("n = %f\n", n);
    time_end = clock();
    duration = (double)(time_end - time_start) / CLOCKS_PER_SEC;
    printf("%f miliseconds\n%f seconds\n",
     (double)(time_end - time_start), duration);
    return 0;
}

