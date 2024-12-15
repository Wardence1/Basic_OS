# Create the object files
nasm -felf32 boot.s -o build/boot.o
i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdio.c -o build/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c tty.c -o build/tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c string.c -o build/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c io/io.c -o build/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c io/keyboard.c -o build/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c shell/shell.c -o build/shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c memory/malloc.c -o build/malloc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
nasm -felf32 interrupts/idt.s -o build/idts.o
i686-elf-gcc -c interrupts/idt.c -o build/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c files/file.c -o build/file.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


# Link the object files together into a .bin file
i686-elf-gcc -T linker.ld -o build/myos.bin -ffreestanding -O2 -nostdlib build/file.o build/idt.o build/idts.o build/malloc.o build/shell.o build/boot.o build/kernel.o build/stdio.o build/tty.o build/string.o build/io.o build/keyboard.o -lgcc


# Open the .bin file with qemu
qemu-system-i386 -kernel build/myos.bin