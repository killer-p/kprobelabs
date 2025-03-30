#include <linux/slab.h>
#include <linux/gfp.h>
#include "../../include/kprobelabs_common.h"
#include "linux/printk.h"

static void *ptr;

int kmallocUnit(void *arg)
{
    struct kmallocArgs *p = (struct kmallocArgs *)arg;

    if (p->bMalloc && ptr == NULL)
    {
        ptr = kmalloc(p->size, GFP_KERNEL);
        if (ptr == NULL)
            return -1;
        printk("kalloc size = %d\n", p->size);
    }
    else if (p->bMalloc == 0 && ptr != NULL) {
        kfree(ptr);
        ptr = NULL;
        printk("kfree success\n");
    }
    else {
        printk("Error, bMalloc = %d, ptr = %p\n", p->bMalloc, ptr);
        return -1;
    }

    return 0;
}