GLOBAL cpuVendor
GLOBAL syscaller
GLOBAL outb
GLOBAL outd
GLOBAL outq
GLOBAL inb
GLOBAL ind
GLOBAL inq
GLOBAL getRax
GLOBAL int80handler
GLOBAL inpw
GLOBAL outpw

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

syscaller: 
	mov rax, rdi
	int 80h
	ret


getRax:
	ret


; void outb(uint16_t port, uint8_t value)
outb:
	push rbp
	mov rbp, rsp

	mov rdx, rdi    
	mov rax, rsi
	out dx, al  

	mov rsp, rbp
	pop rbp
	ret

; void outd(uint16_t port, uint16_t value)
outd:
	push rbp
	mov rbp, rsp

	mov rdx, rdi    
	mov rax, rsi
	out dx, ax

	mov rsp, rbp
	pop rbp
	ret

; void outq(uint16_t port, uint32_t value)
outq:
	push rbp
	mov rbp, rsp

	mov rdx, rdi    
	mov rax, rsi
	out dx, eax

	mov rsp, rbp
	pop rbp
	ret

; uint8_t inb(uint16_t port)
inb:
	push rbp
	mov rbp, rsp
	
	mov rdx, rdi
	in al, dx	

	mov rsp, rbp
	pop rbp
	ret

; uint16_t ind(uint16_t port)
ind:
	push rbp
	mov rbp, rsp
	
	mov rdx, rdi
	in ax, dx	

	mov rsp, rbp
	pop rbp
	ret
; uint32_t inq(uint16_t port)
inq:
	push rbp
	mov rbp, rsp
	
	mov rdx, rdi
	in eax, dx	

	mov rsp, rbp
	pop rbp
	ret
; out for video function
outpw:
	mov rdx, rdi
	out dx, ax
	ret
; in for video function
inpw:
	mov rdx, rdi
	in ax, dx
	ret



	
