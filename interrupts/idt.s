global isr_stub_table
extern exception_handler

section .text:

    %macro isr_err_stub 1
    isr_stub_%+%1:
        pusha                           ; Save all general-purpose registers
        push dword [esp + 32]           ; Push error code (from stack frame)
        push dword %1                   ; Push interrupt number
        call exception_handler          ; Call the handler
        add esp, 8                      ; Clean up the pushed arguments
        popa                            ; Restore registers
        add esp, 4                      ; Still need to remove the error code pushed by CPU
        iret
    %endmacro

    %macro isr_no_err_stub 1
    isr_stub_%+%1:
        pusha                           ; Save all general-purpose registers
        push dword 0                    ; Push a dummy error code (no error code)
        push dword %1                   ; Push interrupt number
        call exception_handler          ; Call the handler
        add esp, 8                      ; Clean up the pushed arguments
        popa                            ; Restore registers
        iret
    %endmacro

    isr_no_err_stub 0
    isr_no_err_stub 1
    isr_no_err_stub 2
    isr_no_err_stub 3
    isr_no_err_stub 4
    isr_no_err_stub 5
    isr_no_err_stub 6
    isr_no_err_stub 7
    isr_err_stub    8
    isr_no_err_stub 9
    isr_err_stub    10
    isr_err_stub    11
    isr_err_stub    12
    isr_err_stub    13
    isr_err_stub    14
    isr_no_err_stub 15
    isr_no_err_stub 16
    isr_err_stub    17
    isr_no_err_stub 18
    isr_no_err_stub 19
    isr_no_err_stub 20
    isr_no_err_stub 21
    isr_no_err_stub 22
    isr_no_err_stub 23
    isr_no_err_stub 24
    isr_no_err_stub 25
    isr_no_err_stub 26
    isr_no_err_stub 27
    isr_no_err_stub 28
    isr_no_err_stub 29
    isr_err_stub    30
    isr_no_err_stub 31

    ; Master PIC starts at 0x20, Slave PIC at 0x28
    ; Treat IRQs as exceptions without an error code
    isr_no_err_stub 32 ; IRQ 0 mapped to 0x20 (32)
    isr_no_err_stub 33 ; IRQ 1 mapped to 0x21 (33)
    isr_no_err_stub 34 ; IRQ 2 mapped to 0x22 (34)
    isr_no_err_stub 35 ; IRQ 3 mapped to 0x23 (35)
    isr_no_err_stub 36 ; IRQ 4 mapped to 0x24 (36)
    isr_no_err_stub 37 ; IRQ 5 mapped to 0x25 (37)
    isr_no_err_stub 38 ; IRQ 6 mapped to 0x26 (38)
    isr_no_err_stub 39 ; IRQ 7 mapped to 0x27 (39)
    isr_no_err_stub 40 ; IRQ 8 mapped to 0x28 (40)
    isr_no_err_stub 41 ; IRQ 9 mapped to 0x29 (41)
    isr_no_err_stub 42 ; IRQ 10 mapped to 0x2A (42)
    isr_no_err_stub 43 ; IRQ 11 mapped to 0x2B (43)
    isr_no_err_stub 44 ; IRQ 12 mapped to 0x2C (44)
    isr_no_err_stub 45 ; IRQ 13 mapped to 0x2D (45)
    isr_no_err_stub 46 ; IRQ 14 mapped to 0x2E (46)
    isr_no_err_stub 47 ; IRQ 15 mapped to 0x2F (47)

    isr_stub_table:
    %assign i 0
    %rep    48
        dd isr_stub_%+i
    %assign i i+1
    %endrep
