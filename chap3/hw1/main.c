#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];
char lines[5][MAXLINE];
int lengths[5];
char temp[MAXLINE];

int main() {
    int i, j;

    for (i = 0; i < 5; i++) {
        fgets(lines[i], MAXLINE, stdin);
        int len = strlen(lines[i]);
        if (lines[i][len - 1] == '\n') {
            lines[i][len - 1] = '\0';
            len--;
        }
        lengths[i] = len;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4 - i; j++) {
            if (lengths[j] < lengths[j + 1]) {
                int tmp_len = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = tmp_len;

                strcpy(temp, lines[j]);
                strcpy(lines[j], lines[j + 1]);
                strcpy(lines[j + 1], temp);
            }
        }
    }

    for (i = 0; i < 5; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

