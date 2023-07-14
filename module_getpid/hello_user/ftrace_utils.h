#ifndef _FTRACE_UTILS_H_
#define _FTRACE_UTILS_H_
#include "hello.h"
#include <sys/types.h>
#define MAX_TRACER_STR 32

int ftrace_tracelog(const char* fmt, ...);

int ftrace_tracelog_set(int enable);

int ftrace_tracelog_clear(const char* trace);

int ftrace_tracer_set(const char* new, char* old);

int ftrace_pid_filter_add(const pid_t* newpid);

int ftrace_pid_filter_clear(void);

void ftrace_close(void);
#endif /* _FTRACE_UTILS_H_ */