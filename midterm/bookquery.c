#include <stdio.h>
#include "db.dat"

int main(int argc, char* argv[])
{
	struct student rec;
	FILE *fp;
	if(argc != 2){
		fprintf(stderr,"How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp = fopen(argc[1], "w");
	printf("%-10s %-8s %-6s %-4s %-2s %-1s\n", "id" , "bookname", "author", "year", "numofborrow", "borrow");
	while(scanf("%d %s %s %d %d %d",&rec.id, rec.name, rec.author, &rec.year, &rec.numofborrow, &rec.borrow)==6)
		fprintf(fp," %d %s %s %d %d %d", rec.id, rec.name, rec.author, rec.year, rec.numofborrow, rec.borrow);
	fclose(fp);
	return 0;
}
