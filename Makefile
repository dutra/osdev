CC = gcc
C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard include/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}
CINCLUDE = include/
CFLAGS = -Wall -m32 -ffreestanding -g -Iinclude/ # -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
LFLAGS = -melf_i386 -T kernel.ld

all: os-image

run: all
	qemu-system-i386 -hda os-image -m 128M -pidfile /tmp/amora_qemu
run-nox: all
	qemu-system-i386 -curses -hda os-image -m 128M -pidfile /tmp/amora_qemu
kill:
	cat /tmp/amora_qemu | xargs kill -15
kill9:
	cat /tmp/amora_qemu | xargs kill -9

debug: all
	qemu-system-i386 -s -S -hda os-image

os-image: boot.bin kernel.bin
	cat $^ > os-image

kernel_entry.o : kernel_entry.asm
	nasm $< -f elf -o $@

interrupts.o : interrupts.asm
	nasm $< -f elf -o $@
idt_flush.o : idt_flush.asm
	nasm $< -f elf -o $@

boot.bin: boot/boot.asm
	nasm $< -f bin -o $@

kernel.bin: kernel_entry.o  ${OBJ} idt_flush.o interrupts.o
	ld ${LFLAGS} $^ -o $@

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.bin *.dis *.o os-image
	rm -rf kernel/*.o kernel/asm/*.o boot/*.bin drivers/*.o lib/*.o
