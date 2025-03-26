#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "units_user.h"

int dumpBacktraceUnit(int argc, char *argv[], int fd)
{
    if (ioctl(fd, KPROBELABS_IOCTL_DUMP_BACKTRACE, NULL) < 0)
    {
        perror("KPROBELABS_IOCTL_DUMP_BACKTRACE return error");
        return 1;
    }
    return 0;
}