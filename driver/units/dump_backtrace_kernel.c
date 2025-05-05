#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int dump_backtrace_unit_init(void)
{
    return 0;
}

int dump_backtrace_unit_deinit(void)
{
    return 0;
}

extern void sched_show_task(struct task_struct *p);

int dump_backtrace_unit(void *arg)
{
    struct task_struct *task;
    printk("dump_backtrace_unit\n");

    for_each_process(task) {
        sched_show_task(task);
    }
    return 0;
}