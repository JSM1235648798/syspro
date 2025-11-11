#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *src, *dst;
    int option, ch;

    if (argc != 4) {
        printf("사용법: copy <옵션 0|1|2> <source> <destination>\n");
        return 1;
    }

    option = atoi(argv[1]);

    src = fopen(argv[2], "r");
    if (src == NULL) {
        printf("원본 파일을 열 수 없습니다.\n");
        return 1;
    }

    dst = fopen(argv[3], "w");
    if (dst == NULL) {
        printf("대상 파일을 생성할 수 없습니다.\n");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF) {
        if (option == 1)         
            ch = tolower(ch);
        else if (option == 2)     
            ch = toupper(ch);
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);

    return 0;
}

