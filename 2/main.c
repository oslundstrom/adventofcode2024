#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLINES 10000
#define MAXLENGHT 1000

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

  int report[MAXLINES][100];
  int n_unsafe = 0;
  // Print the array
  for (int n = 0; n < nlines; n++) {
    bool increasing = false;
    bool decreasing = false;
    bool eol = false;
    int level = 0, accindex = 0;
    char accumulate[50];
    fprintf(stderr, "%s", reportlines[n]);
    for (char character = *reportlines[n]; eol == false; character = *++reportlines[n]) {
      // fprintf(stderr, "%c", character);
      switch (character) {
        case '\0':
          eol = true;
          fprintf(stderr, "(EOL with accindex %d)", accindex);
          if (accindex == 1) { /* Nothing accumulated, continue*/
            fprintf(stderr, "(EOL with accindex %d, prev is %c)", accindex, accumulate[0]);
          }
        case ' ': case '\n': case '!':
          if (accindex == 0) { /* Nothing accumulated, continue*/
            continue;
          }
          sscanf(accumulate, "%d", &report[n][level]);
          accindex = 0;
          break;
        default:
          // printf("%c", character);
          accumulate[accindex++] = character;
          accumulate[accindex] = '\0';
          continue;
      }
      printf("%d, ", report[n][level]);
      if (level != 0) {
        int diff = report[n][level-1] - report[n][level];
        if (diff > 0) {
          decreasing = true;
        } else if (diff < 0) {
          increasing = true;
        }
        if ((increasing && decreasing) || diff == 0 || abs(diff) > 3) {
          n_unsafe += 1;
          printf("U");
          break;
        }
      }
      level++;
    }
    printf("\n");
  }
  printf("Unsafe reports: %d\n", n_unsafe);
  printf("Safe reports: %d\n", nlines - n_unsafe);

  return 0;
}
