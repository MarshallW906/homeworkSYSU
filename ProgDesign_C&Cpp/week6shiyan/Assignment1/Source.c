/*Copyright 2015 MarshallRna Wang */
#include <stdio.h>
#include <string.h>

typedef struct {
    char t_id[21];
    char t_salary[21];
    char t_height[21];
} Employee;

void exch(Employee ems[], int i, int j);
void Emsort(Employee ems[], int length);

int main() {
    int total_test, e_num, current_deal, j;
    int current_test = 1, current_e;
    char idforsrch[21];
    scanf("%d", &total_test);
    do {
        scanf("%d", &e_num);
        Employee ems[e_num];
        for (current_e = 0; current_e < e_num; current_e++)
            scanf("%s%s%s", ems[current_e].t_id,
                ems[current_e].t_salary, ems[current_e].t_height);
        Emsort(ems, e_num);

        scanf("%s", idforsrch);
        for (current_deal = 0; current_deal <= e_num; current_deal++) {
            if (strcmp(idforsrch, ems[current_deal].t_id) == 0) {
                int potential_boss = current_deal + 1, current_subordinates = 0;
                while (strcmp(ems[current_deal].t_height, ems[potential_boss].t_height) > 0)
                    potential_boss++;
                for (j = 0; j < current_deal; j++)
                    if (strcmp(ems[current_deal].t_height, ems[j].t_height) > 0)
                        current_subordinates++;
                printf("(%s,%d)\n",
                    (current_deal != e_num - 1) ? ems[potential_boss].t_id : "0", current_subordinates);
            }
        }
        current_test++;
    } while (current_test <= total_test);
    return 0;
}

void Emsort(Employee ems[], int num) {
    int i, j;
    for (i = 0; i < num - 1; i++)
        for (j = 0; j < num - i - 1; j++)
            if (strcmp(ems[j].t_salary, ems[j + 1].t_salary) > 0)
                exch(ems, j, j + 1);
}

void exch(Employee ems[], int i, int j) {
    Employee t;
    t = ems[i];
    ems[i] = ems[j];
    ems[j] = t;
}
