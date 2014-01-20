CC = gcc
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}
CFLAGS = -Wall -m32 -ffreestanding
LFLAGS = -melf_i386 -Ttext 0x1000 --oformat binary

all: os-image

run: all
	qemu-system-i386 -hda os-image

os-image: boot.bin kernel.bin
	cat $^ > os-image

kernel/kernel_entry.o : kernel/kernel_entry.asm
	nasm $< -f elf -o $@

boot.bin: boot/boot.asm
	nasm $< -f bin -o $@

kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld ${LFLAGS} -o $@ $^

${OBJ} : ${C_SOURCES} ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.bin *.dis *.o os-image
	rm -rf kernel/*.o boot/*.bin drivers/*.o16bit/I
