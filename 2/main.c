#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1000
#define MAXLENGHT 100

int main() {
  int len, nlines;
  char *reportlines[MAXLINES];
  char *p, *line = NULL;
  size_t size = 100;

  nlines = 0;
  while (len = getline(&line, &size, stdin) > 0) {
    if (nlines >= MAXLINES || (p = malloc(len)) == NULL) {
      printf("error: input too big!\n");
      return 1;
    } else {
      // printf("Saving line %s\n", line);
      strcpy(p, line);
      reportlines[nlines++] = p;
    }
  }
  // printf("Consumed all input\n");
  // printf("Lines: %d\n", nlines);
  // printf("Last line: %s\n", line);

  int report[MAXLINES][100], level = 0;
  // Print the array
  for (int n = 0; n < nlines; n++) {
    for (char character = *reportlines[n]; character != '\0'; character = *++reportlines[n]) {
      switch (character) {
        case ' ': case '\n'
          continue;
        default:
          report[n][level++] = (int)character;
      }
      printf("%c,", character);
    }
    printf("\n");
  }

  return 0;
}
