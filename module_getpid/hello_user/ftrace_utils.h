#ifndef _FTRACE_UTILS_H_
#define _FTRACE_UTILS_H_
#include "hello.h"
#include <sys/types.h>
#define MAX_TRACER_STR 32

char ftrace_set_tracing(const char value);

int ftrace_set_tracer(const char* new, char* old);

int ftrace_pid_add(const pid_t* newpid);

int ftrace_pid_reset(void);

int ftrace_marker(const char* fmt, ...);

void ftrace_close(void);
#endif /* _FTRACE_UTILS_H_ */