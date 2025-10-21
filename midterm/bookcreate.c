#include <stdio.h>
#include "db.dat"
int main(int argc, char* argv[])
{
	struct book rec;
	FILE *fp;
	if(argc != 2){
		fprintf(stderr, "How to use: FileName\n",argv[0]);
		exit(1);
	}
	fp = fopen(argv[1],"wb");
	printf("%-10s %-8s %-6s %-4s %-2s %0s", "id"," bookname", "author", "year", "numofborrow", "borrow");
	while(scnf("%d %s %s %d %d %d",&rec.id rec.name, rec.author, &rec.year, &rec.numofborrow, &borrow)== 6)
		fwrite(&rec,sizeof(rec), 1,fp);
	fclose(fp);
	exit(0);
}

