#ifndef KPROBELABS_H
#define KPROBELABS_H

#include <linux/poll.h>
#include <linux/wait.h>

typedef int (*pKprobeLabsFunc)(void *arg);
typedef int (*pKprobeLabsUnitInit)(void);
typedef int (*pKprobeLabsUnitDeinit)(void);

struct KprobeLabsUnit {
    pKprobeLabsFunc func;
    pKprobeLabsUnitInit init;
    pKprobeLabsUnitDeinit deinit;
};

int kmallocUnit(void *arg);
int dumpBacktraceUnit(void *arg);
int procInit(void);
int procExit(void);
int pollInit(void);
int pollExit(void);
int pollUnit(void *arg);
unsigned int KProbeLabsPoll(struct file *file, poll_table *wait);
int pollUnit(void *arg);

#endif