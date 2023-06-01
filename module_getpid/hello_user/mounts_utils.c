#include "mounts_utils.h"
#include "hello.h"
#include <assert.h>
#define _STR(x) #x
#define STR(x) _STR(x)
#define MOUNT_ENTRY_FMT "%*s %" STR(MAX_PATH) "s %99s %*s %*d %*d\n"

static const char* find_fs_path(const char* fstype, char* fspath)
{
    char type[100] = {'\0'};
    FILE *fp = NULL;
    int found = -1;
    int ret = -1;

    assert(fstype && fspath);

    if ((fp = fopen(MOUNTS_LIST,"r")) == NULL) {
        perrorf("open %s failed", MOUNTS_LIST);
        return NULL;
    }

    while ((ret = fscanf(fp, MOUNT_ENTRY_FMT, fspath, type)) == 2) {
        if (strcmp(type, fstype) == 0) {
            found = 1;
            break;
        }
    }
    if (ret < 0) {
        perrorf("read %s error", MOUNTS_LIST);
    }
    fclose(fp);

    return found ? fspath : NULL;
}

/*
 * @desc: find the path of debugfs.
 * @return: the absolute path of debugfs on success, NULL on error.
*/
const char *find_debugfs(void)
{
    static int found = 0;
    static char fspath[MAX_PATH+1] = {'\0'};

    if (found) {
        return fspath;
    }

    if (find_fs_path("debugfs", fspath)) {
        found = 1;
    }

    return found ? fspath : NULL;
}


/*
 * @desc: find the path of sysfs.
 * @return: the absolute path of sysfs on success, NULL on error.
*/
const char *find_sysfs(void)
{
    static int found = 0;
    static char fspath[MAX_PATH+1] = {'\0'};

    if (found) {
        return fspath;
    }

    if (find_fs_path("sysfs", fspath)) {
        found = 1;
    }

    return found ? fspath : NULL;
}
