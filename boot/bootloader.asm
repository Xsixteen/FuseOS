[BITS 16]       ; 16 bit code generation
[ORG 0x7C00]	; Origin of the program. (Start position)

; End matter
times 510-($-$$) db 0
dw 0xAA55
