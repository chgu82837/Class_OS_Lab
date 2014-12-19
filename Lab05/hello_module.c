#include <linux/module.h>

int init_module(void)
{
    printk(KERN_INFO "PastLeo Hello module inserts OK!\n");
    printk(KERN_INFO "======================== Kernel Module TESTING START ========================\n");
    return 0;
}

void cleanup_module(void){
    printk(KERN_INFO "Hello module removed!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OSLAB_PastLeo");
MODULE_DESCRIPTION("OSLAB_MODULE");
