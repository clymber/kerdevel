#ifndef _MOUNTS_UTILS_H_
#define _MOUNTS_UTILS_H_
#define MOUNTS_LIST "/proc/mounts"

/*
 * @desc: find the path of debugfs.
 * @return: the absolute path of debugfs on success, NULL on error.
*/
const char *find_debugfs(void);

/*
 * @desc: find the path of sysfs.
 * @return: the absolute path of sysfs on success, NULL on error.
*/
const char *find_sysfs(void);

#endif /* _MOUNTS_UTILS_H_ */