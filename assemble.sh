nasm -felf32 bootloader.asm -o boot.o
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdio.c -o stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c tty.c -o tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c string.c -o string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


i686-elf-gcc -T linker.ld -o basic_os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o stdio.o tty.o string.o -lgcc


qemu-system-i386 -kernel basic_os.bin -serial stdio
