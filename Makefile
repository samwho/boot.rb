CC	:= clang
AS := nasm
LD := ld
QEMU := qemu-system-i386
SOURCE_SUFFIXES := '(' -name '*.c' -o -name '*.s' ')'
SRCFILES  := $(shell find 'src' ${SOURCE_SUFFIXES})
TESTFILES  := $(shell find 'src/test' ${SOURCE_SUFFIXES})
OBJFILES := $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(SRCFILES) $(TESTFILES)))
CFLAGS := -std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -Iinclude -Imruby/include -m32 -O0 -mno-sse -Wextra
LDFLAGS := -nostdlib -g -melf_i386
ASFLAGS := -felf32 -g

.PHONY: all clean qemu mruby mruby-clean clean-all kernel.bin-real generate-kernel-irb-file

all: os.iso

qemu: os.iso
	@$(QEMU) -cdrom os.iso -monitor stdio

os.iso: kernel.bin
	@mkdir -p isofs/System
	cp $< isofs/System
	cp isofs/boot/grub/stage2_eltorito isofs/boot/grub/stage2_eltorito.copy
	mkisofs -R -b boot/grub/stage2_eltorito.copy -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o $@ isofs
	rm isofs/boot/grub/stage2_eltorito.copy

# Ew.
kernel.bin: generate-kernel-irb-file ${OBJFILES} mruby kernel.bin-real
kernel.bin-real: ${OBJFILES}
	${LD} ${LDFLAGS} -T src/linker.ld -o kernel.bin $^ $(shell find 'mruby/build/boot.rb' -name '*.o')

%.o: %.c @${CC} ${CFLAGS} -MMD -MP -MT "$*.d $*.o"	-c $< -o $@
%.o: %.s @${AS} ${ASFLAGS} -o $@ $<

generate-kernel-irb-file:
	git submodule update --init && ./generate-kernel-irb-file.sh

mruby: mruby/build/boot.rb
mruby/build/boot.rb:
	(git submodule update --init && cd mruby && TARGET=boot.rb MRUBY_CONFIG=../boot.rb ./minirake clean all)

clean:
	$(RM) $(wildcard $(OBJFILES) kernel.bin os.iso)

mruby-clean:
	(cd mruby && TARGET=boot.rb MRUBY_CONFIG=../boot.rb ./minirake clean)

clean-all: clean mruby-clean
