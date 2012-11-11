CC	:= clang
AS := nasm
LD := ld
QEMU := qemu
SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.s' ')'
SRCFILES  := $(shell find 'src' ${SOURCE_SUFFIXES})
OBJFILES := $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRCFILES)))
CFLAGS := -std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -Iinclude -m32
LDFLAGS := -nostdlib -g -melf_i386
ASFLAGS := -felf32 -g
.PHONY: all clean qemu

all: os.iso

qemu:
	@$(QEMU) -cdrom os.iso -monitor stdio

os.iso: kernel.bin
	@mkdir -p isofs/System
	cp $< isofs/System
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -boot-info-table -o $@ isofs

kernel.bin: ${OBJFILES} 
	${LD} ${LDFLAGS} -T src/linker.ld -o $@ $^
%.o: %.c @${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"	-c $< -o $@
%.o: %.asm @${ASM} ${ASFLAGS} -o $@ $<

clean:
	$(RM) $(wildcard $(OBJFILES) kernel.bin os.iso)
