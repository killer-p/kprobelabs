#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "kprobelabs_common.h"
#include "units_user.h"

static UnitDesc desc[] = {
    {kmallocUnit, "kmalloc"},
    {dumpBacktraceUnit, "dump_backtrace"},
    {procUnit, "proc"},
    {pollUnit, "poll"},
};

void print_usage() {
    int i;
    printf("Usage: KProbeLabs <unit>\n");
    printf("unit:\n");
    for (i = 0; i < sizeof(desc) / sizeof(UnitDesc); i++) {
        printf("\t%s\n", desc[i].UnitName);
    }
}

int main(int argc, char *argv[]) {
    int i;
    int fd;

    if (argc < 2 || strcmp(argv[1], "help") == 0) {
        print_usage();
        return 1;
    }

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        printf("open %s failed\n", DEVICE_PATH);
        return 1;
    }

    for (i = 0; i < sizeof(desc) / sizeof(UnitDesc); i++) {
        if (strcmp(argv[1], desc[i].UnitName) == 0) {
            desc[i].UnitFunc(argc, argv, fd);
            break;
        }
    }
    close(fd);
    if (i == sizeof(desc) / sizeof(UnitDesc)) {
        printf("unit %s not found\n", argv[1]);
        return 1;
    }
    return 0;
}
