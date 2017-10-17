#include <stdio.h>
#include <string.h>

void split(char[] separator, char[] str);
int separatorCmp(char *c, int sptor_length);

int main()
{
    int t,i = 0;
    scanf("%d", &t);
    while (i <= t) {
        char separator[601];
        char str[601];
        scanf("%s", separator);
            scanf("%s", str);
        split(separator, str);
        i++;
    }
}

void split(char [] separator, char[] str) {
    int j = 0;
    do {
        
    }
}