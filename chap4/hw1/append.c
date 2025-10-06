#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    FILE *src, *dest;
    char buffer[BUFSIZE];
    size_t n;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file destination_file\n", argv[0]);
        exit(1);
    }

    src = fopen(argv[1], "r");
    if (src == NULL) {
        perror("fopen source file");
        exit(2);
    }

    dest = fopen(argv[2], "a");  
    if (dest == NULL) {
        perror("fopen destination file");
        fclose(src);
        exit(3);
    }

    while ((n = fread(buffer, 1, BUFSIZE, src)) > 0) {
        if (fwrite(buffer, 1, n, dest) != n) {
            perror("fwrite");
            fclose(src);
            fclose(dest);
            exit(4);
        }
    }

    fclose(src);
    fclose(dest);
    return 0;
}

