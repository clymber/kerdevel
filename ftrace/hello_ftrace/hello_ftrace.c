#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Clymber Loong");
MODULE_DESCRIPTION("A Hellow World of Ftrace");

static int hello_init(void)
{
    tracing_on();
    trace_printk("Hello, Ftrace!\n");
    tracing_off();
    return 0;
}

static void hello_exit(void)
{
    tracing_on();
    trace_printk("Good bye, Ftrace!\n");
    tracing_off();
}

module_init(hello_init);
module_exit(hello_exit);
