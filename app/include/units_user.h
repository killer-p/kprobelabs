#ifndef _KPROBELABS_UNITS_USER_H
#define _KPROBELABS_UNITS_USER_H

#include "kprobelabs_common.h"
typedef int (*pUnitFunc)(int argc, char *argv[], int fd);

typedef struct
{
    pUnitFunc UnitFunc;
    char UnitName[64];
} UnitDesc;

int kmallocUnit(int argc, char *argv[], int fd);
int dumpBacktraceUnit(int argc, char *argv[], int fd);
int procUnit(int argc, char *argv[], int fd);

#endif
