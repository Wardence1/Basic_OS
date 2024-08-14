BITS 16


; Set up data segment
mov ax, cs      ; Use CS as the base for DS
mov ds, ax
mov es, ax

; Clear the BSS section
mov di, __bss_start
mov cx, __bss_end
sub cx, di
xor al, al
rep stosb


;MOV SI, msg
;CALL print


; Jump to the kernel
JMP end

; If kernel_main returns, halt the system
cli
hlt

msg: db "Hello", 0

%include "functions.asm"

section .bss
__bss_start:
    resb 4096  ; Reserve 4KB for BSS
__bss_end:

end:

