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
static struct class *KProbeLabsClass;
static struct device *KProbeLabsDevice;

static struct KprobeLabsUnit units[] =
{
    {kmallocUnit, NULL, NULL},
    {dumpBacktraceUnit, NULL, NULL},
    {NULL, procInit, procInit},
};

static long KProbeLabsIoctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    size_t len = _IOC_SIZE(cmd);
    int unitIndex = _IOC_NR(cmd);
    char param[256] = {0};

    if (len > sizeof(param))
    {
        printk(KERN_WARNING "KProbeLabsIoctl: len > sizeof(param)\n");
        return -EINVAL;
    }
    if (len > 0 && copy_from_user(param, (char __user *)arg, len))
    {
        printk(KERN_WARNING "KProbeLabsIoctl: copy_from_user failed\n");
        return -EFAULT;

    }

    if (unitIndex < 0 || unitIndex >= sizeof(units) / sizeof(struct KprobeLabsUnit))
    {
        printk(KERN_WARNING "KProbeLabsIoctl: funIndex out of range\n");
        return -EINVAL;
    }
    return units[unitIndex].func((void*)param);
}

static struct file_operations KProbeLabsFops = {
    .unlocked_ioctl = KProbeLabsIoctl,
};

static int __init KProbeLabsInit(void)
{
    int i;
    major_number = register_chrdev(0, DEVICE_NAME, &KProbeLabsFops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }

    KProbeLabsClass = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(KProbeLabsClass)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(KProbeLabsClass);
    }

    KProbeLabsDevice = device_create(KProbeLabsClass, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(KProbeLabsDevice)) {
        class_destroy(KProbeLabsClass);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(KProbeLabsDevice);
    }


    for (i = 0; i < sizeof(units) / sizeof(struct KprobeLabsUnit); i++)
    {
        if (units[i].init != NULL)
        {
            units[i].init();
        }
    }
    printk(KERN_INFO "Device node created at /dev/%s\n", DEVICE_NAME);
    return 0;
}

static void __exit KProbeLabsDeinit(void)
{
    int i;
    for (i = 0; i < sizeof(units) / sizeof(struct KprobeLabsUnit); i++)
    {
        if (units[i].deinit!= NULL)
        {
            units[i].deinit();
        }
    }
    device_destroy(KProbeLabsClass, MKDEV(major_number, 0));
    class_destroy(KProbeLabsClass);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "The KProbeLabs driver has been unloaded.\n");
}

module_init(KProbeLabsInit);
module_exit(KProbeLabsDeinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("runxin.pan");
MODULE_DESCRIPTION("A Linux kernel driver which can help you start to study linux source code.");
