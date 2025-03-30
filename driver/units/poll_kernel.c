#include <linux/timer.h>
#include <linux/jiffies.h>
#include "../include/units_kernel.h"


static struct timer_list timer;
static DECLARE_WAIT_QUEUE_HEAD(poll_wait_queue);
unsigned int flag;

static void timerCallback(struct timer_list *t)
{
    printk("timerCallback\n");
    flag = 1;
    wake_up_interruptible(&poll_wait_queue);
}

int pollInit(void)
{
    timer_setup(&timer, timerCallback, 0);
    return 0;
}

int pollExit(void)
{
    del_timer(&timer);
    return 0;
}

int pollUnit(void *arg)
{
    unsigned int count = *(unsigned int *)arg;
    printk("pollUnit start timer\n");
    mod_timer(&timer, jiffies + msecs_to_jiffies(count));
    flag = 0;
    return 0;
}

unsigned int KProbeLabsPoll(struct file *file, poll_table *wait)
{
    poll_wait(file, &poll_wait_queue, wait);
    if (flag)
    {
        flag = 0;
        return POLLOUT | POLLIN;
    }
    return 0;
}
