# KDIR:=/opt/clanton-full/1.4.2/sysroots/i586-poky-linux/usr/src/kernel
# PWD:= $(shell pwd)
# PATH=${PATH}:/home/Gen2/IoT_downloads/iotdk-ide-linus//devkit-x86/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux/

ifeq ($(EXECUTION_ENV),GALILEO2)
	CC=i586-poky-linux-gcc
else
	CC=gcc
endif

IOT_HOME = /opt/iot-devkit/1.7.2/sysroots/sysroots
PATH := $(PATH):$(IOT_HOME)/x86_64-pokysdk-linux/usr/bin/i586-poky-linux
#CC = i586-poky-linux-gcc
ARCH = x86
CROSS_COMPILE = i586-poky-linux-
SROOT=$(IOT_HOME)/i586-poky-linux/

APP1 = rgbled_1
APP2 = rgbled_2
APP3 = unexport

all:
	echo my new PATH is ${PATH}
	$(CC) -pthread -Wall -o $(APP1) --sysroot=$(SROOT) RGBled_1.c 
	$(CC) -pthread -Wall -o $(APP2) --sysroot=$(SROOT) RGBled_2.c
	$(CC) -pthread -Wall -o $(APP3) --sysroot=$(SROOT) Unexport.c 

clean:
	rm -f *.o
	rm -f $(APP1) 
	rm -f $(APP2) 
	rm -f $(APP3)
	
