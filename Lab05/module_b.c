#include <linux/module.h>

#define MOD_NAME "OSLAB_module_b"

int v = 56;

extern int f(int);

EXPORT_SYMBOL(v);

int init_module(void)
{
    printk(KERN_INFO "PastLeo %s inserts OK!\n",MOD_NAME);
    printk(KERN_INFO "======================\n");
    printk(KERN_INFO "v=%d, f(v)=%d.",v,f(v));
    printk(KERN_INFO "======================\n");
    return 0;
}

void cleanup_module(void){
    printk(KERN_INFO "%s removed!\n",MOD_NAME);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OSLAB_PastLeo");
MODULE_DESCRIPTION(MOD_NAME);
