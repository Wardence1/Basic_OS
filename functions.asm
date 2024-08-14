BITS 16

; Move si to the string first
print:
    push ax
    push si

.loop:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 0x10
    jmp .loop

.done:
    mov al, 0x0D  ; Carriage return
    mov ah, 0x0E
    int 0x10
    mov al, 0x0A  ; Line feed
    mov ah, 0x0E
    int 0x10

    pop si
    pop ax
    ret