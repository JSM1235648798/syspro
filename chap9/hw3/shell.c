#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void trim(char *s) {
    char *p = s;
    int len;

    while (*p && isspace((unsigned char)*p)) p++;
    if (p != s) memmove(s, p, strlen(p) + 1);

    len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[len - 1] = '\0';
        len--;
    }
}

void run_one_command(char *cmdline) {
    char *args[MAX_ARGS];
    char *infile = NULL;
    char *outfile = NULL;
    int argc = 0;
    int background = 0;
    char *token;
    pid_t pid;

    trim(cmdline);
    if (cmdline[0] == '\0') return;

    if (cmdline[strlen(cmdline) - 1] == '&') {
        background = 1;
        cmdline[strlen(cmdline) - 1] = '\0';
        trim(cmdline);
        if (cmdline[0] == '\0') return;
    }

    token = strtok(cmdline, " \t");
    while (token && argc < MAX_ARGS - 1) {
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t");
            if (token) outfile = token;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            if (token) infile = token;
        } else {
            args[argc++] = token;
        }
        token = strtok(NULL, " \t");
    }
    args[argc] = NULL;
    if (argc == 0) return;

    if (strcmp(args[0], "exit") == 0) exit(0);

    pid = fork();
    if (pid == 0) {
        if (infile) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) {
                perror("open");
                _exit(1);
            }
            dup2(fd, 0);
            close(fd);
        }
        if (outfile) {
            int fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
            if (fd < 0) {
                perror("open");
                _exit(1);
            }
            dup2(fd, 1);
            close(fd);
        }
        execvp(args[0], args);
        perror("execvp");
        _exit(1);
    } else if (pid > 0) {
        if (!background) waitpid(pid, NULL, 0);
    } else {
        perror("fork");
    }
}

int main(void) {
    char line[MAX_LINE];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;

        char *cmd = strtok(line, ";\n");
        while (cmd) {
            run_one_command(cmd);
            cmd = strtok(NULL, ";\n");
        }
    }
    return 0;
}

