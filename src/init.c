#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int init(char *path) {
    struct stat statbuf;
    if ((stat(path, &statbuf) != 0 || S_ISDIR(statbuf.st_mode) == 0) &&
        mkdir(path, 0755) == -1) {
        fprintf(stderr, "Failed to create path directory %s: %s\n", path, strerror(errno));
        return 1;
    }
    if (chdir(path) == -1) {
        fprintf(stderr, "Failed to move to directory %s: %s\n", path, strerror(errno));
        return 1;
    }

    if (mkdir(".git", 0755) == -1 ||
        mkdir(".git/objects", 0755) == -1 ||
        mkdir(".git/refs", 0755) == -1) {
        fprintf(stderr, "Failed to create directories: %s\n", strerror(errno));
        return 1;
    }

    FILE *headFile = fopen(".git/HEAD", "w");
    if (headFile == NULL) {
        fprintf(stderr, "Failed to create .git/HEAD file: %s\n", strerror(errno));
        return 1;
    }
    fprintf(headFile, "ref: refs/heads/main\n");
    fclose(headFile);

    printf("Initialized git directory\n");
}
