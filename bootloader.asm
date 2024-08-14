BITS 16
ORG 0x7C00


START:
	; initialize registers
        XOR AX, AX
        MOV DS, AX
	MOV ES, AX
	MOV SS, AX
	; initialize stack pointer
	MOV SP, 0x7C00

	; Set the kernel to load at 0x1000
	MOV AX, 0x1000
	MOV ES, AX
	XOR BX, BX
	XOR AX, AX


	; Read disk and load in the bootloader to 0x1000
	MOV AH, 0x02
	MOV AL, 0x08
	MOV CH, 0x00
	MOV CL, 0x02
	MOV DH, 0x00
	MOV DL, 0x00
	INT 0x13

	JC failed
	
	MOV SI, msg
	CALL print
	JMP done


done:
	; Jump to the kernel
        JMP 0x1000:0000
        
failed:
	MOV SI, error_msg
	CALL print
	
	CLI
	HLT
	
%include "functions.asm"

msg: DB 0x0A, "Welcome to Basic-OS", 0x0A, 0x0D, "Jackson Kidwell - 2024", 0x0A, 0x0A, 0
error_msg: DB "Error reading from disk.", 0

TIMES 510 - ($ - $$) DB 0
DW 0xAA55
