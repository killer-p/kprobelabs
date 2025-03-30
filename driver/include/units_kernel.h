#ifndef KPROBELABS_H
#define KPROBELABS_H

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
#endif