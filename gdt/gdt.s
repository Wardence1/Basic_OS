global reloadSegments

section .text
    reloadSegments:
       ; Reload the CS register with an offset of 0x08
       jmp 0x08:.reload_CS
    .reload_CS:
       ; Reload data segment registers
       mov ax, 0x10
       mov ds, ax
       mov es, ax
       mov fs, ax
       mov gs, ax
       mov ss, ax
       ret