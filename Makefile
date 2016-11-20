CC=arm-linux-gnueabi-gcc
CFLAGS=-ansi -pedantic -Wall -Wextra -march=armv6 -msoft-float -fPIC -mapcs-frame
LD=arm-linux-gnueabi-ld
LDFLAGS=-N -Ttext=0x10000

.SUFFIXES: .o .elf
.o.elf:
	$(LD) $(LDFLAGS) -o $@ $^
