#include <stdio.h>
#include "lib.h"

int main(int argc, char *argv[])
{
        char * line;
        char * text;
        size_t len, size, read;
        while ((len = getline(&line, &size, stdin)) != 0) {
                printf("%ld\n", len);
                line += len;
                read += len;
        }

        return 0;
}
