/*
 * @desc: implement test APIs to be exported to the kernel. 
*/
#include <linux/kernel.h>

void api_test(void)
{
    printk(KERN_INFO "[hello_api] this is a test message.");
}
EXPORT_SYMBOL_GPL(api_test);
