/*
 * @desc: implement the init and exit point for hello_api.ko module.
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Clymber Loong");
MODULE_DESCRIPTION("A hello world to export kernel symbols.");

static int hello_init(void)
{
    printk(KERN_INFO "[hello_api] Hello, World!\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_INFO "[hello_api] Bye bye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
