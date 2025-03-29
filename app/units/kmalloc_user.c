#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "units_user.h"

static void kmallocHelp() {
    printf("Usage: kmalloc [bmalloc] [size]\n");
    printf("Allocate/free memory of [size] bytes\n");
}

int kmallocUnit(int argc, char *argv[], int fd) {
    struct kmallocArgs kmalloc = {0};

    if (argc < 3) 
    {
        kmallocHelp();
        return 1;
    }
    kmalloc.bMalloc = atoi(argv[2]);
    if (kmalloc.bMalloc)
    {
        kmalloc.size = atoi(argv[3]);
    }
    if (ioctl(fd, KPROBELABS_IOCTL_KMALLOC, &kmalloc) < 0)
    {
        perror("KPROBELABS_IOCTL_KMALLOC return error");
        return 1;
    }
    return 0;
}