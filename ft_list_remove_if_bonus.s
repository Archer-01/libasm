global ft_list_remove_if

extern free

section .text

ft_list_remove_if:
	;   rdi=&begin_list, rsi=data_ref, rdx=cmp, rcx=free_fct
	cmp qword [rdi], 0
	jne __begin
	ret

__begin:
	mov r12, rdi
	mov r13, rsi
	mov r14, rdx
	mov r15, rcx
	mov rcx, qword [r12]

__loop:
	;   r12=&begin_list, r13=data_ref, r14=cmp, r15=free_fct
	cmp rcx, 0
	je  __end_loop
	cmp qword [rcx + NEXT], 0
	je  __end_loop

	mov  rdi, qword [rcx + NEXT] ; rdi = rcx->next
	mov  rdi, qword [rdi + DATA] ; rdi = rcx->next->data
	mov  rsi, r13
	push rcx
	call r14 ; call cmp
	pop  rcx
	cmp  eax, 0
	je   __found_target
	jmp  __loop_next

__found_target:
	mov  r11, qword [rcx + NEXT]
	mov  r10, qword [rcx + NEXT] ; r10 = rcx->next
	mov  r10, qword [r10 + NEXT] ; r10 = rcx->next->next
	mov  qword [rcx + NEXT], r10 ; rcx->next = r10
	mov  rdi, qword [r11 + DATA]
	push rcx
	call r15 ; call free_fct
	pop  rcx
	mov  rdi, r11
	push rcx
	call free
	pop  rcx
	jmp  __loop

__loop_next:
	mov rcx, qword [rcx + NEXT]
	jmp __loop

__end_loop:
	;    r12=&begin_list, r13=data_ref, r14=cmp, r15=free_fct
	mov  rdi, qword [r12] ; rdi = *begin_list
	mov  rdi, qword [rdi + DATA] ; rdi = rdi->data
	mov  rsi, r13
	push rcx
	call r14 ; call cmp
	pop  rcx
	cmp  eax, 0
	je   __found_target_at_beginning
	ret

__found_target_at_beginning:
	mov r11, qword [r12] ; r11 = *begin_list

	mov r10, qword [r12] ; r10 = *begin_list
	mov r10, qword [r10 + NEXT] ; r10 = (*begin_list)->next
	mov qword [r12], r10 ; *begin_list = (*begin_list)->next

	mov  rdi, qword [r11 + DATA]
	call r15 ; call free_fct
	mov  rdi, r11
	call free
	ret

section .rodata

DATA equ 0
NEXT equ 8
