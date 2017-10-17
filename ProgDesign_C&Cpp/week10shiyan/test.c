#include <stdio.h>
#include "myStringCWB.c"

int main() {
    char s1[20] = "abcdefg";
    char s2[20] = "abc";
    char sfind[20] = "cde";
    char intnum[20] = "-520526";
    printf("Strlen Test : %d\n", myStrlen(s1));
    printf("StrCmp Test 1 : %d\n", myStrcmp(s1, s2));
    printf("Strcat Test : %s\n", myStrcat(s1, s2));
    printf("StrCmp Test 2 : %d\n", myStrcmp(s2, s1));
    printf("StrFind Test : %d\n", MyStrfind(s1, sfind));
    LeftRotateString(s1, 5);
    printf("LeftRotateString Test : %s\n", s1);
    printf("Parse Int Test : %d\n", myParseInt(intnum));
    printf("Contain Test : %d %d\n", myStrcontain(s1, s2), myStrcontain(s1, intnum));
    return 0;
}
