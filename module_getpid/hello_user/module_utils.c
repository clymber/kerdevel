#include "module_utils.h"
#include "hello.h"
#include "ftrace_utils.h"
#include <unistd.h>
#include <sys/wait.h>
#define INSMOD "/usr/sbin/insmod"
#define RMMOD "/usr/sbin/rmmod"

static int ftrace_pid_execve(const char* cmd, char* const args[], char* const envp[])
{
    int ret = -1;
    int wstatus = 0;
    pid_t pid = -1;

    if (!cmd || !cmd[0]) {
        errormsg("invalid input, no command specified");
        return -1;
    }

    if ((pid = fork()) < 0) {
        perrorf("fork new process failed");
        return -1;
    }

    if (pid > 0) {
        if ((ret = waitpid(pid, &wstatus, 0)) < 0) {
            perrorf("wait pid %ld failed", (long)pid);
            return -1;
        }

        if (!WIFEXITED(wstatus)) {
            errormsg("subprocess %ld exited abnormally", (long)pid);
            return -1;
        }

        if ((ret = WEXITSTATUS(wstatus)) != 0) {
            errormsg("subprocess %ld return none-zero", (long)pid);
            return -1;
        }
        return 0;
    }

    pid = getpid();
    if (ftrace_pid_add(&pid) < 0) {
        errormsg("ftrace add pid %ld failed", (long)pid);
        return -1;
    }

    if ((ret = execve(cmd, args, envp)) < 0) {
        perrorf("can't execute %s", cmd);
    }
    return ret;
}

int ftrace_insmod(char* mod_path)
{
    if (!mod_path || !mod_path[0]) {
        errormsg("invalid input, no module specified");
        return -1;
    }
    char* const args[] = {
        INSMOD,
        mod_path,
        NULL
    };
    if (ftrace_pid_execve(INSMOD, args, NULL) < 0) {
        errormsg("insmod %s failed", mod_path);
        return -1;
    }
    return 0;
}

int ftrace_rmmod(char* mod_name)
{
    if (!mod_name || !mod_name[0]) {
        errormsg("invalid input, no module specified");
        return -1;
    }
    char* const args[] = {
        RMMOD,
        mod_name,
        NULL
    };
    if (ftrace_pid_execve(RMMOD, args, NULL) < 0) {
        errormsg("rmmod %s failed", mod_name);
        return -1;
    }
    return 0;
}