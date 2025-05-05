#ifndef KPROBELABS_H
#define KPROBELABS_H

#include <linux/poll.h>
#include <linux/wait.h>

typedef int (*kprobelabs_func)(void *arg);
typedef int (*kprobelabs_unit_init)(void);
typedef int (*kprobelabs_unit_deinit)(void);

struct kprobelabs_unit {
    kprobelabs_func func;
    kprobelabs_unit_init init;
    kprobelabs_unit_deinit deinit;
};

int kmalloc_unit(void *arg);
int kmalloc_unit_init(void);
int kmalloc_unit_deinit(void);

int dump_backtrace_unit(void *arg);
int dump_backtrace_unit_init(void);
int dump_backtrace_unit_deinit(void);

int proc_init(void);
int proc_deinit(void);

int poll_init(void);
int poll_deinit(void);
int poll_unit(void *arg);
unsigned int kprobelabs_poll(struct file *file, poll_table *wait);

#endif