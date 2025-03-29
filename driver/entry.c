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
static pKprobeLabsFunc KProbeLabsFuncs[] = {
    KmallocUnit,
    DumpBacktraceUnit,
    ProcUnit,
};

static long KProbeLabsIoctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    size_t len = _IOC_SIZE(cmd);
    int funIndex = _IOC_NR(cmd);
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

    if (funIndex < 0 || funIndex >= sizeof(KProbeLabsFuncs) / sizeof(pKprobeLabsFunc))
    {
        printk(KERN_WARNING "KProbeLabsIoctl: funIndex out of range\n");
        return -EINVAL;
    }
    return KProbeLabsFuncs[funIndex]((void*)param);
}

static ssize_t KProbeLabsRead(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    const char *message = "Hello from KProbeLabs device!\n";
    int message_size = strlen(message);
    
    if (copy_to_user(buffer, message, message_size))
        return -EFAULT;

    return message_size;
}

static struct file_operations KProbeLabsFops = {
    .read = KProbeLabsRead,
    .unlocked_ioctl = KProbeLabsIoctl,
};

static int __init KProbeLabsInit(void)
{
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

    printk(KERN_INFO "Device node created at /dev/%s\n", DEVICE_NAME);
    return 0;
}

static void __exit KProbeLabsDeinit(void)
{
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
