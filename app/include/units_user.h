#ifndef _KPROBELABS_UNITS_USER_H
#define _KPROBELABS_UNITS_USER_H

#include "kprobelabs_common.h"
typedef int (*unit_func)(int argc, char *argv[], int fd);

typedef struct
{
    unit_func UnitFunc;
    char UnitName[64];
} UnitDesc;

int kmalloc_unit(int argc, char *argv[], int fd);
int dump_backtrace_unit(int argc, char *argv[], int fd);
int poll_unit(int argc, char *argv[], int fd);

#endif
