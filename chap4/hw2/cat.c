#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;
    int line_num = 1;
    int print_line_numbers = 0;
    int i;

    if (argc < 2) {
        fp = stdin;
        if (print_line_numbers)
            printf("%6d\t", line_num++);
        c = getc(fp);
        while (c != EOF) {
            putc(c, stdout);
            if (print_line_numbers && c == '\n' && (fp == stdin)) {
                printf("%6d\t", line_num++);
            }
            c = getc(fp);
        }
        if (fp != stdin) fclose(fp);
        return 0;
    }

    int start_idx = 1;
    if (strcmp(argv[1], "-n") == 0) {
        print_line_numbers = 1;
        start_idx = 2;
    }

    for (i = start_idx; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        if (print_line_numbers)
            printf("%6d\t", line_num++);

        c = getc(fp);
        while (c != EOF) {
            putc(c, stdout);
            if (print_line_numbers && c == '\n') {
                printf("%6d\t", line_num++);
            }
            c = getc(fp);
        }
        fclose(fp);
    }

    return 0;
}

