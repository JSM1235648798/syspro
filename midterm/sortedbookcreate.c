#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char bookname[30];
    char author[30];
    int year;
    int numofborrow;
    int borrow;
} BOOK;

int main(void)
{
    BOOK books[50];
    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) return 1;
    int count = fread(books, sizeof(BOOK), 50, fp);
    fclose(fp);

    int mode;
    printf("0: list of all books, 1: list of available books ) ");
    fflush(stdout);
    scanf("%d", &mode);
   

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].year < books[j].year ||
               (books[i].year == books[j].year && books[i].id > books[j].id)) {
                BOOK tmp = books[i];
                books[i] = books[j];
                books[j] = tmp;
            }
        }
    }

    fp = fopen("db.dat", "wb");
    if (fp == NULL) return 1;
    fwrite(books, sizeof(BOOK), count, fp);
    fclose(fp);

    printf("id   bookname       author         year           numofborrow borrow\n");
    for (int i = 0; i < count; i++) {
        if (mode == 0 || (mode == 1 && books[i].borrow == 1)) {
            printf("%-4d %-14s %-14s %-15d %11d %-6s\n",
                   books[i].id,
                   books[i].bookname,
                   books[i].author,
                   books[i].year,
                   books[i].numofborrow,
                   books[i].borrow ? "True" : "False");
        }
    }

    return 0;
}

