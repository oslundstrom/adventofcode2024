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
  while ((len = getline(&line, &size, stdin)) > 0) {
    printf("Line: %s\n", line);
    printf("Len: %d\n", len);
    printf("Size: %d\n", size);
    if (nlines >= MAXLINES || (p = malloc(size)) == NULL) {
      printf("error: input too big!\n");
      return 1;
    } else {
      strcpy(p, line);
      printf("Last char before null: %d\n", p[len-1]);
      printf("Null: %d\n", p[len]);
      if (p[len-1] == 10) {
        p[len-1] = '\0';
      }
      printf("Fixed line: %sEND\n", p);
      reportlines[nlines++] = p;
    }
  }
  // printf("Consumed all input\n");
  // printf("Lines: %d\n", nlines);
  // printf("Last line: %s\n", line);

  int report[MAXLINES][100];
  int n_unsafe = 0;
  int n_saved = 0;
  // Print the array
  for (int n = 0; n < nlines; n++) {
    bool eol = false;
    int level = 0, accindex = 0, read = 0;
    char accumulate[50];
    printf("\nNew line (no %d): %s\n", n, reportlines[n]);
    printf("Accumulating: ");
    while (true) {
      int result = sscanf(reportlines[n], "%d\n%n", &report[n][level], &read);
      if (result == EOF || result < 1) {
        printf("\nStart analysis");
        int n_partial_safe = 0;
        bool full_safe = true;
        for (int i = 0; i <= level; i++) {
          /* This chooses what level to skip*/
          /* Include one more skip, to make sure
          the full report is tested as well*/

          printf("\nSkip %d: ", i);
          bool increasing = false;
          bool decreasing = false;
          bool inner_safe = true;
          int old_j = -1;
          for (int j = 0; j < level; j++) {
            if (j == i)
              continue;
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
                  printf("U");
                } else {
                  inner_safe = false;
                  printf("u");
                }
                break;
              } 
            }
            old_j = j;
          }
          if (i != level && inner_safe) {
            printf(" is");
            n_partial_safe += 1;
          }
        }
        if (full_safe) {
          printf("\nS (%d partials)", n_partial_safe);
          n_partial_safe += 1;
        } else if (! full_safe && n_partial_safe > 0) {
          printf("\ndS (%d partials)", n_partial_safe);
          n_saved++;
        } else {
          printf("\nU (%d partials)", n_partial_safe);
          n_unsafe++;
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
  printf("Saved reports: %d\n", n_saved);
  printf("Safe reports: %d\n", nlines - n_unsafe);

  return 0;
}
