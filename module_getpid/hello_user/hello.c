#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include "hello.h"
#include "mounts_utils.h"
#include "ftrace_utils.h"
#include "module_utils.h"
#define MOD_KO_NAME "hello_getpid"
#define MOD_KO_PATH "../hello_kernel/hello_getpid.ko"

/*
 * @desc: a Helo World, just print a "Hello..." to ftrace.
 */
int main(int argc, char* argv[])
{
    int ret = -1;
    pid_t pid = getpid();
    char old_tracing = '\0';
    char old_tracer[MAX_TRACER_STR] = {'\0'};
    char* progpath = strdup(argv[0]);
    char* progname = basename(progpath);

    if (ftrace_set_tracer("function", old_tracer) < 0) {
        errormsg("set function_graph tracer failed");
        goto exiting;
    }

    if (ftrace_pid_add(&pid) < 0) {
        errormsg("ftrace add pid of %s failed", progname);
        goto exiting;
    }

    if ((old_tracing = ftrace_set_tracing('1')) < 0) {
        errormsg("open ftrace recording failed");
        goto exiting;
    }

    if (ftrace_marker("[%s] Hello! My PID: %ld\n", progname, getpid()) < 0) {
        errormsg("greeting error");
        goto exiting;
    }

    if (ftrace_insmod(MOD_KO_PATH) < 0) {
        errormsg("install module failed");
        goto exiting;
    }

    if (ftrace_rmmod(MOD_KO_NAME) < 0) {
        errormsg("remove module %s failed", MOD_KO_NAME);
        goto exiting;
    }
    ret = 0;
exiting:
    if (old_tracing > 0) {
        if (ftrace_set_tracing(old_tracing) < 0) {
            errormsg("restoring ftrace recording failed");
        }
    }
    if (strlen(old_tracer) > 0) {
        if (ftrace_set_tracer(old_tracer, NULL) < 0) {
            errormsg("restoring ftracer tracer failed");
        }
    }
    if (ftrace_pid_reset() < 0) {
        errormsg("clear set_ftrace_pid failed");
    }
    if (progpath) {
        free(progpath);
        progpath = NULL;
    }
    ftrace_close();
    return ret;
}