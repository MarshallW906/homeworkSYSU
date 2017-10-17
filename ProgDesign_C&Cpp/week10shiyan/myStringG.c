#include "myString.h"
#ifndef NULL
#define NULL 0
#endif // NULL

unsigned int myStrlen(const char s[]) {
  if (s == NULL) return 0;
  unsigned i = 0;
  while (s[i]) {
    i++;
  }
  return i;
}

char * myStrcpy(char destination[], const char source[]) {
  unsigned i = 0;
  while (source[i]) {
    destination[i] = source[i];
    i++;
  }
  destination[i] = source[i];
  return destination;
}

char * myStrcat(char destination[], const char source[]) {
  unsigned i = 0, len = myStrlen(destination);
  while (source[i]) {
    destination[i + len] = source[i];
    i++;
  }
  destination[i + len] = source[i];
  return destination;
}

int myStrcmp(const char str1[], const char str2[]) {
  unsigned i = 0;
  while (str1[i] || str2[i]) {
    if (str1[i] > str2[i]) return 1;
    else if (str2[i] > str1[i]) return -1;
    i++;
  }
  return 0;
}

int MyStrfind(const char str1[], const char str2[]) {
  unsigned i = 0, j;
  while (str1[i]) {
    j = 0;
    while (1) {
      if (str2[j] == 0) {
        return i;
      }
      if (str1[i + j] != str2[j]) {
        break;
      }
      j++;
    }
    i++;
  }
  return -1;
}

void LeftRotateString(char *buff, int n) {
  if (buff == NULL) return;
  unsigned len = myStrlen(buff), j;
  int i;
  for (i = 0; i < n; i++) {
    buff[len] = buff[0];
    for (j = 0; j < len; j++) {
      buff[j] = buff[j + 1];
    }
  }
  buff[len] = '\0';
}

int myParseInt(const char str[]) {
  char temp[21], isneg;
  unsigned len = myStrlen(str), i = 0, j = 0, k, bit;
  long long sum = 0;
  if (str[0] == '-') {
    isneg = 1;
    i++;
  } else if (str[0] == '+') {
    isneg = 0;
    i++;
  } else isneg = 0;
  while (i < len) {
    if (str[i] >= '0'&&str[i] <= '9') {
      temp[j] = str[i] - '0';
      j++;
    } else break;
    i++;
  }
  for (i = 0; i < j; i++) {
    bit = temp[i];
    for (k = 1; k < j - i; k++) {
      bit *= 10;
    }
    sum += bit;
  }
  if (isneg) sum = -sum;
  if (sum > (long long)2147483647) return 2147483647;
  if (sum < -(long long)2147483648) return -2147483648;
  return (int)sum;
}

int myStrcontain(const char str1[], const char str2[]) {
  unsigned len1 = myStrlen(str1), len2 = myStrlen(str2), i, j;
  char contained;
  for (i = 0; i < len2; i++) {
    contained = 0;
    for (j = 0; j < len1; j++) {
      if (str1[j] == str2[i]) {
        contained = 1;
        break;
      }
    }
    if (!contained) return 0;
  }
  return 1;
}
