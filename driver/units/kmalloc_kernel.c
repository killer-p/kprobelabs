#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/list.h>
#include "../../include/kprobelabs_common.h"
#include "linux/printk.h"

struct kmalloc_obj
{
    struct list_head list;
    int size;
};

static struct list_head kmalloc_objs_list;

int kmalloc_unit_init(void)
{
    INIT_LIST_HEAD(&kmalloc_objs_list);
    return 0;
}

int kmalloc_unit_deinit(void)
{
    struct kmalloc_obj *kmalloc_obj, *tmp;
    list_for_each_entry_safe(kmalloc_obj, tmp, &kmalloc_objs_list, list)
    {
        list_del(&kmalloc_obj->list);
        kfree(kmalloc_obj);
    }
    return 0;
}

int kmalloc_unit(void *arg)
{
    struct kmalloc_unit_args *args = (struct kmalloc_unit_args *)arg;
    struct kmalloc_obj *kmalloc_obj, *tmp;

    if (args->bMalloc)
    {
        if (args->size < sizeof(struct kmalloc_obj))
        {
            printk("Error, size < sizeof(struct kmalloc_obj)=%d\n", sizeof(struct kmalloc_obj));
            return -1;
        }
        kmalloc_obj = kmalloc(args->size, GFP_KERNEL);
        if (kmalloc_obj == NULL)
            return -1;
        kmalloc_obj->size = args->size;
        list_add(&kmalloc_obj->list, &kmalloc_objs_list);
        printk("kmalloc success, size = %d, ptr = 0x%p\n", kmalloc_obj->size, kmalloc_obj);
    }
    else if (args->size >= sizeof(struct kmalloc_obj))
    {
        list_for_each_entry_safe(kmalloc_obj, tmp, &kmalloc_objs_list, list)
        {
            if (kmalloc_obj->size == args->size)
            {
                list_del(&kmalloc_obj->list);
                kfree(kmalloc_obj);
                printk("kfree success, size = %d, ptr = 0x%p\n", kmalloc_obj->size, kmalloc_obj);
                break;
            }
        }
    }
    else {
        printk("Error, bMalloc = %d\n", args->bMalloc);
        return -1;
    }

    return 0;
}