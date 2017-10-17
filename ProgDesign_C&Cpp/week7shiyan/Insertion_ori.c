#include <stdio.h>

int main() {
  int num[10000];
  int n;
  int i, j, temp;
  scanf("%d", &n);
  for(i = 0; i < n; i++) {
  scanf("%d", &num[i]);}
  for(i=1; i<n; i++){
  temp = num[i];
  for(j=i-1; j>-1&&num[j]>temp;j--) {
  num[i]=num[j]; num[j]=temp;}}
  for(i = 0; i < n - 1; i++) {
  printf("%d ", num[i]);}
  printf("%d\n", num[i]);
  return 0;
}
