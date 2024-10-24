global ft_strcpy

section .text

ft_strcpy:
	mov rax, rdi

loop:
	mov dl, [rsi]
	mov [rdi], dl
	inc rsi
	inc rdi
	cmp dl, 0
	jne loop

end:
	mov byte [rdi], 0
	ret
