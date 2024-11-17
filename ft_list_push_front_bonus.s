global ft_list_push_front

extern malloc

section .text

ft_list_push_front:
	;    rdi=begin_list, rsi=data
	cmp  qword [rdi], 0
	je   __empty_list
	mov  rbx, qword [rdi]
	push rdi
	mov  rdi, rsi
	call __list_create_elem
	pop  rdi
	mov  qword [rax + NEXT], rbx
	mov  qword [rdi], rax
	ret

__empty_list:
	push rdi
	mov  rdi, rsi
	call __list_create_elem
	pop  rdi
	mov  qword [rdi], rax
	ret

__list_create_elem:
	;    rdi=data
	push rdi
	mov  rdi, 16
	call malloc wrt ..plt
	pop  rdi
	cmp  rax, 0
	je   __malloc_failed
	mov  qword [rax + DATA], rdi
	mov  qword [rax + NEXT], 0
	ret

__malloc_failed:
	mov rax, 0
	ret

section .rodata

DATA EQU 0
NEXT EQU 8
