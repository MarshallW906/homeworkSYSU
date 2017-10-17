#include "myString.h"
#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef MAX_INT
#define MAX_INT ((int)2147483647)
#endif // MAX_INT

#ifndef MIN_INT
#define MIN_INT ((int)-2147483648)
#endif // MIN_INT

unsigned int myStrlen(const char s[]) {
    if (s == NULL) return 0;
    unsigned int i = 0;
    while (s[i++] != '\0');
    return --i;
}

char * myStrcpy(char destination[], const char source[]) {
    char *r = destination;
    if (!(destination != NULL && source != NULL))
        return (char *)NULL;
    return r;
}

char * myStrcat(char destination[], const char source[]) {
    char *r = destination;
    if (!(destination != NULL && source != NULL))
        return (char *)NULL;
    while (*destination++ != '\0');
    destination--;
    while ((*destination++ = *source++) != '\0');
    return r;
}

int myStrcmp(const char str1[], const char str2[]) {
    if (!(str1 != NULL && str2 != NULL))
        return 0;
    while (*str1 == *str2) {
        if (*str1 == '\0')
            return 0;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int MyStrfind(const char str1[], const char str2[]) {
    if (!(str1 != NULL && str2 != NULL))
        return 0;
    int len1 = myStrlen(str1), len2 = myStrlen(str2), i = 0, j;
    while (i + len2 <= len1) {
        j = 0;
        while (*(str1 + i + j) == *(str2 + j)) j++;
        if (j == len2) return i;
        ++i;
    }
    return -1;
}

void LeftRotateString(char *buff, int n) {
    if (buff == NULL) return;
    char temp[n];
    int i, length = myStrlen(buff);
    n %= length;
    for (i = 0; i < n; i++)
        *(temp + i) = *(buff + i);
    while (*(buff + n) != '\0') {
        *buff = *(buff + n);
        buff++;
    }
    for (i = 0; i < n; i++)
        *(buff + i) = *(temp + i);
}

int myParseInt(const char str[]) {
    if (str == NULL) return 0;
    const char *s = str;
    long long sum = 0;
    int i = 0, flag = 1;
    if (str[i] == '-') {
        flag = -1;
        i++;
    } else if (str[i] == '+') {
        flag = 1;
        i++;
    }
    do {
        if (!(str[i] >= '0' && str[i] <= '9')) return sum;
        sum *= 10;
        sum += str[i] - 48;
    } while (str[++i] != '\0');
    sum *= flag;
    if (sum < MIN_INT) return MIN_INT;
    if (sum > MAX_INT) return MAX_INT;
    return sum;
}

int myStrcontain(const char str1[], const char str2[]) {
    if (!(str1 != NULL && str2 != NULL))
        return 0;
    const char *s1 = str1, *s2 = str2;
    while (*s2 != '\0') {
        s1 = str1;
        while (*s1 != *s2 && *s1 != '\0') s1++;
        if (*s1 == '\0') return 0;
        s2++;
    }
    return 1;
}
