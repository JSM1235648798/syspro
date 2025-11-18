#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 20

int main() {
    char line[256];
    char *args[MAXARG];

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0)
            continue;

        int len = strlen(line);
        while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t')) {
            line[--len] = 0;
        }

        int background = 0;
        if (len > 0 && line[len - 1] == '&') {
            background = 1;
            line[--len] = 0;
            while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t')) {
                line[--len] = 0;
            }
        }

        if (strlen(line) == 0)
            continue;

        int i = 0;
        char *tok = strtok(line, " \t");
        while (tok != NULL && i < MAXARG - 1) {
            args[i++] = tok;
            tok = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        printf("[%d] Parent process start\n", getpid());

        pid_t pid = fork();
        if (pid < 0) {
            printf("Parent process end\n");
            printf("Exit\n");
            break;
        } else if (pid == 0) {
            if (background)
                printf("[%d] child process start\n", getpid());
            execvp(args[0], args);
            exit(1);
        } else {
            int status;
            if (!background)
                waitpid(pid, &status, 0);
            else
                waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                if (background)
                    printf("success\n");
                else
                    printf("success\n");
            } else {
                printf("Parent process end\n");
                printf("Exit\n");
                break;
            }
        }
    }
    return 0;
}

