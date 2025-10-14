#include <stdio.h>
#include <string.h>

int main() {
    char lines[100][256];
    int count = 0;
    FILE *fp = fopen("test.txt", "w");
    while (fgets(lines[count], sizeof(lines[count]), stdin)) {
        count++;
    }
    for (int i = count - 1; i >= 0; i--) {
        fputs(lines[i], fp);
    }
    fclose(fp);
    return 0;
}

