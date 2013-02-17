[BITS 32]    ; 32 bit code

[global start]
[extern kernel_main]

start:	     ; Main code label (Not really needed now but will be later)
	call kernel_main	     ; Jump to the start of the instruction 
	cli 		 	     ; Stop Interrupts
	hlt		 	     ; Halt the CPU


