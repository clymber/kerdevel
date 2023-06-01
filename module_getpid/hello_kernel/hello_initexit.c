#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Clymber Loong");
MODULE_DESCRIPTION("A Hello World of Getting PID");

static int hello_init(void)
{
    trace_printk("[%s] Hello, World! My current PID: %d\n",
            module_name(THIS_MODULE), current->pid);
    return 0;
}

static void hello_exit(void)
{
    trace_printk("[%s] Bye bye, World! My current PID: %d\n",
            module_name(THIS_MODULE), current->pid);
}

module_init(hello_init);
module_exit(hello_exit);
