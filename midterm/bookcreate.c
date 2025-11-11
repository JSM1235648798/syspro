#include <stdio.h>

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
    BOOK books[4] = {
        {1, "1984", "George", 1949, 7, 0},
        {2, "Luster", "Raven", 2020, 3, 1},
        {3, "Hamnet", "Maggie", 2020, 1, 0},
        {4, "theWish", "Nocholas", 2021, 2, 1}
    };

    FILE *fp = fopen("db.dat", "wb");
    if (fp == NULL) return 1;
    fwrite(books, sizeof(BOOK), 4, fp);
    fclose(fp);
    return 0;
}

