; @todo get this to work

global loadIdt
global isr_stub
global keyboard_handler_stub
extern isr_handler    ; Declare the C isr_handler function
extern key_test

section .text


    loadIdt:
        mov eax, [esp + 4]  ; Load the address of the IDT pointer
        lidt [eax]          ; Load the IDT with the pointer
        ret


    isr_stub:
        pusha                   ; Save all general-purpose registers
        push ds                 ; Save data segment
        push es                 ; Save extra segment
        push fs                 ; Save FS segment
        push gs                 ; Save GS segment

        mov ax, 0x10            ; Kernel data segment selector
        mov ds, ax              ; Load it into DS
        mov es, ax              ; Load it into ES
        mov fs, ax              ; Load it into FS
        mov gs, ax              ; Load it into GS

        push dword [esp + 32]   ; Push interrupt number onto the stack
        call isr_handler        ; Call the C handler

        add esp, 4              ; Clean up the stack (remove interrupt number)
        pop gs                  ; Restore GS
        pop fs                  ; Restore FS
        pop es                  ; Restore ES
        pop ds                  ; Restore DS
        popa                    ; Restore general-purpose registers
        iret                    ; Return from interrupt
 
    keyboard_handler_stub:
    pusha                  ; Save general-purpose registers
    push ds                ; Save data segment register
    push es                ; Save extra segment register
    push fs                ; Save FS segment register
    push gs                ; Save GS segment register

    mov ax, 0x10           ; Load kernel data segment selector
    mov ds, ax             ; Set DS register
    mov es, ax             ; Set ES register
    mov fs, ax             ; Set FS register
    mov gs, ax             ; Set GS register

    call key_test  ; Call the C function to handle the interrupt

    pop gs                 ; Restore GS segment register
    pop fs                 ; Restore FS segment register
    pop es                 ; Restore extra segment register
    pop ds                 ; Restore data segment register
    popa                   ; Restore general-purpose registers

    iret                   ; Return from interrupt