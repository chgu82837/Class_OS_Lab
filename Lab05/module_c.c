#include <linux/module.h>

#define MOD_NAME "OSLAB_module_c"

extern int v;
extern int f(int);
int v_new = 0;

module_param(v_new,int,0);
MODULE_PARM_DESC(v_new,"a parameter overwritting origin variable v.");

int init_module(void)
{
    printk(KERN_INFO "PastLeo %s inserts OK!\n",MOD_NAME);
    printk(KERN_INFO "======================\n");
    printk(KERN_INFO "v=%d, f(v)=%d.",v,f(v));
    v = v_new;
    printk(KERN_INFO "v has been set to %d.\n",v);
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
