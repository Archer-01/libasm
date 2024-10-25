global ft_strcmp

section .text

ft_strcmp:

loop:
	mov cl, [rdi]
	mov dl, [rsi]
	cmp cl, 0
	je  test_s2
	cmp dl, 0
	je  test_s1
	inc rdi
	inc rsi
	cmp cl, dl
	jg ret_one
	jl ret_negative_one
	je loop

test_s1:
	cmp byte [rdi], 0
	je  ret_zero
	jg  ret_one

test_s2:
	cmp byte [rsi], 0
	je  ret_zero
	jg  ret_negative_one

ret_zero:
	mov rax, 0
	ret

ret_one:
	mov rax, 1
	ret

ret_negative_one:
	mov rax, -1
	ret
