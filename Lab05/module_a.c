#include <linux/module.h>

#define MOD_NAME "OSLAB_module_a"

int f(int x){
    if (x>100)
        return 1;
    else if (x==100)
        return 0;
    else
        return -1;
}

EXPORT_SYMBOL(f);

int init_module(void)
{
    printk(KERN_INFO "PastLeo %s inserts OK!\n",MOD_NAME);
    return 0;
}

void cleanup_module(void){
    printk(KERN_INFO "%s removed!\n",MOD_NAME);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OSLAB_PastLeo");
MODULE_DESCRIPTION(MOD_NAME);
