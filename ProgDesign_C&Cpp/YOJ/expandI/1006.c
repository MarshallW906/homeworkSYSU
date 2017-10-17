#include <stdio.h>
#include <string.h>

int main() {
    char str[81];
    scanf("%s", str);
    int i, length = strlen(str);
    for (i = 0; i < length; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = 'a' + 'z' - str[i];
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = 'A' + 'Z' - str[i];
    }
    printf("%s\n", str);
    return 0;
}
