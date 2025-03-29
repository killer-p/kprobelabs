#ifndef KPROBELABS_H
#define KPROBELABS_H

typedef int (*pKprobeLabsFunc)(void *arg);

int KmallocUnit(void *arg);
int DumpBacktraceUnit(void *arg);
int ProcUnit(void *arg);
#endif