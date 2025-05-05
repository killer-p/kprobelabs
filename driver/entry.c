#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#include "../include/kprobelabs_common.h"
#include "include/units_kernel.h"

static int major_number;
static struct class *kprobelabs_class;
static struct device *kprobelabs_dev;

static struct kprobelabs_unit units[] =
{
    {kmalloc_unit, kmalloc_unit_init, kmalloc_unit_deinit},
    {dump_backtrace_unit, dump_backtrace_unit_init, dump_backtrace_unit_deinit},
    {NULL, proc_init, proc_deinit},
    {poll_unit, poll_init, poll_deinit},
};

static long kprobelabs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    size_t len = _IOC_SIZE(cmd);
    int unitIndex = _IOC_NR(cmd);
    char param[256] = {0};

    if (len > sizeof(param))
    {
        printk(KERN_WARNING "kprobelabs_ioctl: len > sizeof(param)\n");
        return -EINVAL;
    }
    if (len > 0 && copy_from_user(param, (char __user *)arg, len))
    {
        printk(KERN_WARNING "kprobelabs_ioctl: copy_from_user failed\n");
        return -EFAULT;
    }

    if (unitIndex < 0 || unitIndex >= sizeof(units) / sizeof(struct kprobelabs_unit))
    {
        printk(KERN_WARNING "kprobelabs_ioctl: funIndex out of range\n");
        return -EINVAL;
    }
    if (units[unitIndex].func)
    {
        return units[unitIndex].func((void*)param);
    }
    return -1;
}

static struct file_operations kprobelabs_fops = {
    .unlocked_ioctl = kprobelabs_ioctl,
    .poll = kprobelabs_poll,
};

static int __init kprobelabs_init(void)
{
    int i;
    major_number = register_chrdev(0, DEVICE_NAME, &kprobelabs_fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }

    kprobelabs_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(kprobelabs_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(kprobelabs_class);
    }

    kprobelabs_dev = device_create(kprobelabs_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(kprobelabs_dev)) {
        class_destroy(kprobelabs_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(kprobelabs_dev);
    }


    for (i = 0; i < sizeof(units) / sizeof(struct kprobelabs_unit); i++)
    {
        if (units[i].init != NULL)
        {
            units[i].init();
        }
    }
    printk(KERN_INFO "Device node created at /dev/%s\n", DEVICE_NAME);
    return 0;
}

static void __exit kprobelabs_deinit(void)
{
    int i;
    for (i = 0; i < sizeof(units) / sizeof(struct kprobelabs_unit); i++)
    {
        if (units[i].deinit!= NULL)
        {
            units[i].deinit();
        }
    }
    device_destroy(kprobelabs_class, MKDEV(major_number, 0));
    class_destroy(kprobelabs_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "The KProbeLabs driver has been unloaded.\n");
}

module_init(kprobelabs_init);
module_exit(kprobelabs_deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("runxin.pan");
MODULE_DESCRIPTION("A Linux kernel driver which can help you start to study linux source code.");
