global ft_list_sort

section .text

ft_list_sort:
	;   rdi=&begin_list, rsi=cmp
	cmp qword [rdi], 0
	jne __sort
	ret

__sort:
	;   r8=i, r9=j
	mov r8, qword [rdi]
	jmp __outer_loop

__outer_loop:
	mov r12, 0
	mov r9, qword [r8 + NEXT]
	jmp __inner_loop

__inner_loop:
	cmp r9, 0
	je  __end_inner_loop
	cmp r8, r9
	je  __continue_inner_loop

	push rdi
	push rsi
	push r8
	push r9

	mov  r10, rsi
	push r10

	mov  rdi, qword [r8 + DATA]
	mov  rsi, qword [r9 + DATA]
	call r10 ;call cmp

	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi

	cmp eax, 0
	jg  __swap
	jmp __continue_inner_loop

__swap:
	mov r12, 1

	push rdi
	push rsi

	mov  rdi, r8
	mov  rsi, r9
	call __swap_data

	pop rsi
	pop rdi

	jmp __continue_inner_loop

__swap_data:
	mov r14, qword [rdi + DATA]
	mov r15, qword [rsi + DATA]
	mov qword [rdi + DATA], r15
	mov qword [rsi + DATA], r14
	ret

__continue_inner_loop:
	mov r9, qword [r9 + NEXT]
	cmp r9, 0
	jnz __inner_loop
	jmp __end_inner_loop

__end_inner_loop:
	cmp r12, 0
	je  __end
	mov r8, qword [r8 + NEXT]
	cmp r8, 0
	jnz __outer_loop
	jmp __end

__end:
	ret

section .rodata

DATA equ 0
NEXT equ 8
