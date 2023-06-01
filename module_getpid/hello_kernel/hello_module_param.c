#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

static int read_mypid(char* buff, const struct kernel_param* kp)
{
    return sprintf(buff, "%d", current->pid);
}

static const struct kernel_param_ops mypid_ops = {
    .get = read_mypid
};

module_param_cb(mypid, &mypid_ops, NULL, 0444);
MODULE_PARM_DESC(mypid, "get my process id");
