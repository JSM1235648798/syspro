#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 1024
#define MAXARG 64

char *trim(char *s) {
    char *end;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == 0) return s;
    end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t')) {
        *end = 0;
        end--;
    }
    return s;
}

int main() {
    char line[MAXLINE];
    char *cmd;
    char *saveptr1;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0)
            continue;

        saveptr1 = NULL;
        cmd = strtok_r(line, ";", &saveptr1);

        while (cmd != NULL) {
            char *args[MAXARG];
            char *infile = NULL;
            char *outfile = NULL;
            int background = 0;
            char *p;

            cmd = trim(cmd);
            if (strlen(cmd) == 0) {
                cmd = strtok_r(NULL, ";", &saveptr1);
                continue;
            }

            if (strncmp(cmd, "[shell]", 7) == 0) {
                cmd = cmd + 7;
                cmd = trim(cmd);
            }

            if (strlen(cmd) == 0) {
                cmd = strtok_r(NULL, ";", &saveptr1);
                continue;
            }

            if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0)
                return 0;

            p = cmd + strlen(cmd) - 1;
            while (p >= cmd && (*p == ' ' || *p == '\t')) {
                *p = 0;
                p--;
            }
            if (p >= cmd && *p == '&') {
                background = 1;
                *p = 0;
            }

            char *gt = strchr(cmd, '>');
            if (gt != NULL) {
                *gt = 0;
                gt++;
                gt = trim(gt);
                if (*gt != 0) {
                    outfile = gt;
                    while (*gt && *gt != ' ' && *gt != '\t') gt++;
                    *gt = 0;
                }
            }

            char *lt = strchr(cmd, '<');
            if (lt != NULL) {
                *lt = 0;
                lt++;
                lt = trim(lt);
                if (*lt != 0) {
                    infile = lt;
                    while (*lt && *lt != ' ' && *lt != '\t') lt++;
                    *lt = 0;
                }
            }

            cmd = trim(cmd);
            if (strlen(cmd) == 0) {
                cmd = strtok_r(NULL, ";", &saveptr1);
                continue;
            }

            int i = 0;
            char *tok;
            char *saveptr2 = NULL;
            tok = strtok_r(cmd, " \t", &saveptr2);
            while (tok != NULL && i < MAXARG - 1) {
                args[i++] = tok;
                tok = strtok_r(NULL, " \t", &saveptr2);
            }
            args[i] = NULL;

            if (args[0] == NULL) {
                cmd = strtok_r(NULL, ";", &saveptr1);
                continue;
            }

            pid_t pid = fork();
            if (pid == 0) {
                if (infile != NULL) {
                    int fd = open(infile, O_RDONLY);
                    if (fd < 0) exit(1);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                if (outfile != NULL) {
                    int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0) exit(1);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                execvp(args[0], args);
                exit(1);
            } else if (pid > 0) {
                if (!background)
                    waitpid(pid, NULL, 0);
            }

            cmd = strtok_r(NULL, ";", &saveptr1);
        }
    }
    return 0;
}

