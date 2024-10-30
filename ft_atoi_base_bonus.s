global ft_atoi_base

extern ft_strlen

section .text

ft_atoi_base:

__check_base_len:
	;    Checks is len(base) < 2
	;    rdi=str, rsi=base
	push rdi
	mov  rdi, rsi
	call ft_strlen
	pop  rdi
	cmp  rax, 2
	jl   __bad_base

	mov rcx, 0

__loop1:
	;   Checks for invalid characters (+, - and whitespaces) in base
	;   rsi=base, rax=ft_strlen(base)
	cmp byte [rsi + rcx], '+'
	je  __bad_base
	cmp byte [rsi + rcx], '-'
	je  __bad_base
	cmp byte [rsi + rcx], ' '
	je  __bad_base
	inc rcx
	cmp rcx, rax
	jl  __loop1

	mov rcx, 0

__loop2:
	;   Checks for duplicates in base
	;   rsi=base, rax=ft_strlen(base), bl=current char in base
	mov rdx, 0

__loop2_inner:
	cmp rcx, rdx
	je  __loop2_inner_continue
	mov rbx, 0
	mov bl, byte [rsi + rcx]
	cmp bl, byte [rsi + rdx]
	je  __bad_base
	inc rdx
	cmp byte [rsi + rdx], 0
	je  __loop2_next

__loop2_inner_continue:
	inc rdx
	cmp byte [rsi + rdx], 0
	je __loop2_next
	jmp __loop2_inner

__loop2_next:
	inc rcx
	cmp byte [rsi + rcx], 0
	je  __pre_check_sign
	jmp __loop2

__pre_check_sign:
	mov rcx, 0

__check_sign:
	;   Checks if str begins with a sign (+ or -)
	;   rdi=str, rcx=loop index
	cmp byte [rdi], '+'
	je  __skip_sign_plus
	cmp byte [rdi], '-'
	je  __skip_sign_minus
	jmp __convert_num

__skip_sign_plus:
	inc rcx

__skip_sign_minus:
	neg byte [sign]
	inc rcx

__convert_num:
	mov qword [baselen], rax
	mov rax, 0
	mov rcx, 0

__loop3:
	;    Convert str to an integer
	;    rdi=str, rax=return value, rcx=loop counter
	push rdi
	push rcx
	push rax
	mov  rbx, 0
	mov  bl, byte [rdi + rcx]
	mov  rdi, rbx
	call __find_digit
	mov  rbx, rax
	pop  rax
	pop  rcx
	pop  rdi
	;    Check the return value of __find_digit
	cmp  rbx, -1
	je   __ret_value
	;    rbx will hold the return value of __find_digit
	imul rax, qword [baselen]
	add  rax, rbx
	inc  rcx
	cmp  byte [rdi + rcx], 0
	je   __ret_value
	jmp  __loop3

__ret_value:
	; Coming from __loop3
	ret

__bad_base:
	mov rax, 0
	ret

__find_digit:
	;   Params: rdi=c, rsi=base
	mov rcx, 0
	mov rbx, 0
	mov rbx, rdi

__find_digit_loop:
	cmp byte [rsi + rcx], bl
	je  __find_digit_ret
	inc rcx
	cmp byte [rsi + rcx], 0
	je  __find_digit_notfound
	jmp __find_digit_loop

__find_digit_notfound:
	mov rax, -1
	ret

__find_digit_ret:
	mov rax, rcx
	ret

section .data

sign:
	db 1

baselen:
	dq 0
