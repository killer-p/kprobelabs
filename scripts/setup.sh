#!/bin/bash

# 设置交叉编译环境变量
export ARCH=arm
export CROSS_COMPILE=arm-rockchip830-linux-uclibcgnueabihf-
export PATH=/home/prx/project/luckfox-pico/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin:$PATH
export KDIR=/home/prx/project/luckfox-pico/luckfox-pico/sysdrv/source/objs_kernel
export LUCKFOX_SDK_DIR=/home/prx/project/luckfox-pico/luckfox-pico/


# 动态获取以 enx 开头的网卡名称，并只保留数字和字母字符
get_enx_interfaces() {
    ip a | grep '^[0-9]\+:' | grep -o 'enx[0-9a-fA-F:]*' | sed 's/[^a-zA-Z0-9]//g'
}

connect() {
    enx_interfaces=($(get_enx_interfaces))
    echo "confing network..."
    sudo ip addr add 172.32.0.100/24 dev ${enx_interfaces}
    sudo ip link set ${enx_interfaces} up
    echo "Connecting to ARM board..."
    ssh root@172.32.0.93
}

cp_to() {
    echo "scp $1 root@172.32.0.93:$2"
    scp $1 root@172.32.0.93:$2
}

cp_from() {
    echo "scp -r root@172.32.0.93:$1 $2"
    scp -r root@172.32.0.93:$1 $2
}

help(){
    echo "Usage: source setup.sh,then input help"
    echo "support cmds:"
    echo "connect"
    echo "scp_to [src] [dst]"
    echo "scp_from [src] [dst]"
}

