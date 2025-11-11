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
    FILE *fp = fopen("data.dat", "rb");
    if (fp == NULL) {
        printf("data.dat not found\n");
        return 1;
    }

    int count = fread(books, sizeof(BOOK), 10, fp);
    fclose(fp);

    int mode, id;

    printf("0 bookId: borrow book, 1 bookId: return book ) ");
    if (scanf("%d %d", &mode, &id) != 2) return 1;


    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            if (mode == 0) {
                if (books[i].borrow == 1) {
                    printf("You cannot borrow bellow book since it has been booked.\n");
                } else {
                    books[i].borrow = 1;
                    books[i].numofborrow++;
                    printf("You've got bellow book..\n");
                }
            } else if (mode == 1) {
                if (books[i].borrow == 0) {
                    printf("You cannot return this book because it was not borrowed.\n");
                } else {
                    books[i].borrow = 0;
                    printf("You've returned bellow book..\n");
                }
            }

            printf("id  %-12s %-12s %-8s %-12s %-8s\n", "bookname", "author", "year", "numofborrow", "borrow");
            printf("%-3d %-12s %-12s %-8d %-12d %-8s\n",
                   books[i].id,
                   books[i].bookname,
                   books[i].author,
                   books[i].year,
                   books[i].numofborrow,
                   books[i].borrow ? "True" : "False");
            break;
        }
    }

    fp = fopen("data.dat", "wb");
    if (fp == NULL) return 1;
    fwrite(books, sizeof(BOOK), count, fp);
    fclose(fp);

    return 0;
}

