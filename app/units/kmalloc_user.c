#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "units_user.h"

static void kmallocHelp() {
    printf("Usage: kmalloc [size]\n");
    printf("Allocate memory of size [size] bytes\n");
}

int kmallocUnit(int argc, char *argv[], int fd) {
    int size;

    if (argc < 3) 
    {
        kmallocHelp();
        return 1;
    }
    size = atoi(argv[2]);
    if (ioctl(fd, KPROBELABS_IOCTL_KMALLOC, &size) < 0)
    {
        perror("KPROBELABS_IOCTL_KMALLOC return error");
        return 1;
    }
    return 0;
}