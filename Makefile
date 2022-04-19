#
# VNPT Technology JSC.
#
# VNPT-Technology implement
# 

# ROOT = $(shell pwd)/../../../..
# CROSS_TARGET ?= $(ROOT)/toolchain/rsdk-6.5.0-5281-EL-4.9-u1.0-m32fut-191025p1/bin/mips-linux
# CROSS_COMPILE ?= $(CROSS_TARGET)-

# DIR_TMPFS:= $(shell pwd)/../../host/mipsel-buildroot-linux-uclibc/sysroot/usr

# CC = $(CROSS_COMPILE)gcc

# RM = rm -rf

# CFLAGS := -I$(DIR_TMPFS)/include
# DFLAGS := -L$(DIR_TMPFS)/lib -lm -lpthread -ljson-c

# SRC = $(shell pwd)
# src = $(wildcard $(SRC)/*.c)
# obj = $(src:.c=.o)
# INC_FILES := controlCam.h

# TARGET = controlCam

# $(SRC)/%.o: %.c $(INC_FILES)
# 	@echo $(CFLAGS)
# 	$(CC) -Wall -c $< -o $@ $(CFLAGS) $(DFLAGS)

# $(TARGET): $(obj)
# 	$(CC) $(CFLAGS) $^ -o controlCam $(DFLAGS) 

# .PHONY: clean

# clean:
# 	$(RM) $(TARGET) *.o
	
client.o: testClient.c controlCam.h
	gcc -ljson-c -c testClient.c

controlCam.o: controlCam.c controlCam.h
	gcc -ljson-c -c controlCam.c

client: testClient.o controlCam.o
	gcc testClient.o controlCam.o -ljson-c -o client


server.o: testServer.c controlCam.h
	gcc -ljson-c -c testServer.c

controlCam.o: controlCam.c controlCam.h
	gcc -ljson-c -c controlCam.c

server: testServer.o controlCam.o
	gcc testServer.o controlCam.o -ljson-c -o server