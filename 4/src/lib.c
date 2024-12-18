#include <string.h>
#include <stdio.h>
#include "lib.h"

#define LINELEN  140
#define MAXLINES 500

#define SOUTH_OFFSET (-LINELEN)
#define NORTH_OFFSET (LINELEN)
#define NW_OFFSET (-LINELEN-1)
#define NE_OFFSET (-LINELEN+1)
#define SW_OFFSET (LINELEN-1)
#define SE_OFFSET (LINELEN+1)


bool check_string(char* string, int origin, int offset)
{
        char * ans = "XMAS";
        int len = strlen(ans);
        int col, row;
        int matrix_index;
	printf("Starting comparison\n");
        for (int i=0; i<len; i++) {
                matrix_index = origin + i * offset;
                row = i / LINELEN;
                col = i % LINELEN;
                // Also implement checks for backward crossings
                if (row == 0 && i != 0)
                        return false;
                if (col == 0 && i != 0)
                        return false;
		printf("Comparing %c to %c\n", string[matrix_index], ans[i]);
                if (string[matrix_index] != ans[i])
                        return false;
        }
        return true;
}

