global ft_strdup

extern __errno_location
extern ft_strcpy
extern ft_strlen
extern malloc

section .text

ft_strdup:
	cmp  rdi, 0
	je   return_null
	push rdi
	call ft_strlen
	inc rax
	mov  rdi, rax
	call malloc
	cmp  rax, 0
	je   error
	mov  rdi, rax
	pop  rsi
	call ft_strcpy
	ret

error:
	call __errno_location
	mov  eax, 12

return_null:
	mov rax, 0
	ret
