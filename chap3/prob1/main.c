#include <stdio.h>
#include <string.h>

#define SIZE 100

int main() {
    char arr[5][SIZE];
    int i = 0;

    
    while (i < 5) {
        printf( i + 1);
        fgets(arr[i], SIZE, stdin);

      ê
        arr[i][strcspn(arr[i], "\n")] = 0;
        i++;
    }

    
    for (int x = 0; x < 4; x++) {
        for (int y = x + 1; y < 5; y++) {
            if (strlen(arr[x]) < strlen(arr[y])) {
                char temp[SIZE];
                strcpy(temp, arr[x]);
                strcpy(arr[x], arr[y]);
                strcpy(arr[y], temp);
            }
        }
    }

   
    for (int j = 0; j < 5; j++) {
        printf("%s\n", arr[j]);
    }

    return 0;
}

