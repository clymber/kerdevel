#ifndef _HELLO_H_
#define _HELLO_H_
#include <errno.h>
#include <string.h>
#include <stdio.h>
#define MAX_PATH 256

/*
 * @desc: print an error message, including errno, to stdand error
*/
#define perrorf(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt ": %s\n", ##__VA_ARGS__, strerror(errno))

/*
 * @desc: print an simple error message, without errno.
*/
#define errormsg(fmt, ...) fprintf(stderr, "[ERROR] "fmt"\n", ##__VA_ARGS__)

/*
 * @desc: return true if the @str is not NULL and not empty
*/
#define not_empty(str) ((str != NULL) && (str[0] != '\0'))

#endif /* _HELLO_H_*/
