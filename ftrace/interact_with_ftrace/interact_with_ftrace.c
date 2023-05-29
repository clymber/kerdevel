#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#define MAX_PATH 256
#define _STR(x) #x
#define STR(x) _STR(x)
#define MOUNTS_LIST "/proc/mounts"
#define MOUNT_ENTRY_FMT "%*s %" STR(MAX_PATH) "s %99s %*s %*d %*d\n"

/*
 * @desc: print an error message, including errno, to stdand error
*/
#define perrorf(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt ": %s\n", ##__VA_ARGS__, strerror(errno))

/*
 * @desc: find the path of debugfs.
 * @return: the absolute path of debugfs on success, NULL on error.
*/
static const char *find_debugfs(void)
{
    static char debugfs[MAX_PATH+1] = {'\0'};
    static int debugfs_found = 0;
    char type[100] = {'\0'};
    FILE *fp = NULL;
    int ret = -1;

    if (debugfs_found) {
        return debugfs;
    }

    if ((fp = fopen(MOUNTS_LIST,"r")) == NULL) {
        perrorf("open %s failed", MOUNTS_LIST);
        return NULL;
    }

    while ((ret = fscanf(fp, MOUNT_ENTRY_FMT, debugfs, type)) == 2) {
        if (strcmp(type, "debugfs") == 0) {
            debugfs_found = 1;
            break;
        }
    }
    if (ret < 0) {
        perrorf("read %s error", MOUNTS_LIST);
    }
    fclose(fp);

    return debugfs_found ? debugfs : NULL;
}

/*
 * @desc: a Helo World, just print a "Hello..." to ftrace.
 */
int main(int argc, char* argv[])
{
    int ret = -1;
    const char* debugfs = NULL;
    char  path[MAX_PATH] = {'\0'};
    int trace_fd  = -1;
    int marker_fd = -1;

    if ((debugfs = find_debugfs()) == NULL) {
        perrorf("can't find debugfs");
        return -1;
    }

    if (snprintf(path, MAX_PATH, "%s/tracing/tracing_on", debugfs) < 0) {
        perrorf("get tracing_on path failed");
        return -1;
    }

    if ((trace_fd = open(path, O_WRONLY)) < 0) {
        perrorf("open %s failed", path);
        return -1;
    }

    if (write(trace_fd, "1", 1) < 0) {
        perrorf("enable ftrace recording failed");
        ret = -1; goto exiting;
    }

    if (snprintf(path, MAX_PATH, "%s/tracing/trace_marker", debugfs) < 0) {
        perrorf("get trace_marker path failed");
        ret = -1; goto exiting;
    }

    if ((marker_fd = open(path, O_WRONLY)) < 0) {
        perrorf("open %s failed", path);
        ret = -1; goto exiting;
    }

    const char* greeting = "Hello, Ftrace!\n";
    if (write(marker_fd, greeting,strlen(greeting)) < 0) {
        perrorf("say Hello failed");
        ret = -1; goto exiting;
    }

    ret = 0;
exiting:
    if (marker_fd >= 0) {
        (void)write(trace_fd, "0", 1);
        close(marker_fd);
        marker_fd = -1;
    }
    if (trace_fd >= 0) {
        close(trace_fd);
        trace_fd = -1;
    }
    return ret;
}