#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "units_user.h"

static void ProcHelp() {
    printf("Usage: proc [0/1]\n");
    printf("create /proc/kprobelabs for enable/disable\n");
}

int procUnit(int argc, char *argv[], int fd) {
    int bInit;

    if (argc < 3) 
    {
        ProcHelp();
        return 1;
    }
    bInit = atoi(argv[2]);
    if (ioctl(fd, KPROBELABS_IOCTL_PROC, &bInit) < 0)
    {
        perror("KPROBELABS_IOCTL_PROC return error");
        return 1;
    }
    return 0;
}