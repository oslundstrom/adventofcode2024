#include <stdio.h>
#include <string.h>
#include "lib.h"


#define MAXLINES 500
#define MAXLINELEN 200


int main(int argc, char *argv[])
{
        char * line;
        char text[MAXLINES*MAXLINELEN];
        size_t len, size, read, linelen;
        while ((len = getline(&line, &size, stdin)) != -1) {
		// printf("Read %s\n", line);
		line[len-1] = '\0';
		strcat(text, line);
                read += len;
		linelen = len - 1;
        }
	len = linelen;
	printf("Read %ld chars\n", read);
	printf("Len is %ld\n", len);
	printf("Read \n%s", text);

	int west_offset = -1;
	int east_offset = 1;
	int south_offset = -len;
	int north_offset = len;
	int nw_offset = -len-1;
	int ne_offset = -len+1;
	int sw_offset = len-1;
	int se_offset = len+1;

	printf("\n\n");
	
	int found = 0;
	for (int i=0; i<read; i++) {
		printf("\nChecking char %d, (%d, %d) ", i, i/len, i%len);
		if (check_string(text, i, west_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, east_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, south_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, north_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, nw_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, ne_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, sw_offset, len)) {
			found++;
			printf("\n");
		}
		if (check_string(text, i, se_offset, len)) {
			found++;
			printf("\n");
		}
	}

	printf("Found %d strings\n", found);
	
        return 0;
}
