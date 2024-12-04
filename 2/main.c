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
      printf("Last char before null: %d\n", p[len-1]);
      printf("Null: %d\n", p[len]);
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
    bool eol = false;
    int level = 0, accindex = 0, read = 0;
    char accumulate[50];
    fprintf(stderr, "New line: %s", reportlines[n]);
    fprintf(stderr, "Accumulating: ");
    while (true) {
      sscanf(reportlines[n], "%d\n%n", &report[n][level], &read);
      if (read == 0) {
        fprintf(stderr, "\nStart analysis\n");
        int n_partial_safe = 0;
        int full_safe = 0;
        for (int i = 0; i <= level; i++) {
          /* This chooses what level to skip*/
          /* Include one more skip, to make sure
          the full report is tested as well*/

          printf("\nSkip %d: ", i);
          bool increasing = false;
          bool decreasing = false;
          bool inner_safe = false;
          int old_j = -1;
          for (int j = 0; j < level; j++) {
            if (j == i)
              break;
            printf("%d, ", report[n][j]);
            if (old_j != -1) { /* Else this is the first loop*/
              int diff = report[n][old_j] - report[n][j];
              if (diff > 0) {
                decreasing = true;
              } else if (diff < 0) {
                increasing = true;
              }
              if ((increasing && decreasing) || diff == 0 || abs(diff) > 3) {
                if (i == level) {
                  /* This means we are testing the full test case*/
                  full_safe = false;
                } else {
                  inner_safe = false;
                }
                printf("U");
                break;
              } 
              old_j = j;
            }
            n_partial_safe += 1;
          }
          if (full_safe) {
            continue;
          } else if (! full_safe && n_partial_safe > 0) {
            continue;
          } else {
            n_unsafe++;
          }

        }
        break;
      }
      reportlines[n] += read; /* Advance the pointer */
      if (report[n][level] == 0)
        continue; /* Need to break here, the zeros do not appear in data
        and there appear ghost bangs that become zeros*/
      printf("%d, ", report[n][level]);
      level++;
    }
    printf("\n");
  }
  printf("Unsafe reports: %d\n", n_unsafe);
  printf("Safe reports: %d\n", nlines - n_unsafe);

  return 0;
}
