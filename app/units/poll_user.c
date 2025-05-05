#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <unistd.h>
#include "units_user.h"

static void unit_help() {
    printf("Usage: poll [timeout_ms]\n");
}

int poll_unit(int argc, char *argv[], int fd) {
    struct pollfd fds[1];
    int timeout_ms;
    int ret;

    if (argc < 3) {
        unit_help();
        return 1;
    }
    timeout_ms = atoi(argv[2]);
    if (timeout_ms < 0) {
        unit_help();
        return 1;
    }
    if (ioctl(fd, KPROBELABS_IOCTL_POLL, &timeout_ms) < 0)
    {
        perror("KPROBELABS_IOCTL_PROC return error");
        return 1;
    }

    fds[0].fd = fd;
    fds[0].events = POLLIN | POLLOUT;
    ret = poll(fds, 1, -1);
    if (ret > 0)
    {
        if (fds[0].revents & POLLIN)
        {
            printf("POLLIN\n");
        }
        if (fds[0].revents & POLLOUT)
        {
            printf("POLLOUT\n");
        }
    }
    else if (ret == 0){
        printf("Timeout\n");
    }
    else
    {
        perror("poll() return error");
    }

    return 0;
}