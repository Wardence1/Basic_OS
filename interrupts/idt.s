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

    isr_stub_table:
    %assign i 0 
    %rep    32 
        dd isr_stub_%+i ; use DQ instead if targeting 64-bit
    %assign i i+1 
    %endrep