#include <stdio.h>

int main() {
int num[10000];
int n;
int i, j, temp;
int m, k, p, q, o;
int result[2000];

scanf("%d", &n);

for(i = 0; i < n; i++) {
scanf("%d", &num[i]);
}

for(i = 0; i <= n; i++) {
for(j = 0; i + j < n; j++) {
  if(num[j] > num[j + 1]) {
temp = num[j];
num[j + 1] = num[j];
num[j] = temp;
  }
}
}

for(i = 0; i < n - 1; i++) {
printf("%d ", num[i]);
}
printf("%d\n", num[i]);

return 0;
}
