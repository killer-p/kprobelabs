#include <linux/slab.h>
#include <linux/gfp.h>

int KmallocUnit(void *arg)
{
    void *ptr;
    int size = *(int *)arg;
    printk("KmallocUnit, size = %d\n", size);
    if (size <= 0)
        return -1;

    ptr = (void*)kmalloc(size, GFP_KERNEL);
    if(ptr == NULL)
        return -1;
    kfree(ptr);

    return 0;
}