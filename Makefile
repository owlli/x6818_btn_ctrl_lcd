#这里要写内核源码绝对路径
LINUX_PATH=/home/lzh/Desktop/s5p6818_study/Linux/src/linux-3.4

obj-m += my_buttoncloselcd.o

all:
	make -C $(LINUX_PATH) M=`pwd` modules

clean:
	make -C $(LINUX_PATH) M=`pwd` modules clean
	

