TITLE Add and Subtract		(AddSub.asm)

; This program adds and subtracts 32-bit integers.

INCLUDE Irvine32.inc

.data
INCLUDE PHW01.inc

.code
main PROC
	mov	ecx, 0		;ecx = 0
	add	ecx, val1	;ecx = val1
	add	ecx, ecx	;ecx = 2*val1
	add	ecx, ecx	;ecx = 4*val1
	add	ecx, ecx	;ecx = 8*val1
	sub	ecx, val1	;ecx = 7*val1
	mov eax, 0		;eax = 0
	sub	eax, ecx	;eax = 7*val1
	mov ecx, 0		;ecx = 0
	add ecx, val2	;ecx = val2
	add ecx, ecx	;ecx = 2*val2
	add ecx, ecx	;ecx = 4*val2
	add ecx, ecx	;ecx = 8*val2
	add ecx, ecx	;ecx = 16*val2
	add ecx, val2	;ecx = 17*val2
	add eax, ecx	;eax = -7*val1 + 17*val2
	mov ecx, 0		;ecx = 0
	sub ecx, val3	;ecx = -val3
	add ecx, ecx	;ecx = -2*val3
	add ecx, ecx	;ecx = -4*val3
	add ecx, ecx	;ecx = -8*val3
	add ecx, ecx	;ecx = -16*val3
	sub ecx, val3	;ecx = -17*val3
	add eax, ecx	;eax = -7*val + 17*val2 -17*val3
	mov ecx, 0		;ecx = 0
	add ecx, val4	;ecx = val4
	add ecx, ecx	;ecx = 2*val4
	add ecx, ecx	;ecx = 4*val4
	add ecx, ecx	;ecx = 8*val4
	add ecx, ecx	;ecx = 16*val4
	add ecx, ecx	;ecx = 32*val4
	sub ecx, val4	;ecx = 31*val4
	add eax, ecx	;eax = -7*val + 17*val2 -17*val3 + 31*val4
	
	mov ecx, 0		;ecx = 0
	add ecx, val1	;ecx = val1
	add ecx, ecx	;ecx = 2*val1
	add ecx, ecx	;ecx = 4*val1
	add ecx, ecx	;ecx = 8*val1
	add ecx, ecx	;ecx = 16*val1
	add ecx, ecx	;ecx = 32*val1
	add ecx, ecx	;ecx = 64*val1
	sub ecx, val1	;ecx = 63*val1
	mov ebx, ecx	;ebx = 63*val1
	mov ecx, 0		;ecx = 0
	sub ecx, val2	;ecx = -val2
	add ecx, ecx	;ecx = -2*val2
	add ecx, ecx	;ecx = -4*val2
	add ecx, ecx	;ecx = -8*val2
	add ecx, ecx	;ecx = -16*val2
	add ecx, val2	;ecx = -15*val2
	add ebx, ecx	;ebx = 63*val1 - 15*val2
	mov ecx, 0		;ecx = 0
	add ecx, val3	;ecx = val3
	add ecx, ecx	;ecx = 2*val3
	add ecx, ecx	;ecx = 4*val3
	add ecx, ecx	;ecx = 8*val3
	add ecx, ecx	;ecx = 16*val3
	sub ecx, val3	;ecx = 15*val3
	add ebx, ecx	;eax = 63*val1 - 15*val2 + 15*val3
	mov ecx, 0		;ecx = 0
	sub ecx , val4	;ecx = -val4
	add ecx, ecx	;ecx = -2*val4
	add ecx, ecx	;ecx = -4*val4
	add ecx, ecx	;ecx = -8*val4
	add ecx, ecx	;ecx = -16*val4
	add ecx, ecx	;ecx= -32*val4
	add ecx, val4	;ecx = -31*val4
	add ebx, ecx	;eax = 63*val1 - 15*val2 + 15*val3 -31*val4

	call	DumpRegs

	exit
main ENDP
END main
