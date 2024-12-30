#define UNUSED(x) (void)(x)

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <ftw.h>
#include <unistd.h>

int rm_cb(const char *path, const struct stat *sb, int ftw_flag, struct FTW *ftwbuf) {
    UNUSED(sb);
    UNUSED(ftw_flag);
    UNUSED(ftwbuf);
    if (remove(path)) {
        perror(path);
        return -1;
    }
    return 0;
}
int rmrf(const char *path) {
    return nftw(path, rm_cb, 2 << 5, FTW_DEPTH | FTW_PHYS);
}
