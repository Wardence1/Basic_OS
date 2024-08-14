nasm -f bin -o bootloader.bin bootloader.asm
nasm -f bin -o kernel_start.bin kernel_start.asm

dd if=/dev/zero of=OS.img bs=512 count=2880

dd if=bootloader.bin of=OS.img bs=512 count=1 conv=notrunc


# Compile kernel.c into binary
bcc -ansi -0 -c -o kernel_main.o kernel.c
ld86 -0 -d kernel_main.o -o kernel_main.bin

# Add the start and main kernels together
cat kernel_start.bin kernel_main.bin > kernel.bin

dd if=kernel.bin of=OS.img bs=512 seek=1 conv=notrunc

qemu-system-i386 -drive format=raw,file=OS.img,index=0,if=floppy

