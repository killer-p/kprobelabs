#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "units_user.h"

static void unit_help() {
    printf("Usage: kmalloc [bmalloc] [size]\n");
    printf("Allocate/free memory of [size] bytes\n");
}

int kmalloc_unit(int argc, char *argv[], int fd) {
    struct kmalloc_unit_args kmalloc = {0};

    if (argc < 3) 
    {
        unit_help();
        return 1;
    }
    kmalloc.bMalloc = atoi(argv[2]);
    kmalloc.size = atoi(argv[3]);
    if (ioctl(fd, KPROBELABS_IOCTL_KMALLOC, &kmalloc) < 0)
    {
        perror("KPROBELABS_IOCTL_KMALLOC return error");
        return 1;
    }
    return 0;
}