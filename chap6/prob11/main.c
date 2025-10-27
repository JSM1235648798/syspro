#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

void print_mode(mode_t mode) {
    char buf[11] = "----------";
    if (S_ISDIR(mode)) buf[0] = 'd';
    if (S_ISCHR(mode)) buf[0] = 'c';
    if (S_ISBLK(mode)) buf[0] = 'b';
    if (S_ISLNK(mode)) buf[0] = 'l';
    if (mode & S_IRUSR) buf[1] = 'r';
    if (mode & S_IWUSR) buf[2] = 'w';
    if (mode & S_IXUSR) buf[3] = 'x';
    if (mode & S_IRGRP) buf[4] = 'r';
    if (mode & S_IWGRP) buf[5] = 'w';
    if (mode & S_IXGRP) buf[6] = 'x';
    if (mode & S_IROTH) buf[7] = 'r';
    if (mode & S_IWOTH) buf[8] = 'w';
    if (mode & S_IXOTH) buf[9] = 'x';
    printf("%s ", buf);
}

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char *opts = "";

    int show_inode = 0, show_slash = 0, quote_name = 0;

    if (argc > 1) {
        opts = argv[1];
        if (strstr(opts, "-i")) show_inode = 1;
        if (strstr(opts, "-p")) show_slash = 1;
        if (strstr(opts, "-Q")) quote_name = 1;
    }

    dp = opendir(".");
    while ((entry = readdir(dp)) != NULL) {
        stat(entry->d_name, &statbuf);

        if (show_inode) {
            printf("%lu ", entry->d_ino);
        }

        print_mode(statbuf.st_mode);
        printf("%2ld ", statbuf.st_nlink);

        struct passwd *pw = getpwuid(statbuf.st_uid);
        struct group  *gr = getgrgid(statbuf.st_gid);
        printf("%s %s ", pw->pw_name, gr->gr_name);
        printf("%5ld ", statbuf.st_size);

        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&statbuf.st_mtime));
        printf("%s ", timebuf);

        if (quote_name)
            printf("\"%s\"", entry->d_name);
        else if (show_slash && S_ISDIR(statbuf.st_mode))
            printf("%s/", entry->d_name);
        else
            printf("%s", entry->d_name);

        printf("\n");
    }
    closedir(dp);
    return 0;
}

