# KProbeLabs

## 1.brief
This is a Linux source code learning project which is based on luckfox-pico min B arm soc board.
Also it can be used on other arm soc board.

## 2.download

you need to get https://github.com/LuckfoxTECH/luckfox-pico first,and build it.

```bash
git clone https://github.com/LuckfoxTECH/luckfox-pico.git

cd luckfox-pico
./build.sh lunch
./build.sh

cd sysdrv/source/kernel
make luckfox_rv1106_linux_defconfig
bear -- make -j8
```

then clone the project: 

```bash
git clone https://github.com/killer-p/kprobelabs.git
```

## 3.usage

firtstly, you can source the environment using the following command:
```bash
vim scripts/setup.sh
# modify the following line to your own path
export PATH=/home/prx/project/luckfox-pico/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin:$PATH
export KDIR=/home/prx/project/luckfox-pico/luckfox-pico/sysdrv/source/objs_kernel
export LUCKFOX_SDK_DIR=/home/prx/project/luckfox-pico/luckfox-pico/

# the source the setup.sh
source scripts/setup.sh
```
the setup.sh will set the environment variable and many useful commond for you.

for example:
```bash
prx@ubuntu24:~/project/luckfox-pico/luckfox-pico/kprobeslabs$ source scripts/setup.sh 
prx@ubuntu24:~/project/luckfox-pico/luckfox-pico/kprobeslabs$ help
Usage: source setup.sh,then input help
support cmds:
connect
scp_to [src] [dst]
scp_from [src] [dst]
prx@ubuntu24:~/project/luckfox-pico/luckfox-pico/kprobeslabs$ 
```

then build the project:
```bash
make all
```

the output file is in app/kprobeslabs and driver/kprobeslabs.ko