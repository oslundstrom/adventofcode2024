#include "main.h"
#include <string.h>

bool check_string(char* string, int origin, int offset)
{
        char * ans = "XMAS";
        int len = strlen(ans);
        for (int i=0; i<len; i++) {
                if (string[origin + i * offset] != ans[i])
                        return false;
        }
        return true;
}

int main(int argc, char *argv[])
{
        return 0;
}
