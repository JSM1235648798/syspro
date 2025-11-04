#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            char **p;
            for (p = environ; *p != NULL; p++)
                printf("%s\n", *p);
        } else {
            char *val = getenv(argv[2]);
            if (val != NULL)
                printf("%s = %s\n", argv[2], val);
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        uid_t ruid = getuid();
        uid_t euid = geteuid();
        struct passwd *rpw = getpwuid(ruid);
        struct passwd *epw = getpwuid(euid);
        printf("My Realistic User ID : %d(%s)\n", (int)ruid, rpw ? rpw->pw_name : "");
        printf("My Valid User ID : %d(%s)\n", (int)euid, epw ? epw->pw_name : "");
    } else if (strcmp(argv[1], "-g") == 0) {
        gid_t rgid = getgid();
        gid_t egid = getegid();
        struct group *rg = getgrgid(rgid);
        struct group *eg = getgrgid(egid);
        printf("My Realistic Group ID : %d(%s)\n", (int)rgid, rg ? rg->gr_name : "");
        printf("My Valid Group ID : %d(%s)\n", (int)egid, eg ? eg->gr_name : "");
    } else if (strcmp(argv[1], "-i") == 0) {
        printf("my process number : [%d]\n", (int)getpid());
    } else if (strcmp(argv[1], "-p") == 0) {
        printf("my parent's process number : [%d]\n", (int)getppid());
    }

    return 0;
}

