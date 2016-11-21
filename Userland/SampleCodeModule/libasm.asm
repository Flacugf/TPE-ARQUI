GLOBAL write
GLOBAL read
GLOBAL syscaller
GLOBAL playSound
GLOBAL colourSwap
GLOBAL closeCpu
GLOBAL playSong
GLOBAL writeSlow
GLOBAL writeInLine
GLOBAL video
GLOBAL send
send:
	push rbp
	mov rbp, rsp
	mov rcx, rdi
	mov rdx, rsi
	mov rax, 11
	int 80h
	mov rsp, rbp
	pop rbp
	ret
write:
	push rbp
	mov rbp, rsp
	push rbx
	mov rbx, 1
	mov rcx, rdi ;char
	mov rdx, rsi ;length
	mov rax, 2
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret
writeInLine:
	push rbp
	mov rbp, rsp
	push rbx
	mov rbx, 1
	mov rcx, rdi ;char
	mov rdx, rsi ;length
	mov rax, 8
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret
writeSlow:
	push rbp
	mov rbp, rsp
	push rbx
	mov rbx, 1
	mov rcx, rdi ;char
	mov rdx, rsi ;length
	mov rax, 3
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret
read:
	push rbp
	mov rbp, rsp
	push rbx
	mov rcx, rdi  
	mov rdx, rsi ;length
	mov rax, 1
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret

closeCpu:
	push rbp
	mov rbp, rsp
	push rbx
	mov rcx, rdi  
	mov rdx, rsi ;length
	mov rax, 4
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret


playSound:
	push rbp
	mov rbp, rsp
	push rbx
	mov rcx, rdi  
	mov rdx, rsi ;length
	mov rax, 42
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret

colourSwap:
	push rbp
	mov rbp, rsp
	push rbx
	mov rcx, rdi  
	mov rdx, rsi ;length
	mov rax, 6
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret
playSong:
	push rbp
	mov rbp, rsp
	push rbx
	mov rbx, 1
	mov rcx, rdi 
	mov rdx, rsi ;length
	mov rax, 9
	int 80h
	pop rbx
	mov rsp,rbp
	pop rbp
	ret
video:
	push rbp
	mov rbp, rsp
	push rbx
	mov rcx, rdi
	mov rdx, rsi
	mov rax, 10
	int 80h
	pop rbx
	mov rsp, rbp
	pop rbp
	ret
