#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Clymber Loong");
MODULE_DESCRIPTION("A Hello, World Module");

static int   irq   = 10;
static int   debug = 0;
static char *name  = "Hello World"; 

static int hello_init(void)
{
    printk(KERN_ALERT "Hello, World! name=%s, irq=%d, debug=%d\n", name, irq, debug);
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Bye Bye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
module_param(irq, int, 0660);
module_param(debug, int, 0660);
module_param(name, charp, 0660);

MODULE_PARM_DESC(irq, "The interrupt line number.");
MODULE_PARM_DESC(debug, "Debug mode, 1 is on, 0 is off.");
MODULE_PARM_DESC(name, "Your name");
