#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "logger.h"

int sign(int i) {
	// Returns -1 if negative and 1 if positive, 0 if 0
	if (i == 0)
		return 0;
	return i/abs(i);
}

bool check_string(char* string, int origin, int offset, int linelen) {
    char * ans = "XMAS";
    int len = strlen(ans);
    int col, row;
    int matrix_index;


    log_debug("Starting comparison at origin=%d with offset=%d", origin, offset);
    log_debug("Len is %d\n", len);
    printf("[%d] ", offset);

    
    int old_row = -1, old_col = -1;
    int row_dir = -2, col_dir = -2;

    for (int i=0; i<len; i++) {
        matrix_index = origin + i * offset;
        row = matrix_index / linelen;
        col = matrix_index % linelen;

        log_debug("Comparing string[%d]='%c' (row %d, col %d) to ans[%d]='%c'",
                 matrix_index, string[matrix_index], row, col, i, ans[i]);

	if (old_row > -1) {
	    if (row_dir != -2) {
		log_debug("Dir is %i (row) and %i (col)", row_dir, col_dir);
		if (row_dir != sign(old_row - row) || col_dir != sign(old_col - col)) {
		    log_debug("Out of bounds at %d", i);
	            printf("%c| ", string[matrix_index]);
		    return false;
		}
	    }
	    row_dir = sign(old_row - row);
	    col_dir = sign(old_col - col);
	}
        old_row = row;
        old_col = col;


        if (string[matrix_index] != ans[i]) {
            log_debug("Character mismatch at position %d", i);
	    printf("%c- ", string[matrix_index]);
            return false;
        }
	printf("%c", string[matrix_index]);
    }

    printf("\n");
    log_info("Found match at origin=%d with offset=%d (%d, %d)", origin, offset, origin / linelen, origin % linelen);
    return true;
}
