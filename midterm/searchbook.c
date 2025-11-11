#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char bookname[30];
    char author[30];
    int year;
    int numofborrow;
    int borrow;
} BOOK;

void toLower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

int main(void)
{
    BOOK books[50];
    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) return 1;
    int count = fread(books, sizeof(BOOK), 50, fp);
    fclose(fp);

    char input[30], temp[30];
    printf("input name of book ) ");
    fflush(stdout);
    scanf("%s", input);

    int found = 0;
    char lowerInput[30];
    strcpy(lowerInput, input);
    toLower(lowerInput);

    for (int i = 0; i < count; i++) {
        strcpy(temp, books[i].bookname);
        toLower(temp);
        if (strcmp(temp, lowerInput) == 0) {
            printf("id   bookname       author         year           numofborrow borrow\n");
            printf("%-4d %-14s %-14s %-15d %11d %-6s\n",
                   books[i].id,
                   books[i].bookname,
                   books[i].author,
                   books[i].year,
                   books[i].numofborrow,
                   books[i].borrow ? "True" : "False");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("not found book name : '%s'\n", input);

    return 0;
}

