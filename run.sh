# Create the object files
nasm -felf32 boot.s -o build/boot.o
i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdio.c -o build/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c tty.c -o build/tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c string.c -o build/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c io/io.c -o build/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c io/keyboard.c -o build/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Link the object files together into a .bin file
i686-elf-gcc -T linker.ld -o build/myos.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/stdio.o build/tty.o build/string.o build/io.o build/keyboard.o -lgcc


# Open the .bin file with qemu
qemu-system-i386 -kernel build/myos.bin