#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

// need to export show_stack in kernel source code:EXPORT_SYMBOL_GPL(show_stack);
//extern void show_stack(struct task_struct *tsk, unsigned long *sp, const char *loglvl);

int dumpBacktraceUnit(void *arg)
{
    struct task_struct *task;
    printk("DumpBacktraceUnit\n");

    for_each_process(task) {
        //show_stack(task, NULL, KERN_WARNING);
    }
    return 0;
}