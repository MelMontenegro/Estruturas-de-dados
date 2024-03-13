#include <stdio.h>
 //!showArray(v, cursors=[j])
int main () {
int n, j, x, i;
scanf("%d, &n");
int v[n + 1];
for (j = 0; j < n; j ++) {
    scanf ("%d", &v[j]);
}
printf("Informe um numero\n");
scanf("%d", &x);
for (j = i - 1; j >= 0 && x < v[j]; j--) {
    v[j + 1] = v[j];
 }
 v[j + 1] = x;
 for (j = 0; j < n + 1; j++); {
    printf("%d", v[j]);
 }
}