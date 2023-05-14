/*
 * @desc: verify the symbol exported by module 'hello_api'
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Clymber Loong");
MODULE_DESCRIPTION("A demo to invoke symbols that other modules exported.");

extern void api_test(void); // from hello_api.ko

static int hello_init(void)
{
    printk(KERN_INFO "[hello_feature] Hello, World!\n");
    api_test();
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_INFO "[hello_feature] Bye Bye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
