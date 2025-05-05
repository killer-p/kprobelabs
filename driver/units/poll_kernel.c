#include <linux/timer.h>
#include <linux/jiffies.h>
#include "../include/units_kernel.h"


static struct timer_list timer;
static DECLARE_WAIT_QUEUE_HEAD(poll_wait_queue);
unsigned int flag;

static void timer_cb(struct timer_list *t)
{
    printk("timer_cb\n");
    flag = 1;
    wake_up_interruptible(&poll_wait_queue);
}

int poll_init(void)
{
    timer_setup(&timer, timer_cb, 0);
    return 0;
}

int poll_deinit(void)
{
    del_timer(&timer);
    return 0;
}

int poll_unit(void *arg)
{
    unsigned int count = *(unsigned int *)arg;
    printk("pollUnit start timer\n");
    mod_timer(&timer, jiffies + msecs_to_jiffies(count));
    flag = 0;
    return 0;
}

unsigned int kprobelabs_poll(struct file *file, poll_table *wait)
{
    poll_wait(file, &poll_wait_queue, wait);
    if (flag)
    {
        flag = 0;
        return POLLOUT | POLLIN;
    }
    return 0;
}
