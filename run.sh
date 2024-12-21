# Create the object files
nasm -felf32 boot.s -o build/boot.o
i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdio.c -o build/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c tty.c -o build/tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c string.c -o build/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c io/io.c -o build/io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c io/keyboard.c -o build/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c shell/shell.c -o build/shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c memory/mem.c -o build/mem.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
nasm -felf32 interrupts/idt.s -o build/idts.o
i686-elf-gcc -c interrupts/idt.c -o build/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c files/file.c -o build/file.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c gdt/gdt.c -o build/gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
nasm -felf32 gdt/gdt.s -o build/gdts.o

# Link the object files together into a .bin file
i686-elf-gcc -T linker.ld -o build/myos.bin -ffreestanding -O2 -nostdlib build/gdts.o build/gdt.o build/file.o build/idt.o build/idts.o build/mem.o build/shell.o build/boot.o build/kernel.o build/stdio.o build/tty.o build/string.o build/io.o build/keyboard.o -lgcc

# Create a fill the floppy image
#dd if=/dev/zero of=build/floppy.img bs=512 count=2880
#dd if=build/myos.bin of=build/floppy.img bs=512 count=1 conv=notrunc

# Open the .bin file with qemu
qemu-system-i386 -kernel build/myos.bin