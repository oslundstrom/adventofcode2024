#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 1000

int comp(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int main() {
  int a[MAXLINES], b[MAXLINES];
  int i = 0, n = 0;
  char *line = NULL;
  size_t size = 0;
  ssize_t chars_read;

  while (getline(&line, &size, stdin) > 0) {
    sscanf(line, "%d %d", a+i, b+i);
    i++;
  }

  qsort(a, sizeof(a), sizeof(a[0]), comp);

  // Print the two arrays
  for (n = 0; n < i; n++)
    printf("%d,", a[n]);
  printf("\n");

  for (n = 0; n < i; n++)
    printf("%d,", b[n]);
  printf("\n");

  return 0;
}
