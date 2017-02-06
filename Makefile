CC = /home/greg/esp-open-sdk/xtensa-lx106-elf/bin/xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
#LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -Wl,--end-group -lgcc
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld


blinky-0x00000.bin: blinky
	/home/greg/esp-open-sdk/esptool/esptool.py elf2image $^

blinky: blinky.o

blinky.o: blinky.c

flash: blinky-0x00000.bin
	/home/greg/esp-open-sdk/esptool/esptool.py write_flash 0 blinky-0x00000.bin 0x40000 blinky-0x40000.bin

clean:
	rm -f blinky blinky.o blinky-0x00000.bin blinky-0x40000.bin
