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
    BOOK books[10];
    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) return 1;

    int count = fread(books, sizeof(BOOK), 10, fp);
    fclose(fp);

    int mode;
    scanf("%d", &mode);

    if (mode == 0)
        printf("0: list of all books, 1: list of available books ) 0\n");
    else if (mode == 1)
        printf("0: list of all books, 1: list of available books ) 1\n");

    printf("id  %-12s %-12s %-8s %-12s %-8s\n", "bookname", "author", "year", "numofborrow", "borrow");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (mode == 0 || (mode == 1 && books[i].borrow == 0)) {
            printf("%-3d %-12s %-12s %-8d %-12d %-8s\n",
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

