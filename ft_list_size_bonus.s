global ft_list_size

section .text

ft_list_size:
	;   rdi=begin_list
	mov rax, 0

__loop:
	cmp rdi, 0
	je  __loop_end
	inc rax
	mov rdi, qword [rdi + NEXT]
	jmp __loop

__loop_end:
	ret

section .rodata

NEXT EQU 8
