#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LEN 100

int main(int argc, char *argv[]) {
    char savedText[MAX_LINES][MAX_LEN];
    int lineCount = 0;
    FILE *fd;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    fd = fopen(argv[1], "r");
    if (fd == NULL) {
        printf("File open failed\n");
        return 1;
    }
    printf("File read success\n");
    while (fgets(savedText[lineCount], MAX_LEN, fd) != NULL) {
        savedText[lineCount][strcspn(savedText[lineCount], "\n")] = '\0';
        lineCount++;
        if (lineCount >= MAX_LINES) break;
    }
    fclose(fd);

    printf("Total Line : %d\n", lineCount);
    printf("You can choose 1 ~ %d Line\n", lineCount);
    printf("Pls 'Enter' the line to select : ");

    char input[256];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < lineCount; i++)
            printf("%s\n", savedText[i]);
    } else {
        char *token = strtok(input, ",");
        while(token) {
            int start, end;
            if (strchr(token, '-') != NULL) {
                sscanf(token, "%d-%d", &start, &end);
                for (int i = start; i <= end && i <= lineCount; i++)
                    printf("%s\n", savedText[i-1]);
            } else {
                int n = atoi(token);
                if (n >= 1 && n <= lineCount)
                    printf("%s\n", savedText[n-1]);
            }
            token = strtok(NULL, ",");
        }
    }
    return 0;
}

