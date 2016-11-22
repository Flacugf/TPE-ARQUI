;
; interrups.asm
;
;

GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL int80Handler
GLOBAL keyboardHandler
GLOBAL timerTickHandler
GLOBAL _lidt
GLOBAL haltcpu
GLOBAL networkHandler
EXTERN int80HandlerC
EXTERN keyboardHandlerC
EXTERN timerTickHandlerC
EXTERN networkHandlerC
%macro pushall 0
    push rax      ;save current rax
    push rbx      ;save current rbx
    push rcx      ;save current rcx
    push rdx      ;save current rdx
    push rbp      ;save current rbp
    push rdi       ;save current rdi
    push rsi       ;save current rsi
    push r8        ;save current r8
    push r9        ;save current r9
    push r10      ;save current r10
    push r11      ;save current r11
    push r12      ;save current r12
    push r13      ;save current r13
    push r14      ;save current r14
    push r15      ;save current r15
%endmacro

%macro popall 0
        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rsi
        pop rdi
        pop rbp
        pop rdx
        pop rcx
        pop rbx
        pop rax
%endmacro


SECTION .text

_cli:
	cli
	ret


_sti:
	sti
	ret


picMasterMask:
    mov rax, rdi
    out	21h,al
    ret

picSlaveMask:
    mov rax, rdi 
    out	0A1h,al
    ret

;int80handler:
int80Handler:
	pushall
	sti
	mov rdi, rcx   ; Primer parametro
    mov rsi, rax    ; syscall
	call int80HandlerC
	popall
	iretq

keyboardHandler:
    pushall
    call keyboardHandlerC
    mov al, 0x20
    out 0x20, al

    mov al, 20h
    out 0xA0, al
    popall
    iretq

haltcpu:
	hlt
	ret

timerTickHandler:
    pushall
    call timerTickHandlerC
    mov al,0x20
    out 0x20,al

    mov al, 20h
    out 0xA0, al
    popall
    iretq

networkHandler:
    pushall
    call networkHandlerC
    mov al,20h
    out 20h, al

    mov al, 20h
    out 0xA0, al
    popall
    iretq
