#include "ftrace_utils.h"
#include "mounts_utils.h"
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

static FILE* tracing_on_fp = NULL;
static FILE* trace_marker_fp = NULL;

static char* ftrace_abs_path(const char* file, char* path)
{
    assert(file && path);
    const char* debugfs = NULL;
    if ((debugfs = find_debugfs()) == NULL) {
        perrorf("can't find debugfs");
        return NULL;
    }

    if (snprintf(path, MAX_PATH, "%s/%s", debugfs, file) < 0) {
        perrorf("%s, concatenating path failed", file);
        return NULL;
    }

    return path;
}

int ftrace_tracelog_set(int enable)
{
    int oldvalue = '\0';
    char path[MAX_PATH] = {'\0'};

    if (!tracing_on_fp) {
        if (ftrace_abs_path("tracing/tracing_on", path) == NULL) {
            return -1;
        }

        if ((tracing_on_fp = fopen(path, "r+")) == NULL) {
            perrorf("open %s failed", path);
            return -1;
        }
    }

    rewind(tracing_on_fp);
    if (fscanf(tracing_on_fp, "%d", &oldvalue) < 1) {
        perrorf("%s, get original value failed", path);
        return -1;
    }

    if ((bool)enable == (bool)oldvalue) {
        return oldvalue;
    }

    rewind(tracing_on_fp);
    if (fprintf(tracing_on_fp, "%c", (bool)enable? '1': '0') < 1) {
        perrorf("%s, set new value failed", path);
        return -1;
    }

    return oldvalue;
}

int ftrace_tracer_set(const char* new, char* old)
{
    int ret = -1;
    char path[MAX_PATH] = {'\0'};
    FILE* tracer_fp = NULL;

    if (!new) {
        errormsg("invalid input, no tracer specified");
        return -1;
    }

    if (ftrace_abs_path("tracing/current_tracer", path) == NULL) {
        return -1;
    }

    if ((tracer_fp = fopen(path, "w+")) == NULL) {
        perrorf("open %s failed", path);
        goto returning;
    }

    if (old) {
        if (fscanf(tracer_fp, "%s\n", old) < 1) {
            perrorf("get orginal tracer name failed");
            goto returning;
        }
        rewind(tracer_fp);
    }

    if (fprintf(tracer_fp, "%s\n", new) < 0) {
        perrorf("set new tracer name(%s) failed", new);
        goto returning;
    }

    ret = 0;
returning:
    if (tracer_fp) {
        fclose(tracer_fp);
        tracer_fp = NULL;
    }
    return ret;
}

int ftrace_tracelog(const char* fmt, ...)
{
    int ret = -1;
    va_list valist;
    char path[MAX_PATH] = {'\0'};

    if (!fmt) {
        errormsg("invalid input, no string specified");
        return -1;
    }

    if (!trace_marker_fp) {
        if (ftrace_abs_path("tracing/trace_marker", path) == NULL) {
            return -1;
        }

        if ((trace_marker_fp = fopen(path, "a+")) == NULL) {
            perrorf("open %s failed", path);
            return -1;
        }
    }

    va_start(valist, fmt);

    if ((ret = vfprintf(trace_marker_fp, fmt, valist)) < 0) {
        perrorf("mark print error");
    }
 
    va_end(valist);
    return ret;
}

int ftrace_pid_filter_add(const pid_t* newpid)
{
    char path[MAX_PATH+1] = {'\0'};
    FILE* fp = NULL;
    int ret = -1;

    if (!newpid) {
        errormsg("invalid input, no pid specified");
        return -1;
    }

    if (ftrace_abs_path("tracing/set_ftrace_pid", path) == NULL) {
        return -1;
    }

    if ((fp = fopen(path, "a+")) == NULL) {
        perrorf("open %s failed", path);
        return -1;
    }

    if (fprintf(fp, "%ld", (long int)(*newpid)) < 0) {
        perrorf("add new pid to filter failed");
        goto returning;
    }

    ret = 0;
returning:
    if (fp) {
        fclose(fp);
        fp = NULL;
    }
    return ret;
}

static int ftrace_clear_file(const char* whichfile)
{
    char path[MAX_PATH+1] = {'\0'};
    FILE* fp = NULL;
    assert(not_empty(whichfile));

    if (ftrace_abs_path(whichfile, path) == NULL) {
        return -1;
    }

    if ((fp = fopen(path, "w")) == NULL) {
        perrorf("open %s failed", path);
        return -1;
    }

    fclose(fp);
    return 0;
}

int ftrace_pid_filter_clear(void)
{
    return ftrace_clear_file("tracing/set_ftrace_pid");
}

int ftrace_tracelog_clear(const char* trace)
{
    const char* whichtrace = not_empty(trace)? trace: "tracing/trace";
    return ftrace_clear_file(whichtrace);
}

void ftrace_close(void)
{
    if (tracing_on_fp) {
        fclose(tracing_on_fp);
        tracing_on_fp = NULL;
    }
    if (trace_marker_fp) {
        fclose(trace_marker_fp);
        trace_marker_fp = NULL;
    }
}

