section .data
	Input: db "Vnesi besedilo: ", 0 ; format za vnos
	Output: db "Napisano z malimi crkami: ", 0 ; format za izpis

section .bss
	besedilo: resb 1024 ; pripravljen prostor za besedilo

section .text
	global main
	global toLowerUnderscore

main:
	; pripravimo stack
	push rbp
	mov rbp, rsp
	
	; ssize_t write(int fildes, const void *buf, size_t nbytes);
	mov rax, 1 ; syscall za write
	mov rdi, 1 ; fd 1 = STDOUT
	mov rsi, Input ; buf
	mov rdx, 17 ; size
	syscall
	
	; ssize_t read(int fildes, void *buf, size_t nbyte);
	mov rax, 0 ; syscall za write
	mov rdi, 0 ; fd 0 = STDIN
	mov rsi, besedilo ; buf
	mov rdx, 1024 ; max size
	syscall
	mov r12, rax ; read vrne stevilo bytov prebranih
	
	mov rdi, besedilo ;
	call toLowerUnderscore
	
	mov rax, 1 ; syscall za write
	mov rdi, 1 ; fd 1 = STDOUT
	mov rsi, Output ; buf
	mov rdx, 27 ; size
	syscall
	
	mov rax, 1 ; syscall za write
	mov rdi, 1 ; fd 1 = STDOUT
	mov rsi, besedilo ; buf
	mov rdx, r12 ; size
	syscall
	
	mov rax, 1 ; syscall za write
	mov rdi, 1 ; fd 1 = STDOUT
	mov rsi, 0xA ; buf
	mov rdx, 2 ; size
	syscall

	
.exit:
	; ponastavimo stack
	mov rsp, rbp
	pop rbp
	;xor rax, rax
	ret


	
toLowerUnderscore:
	lodsb ; prebere byte in shrani v al
	
	cmp al, 0 ; ce je konec niza
	je .konec
	
	cmp al, 32 ; ce je presledek
	je .Space
	
	cmp al, 65 ; ce je prebrana crka vecja ali enaka 65 (ascii A = 65)
	jge .GreaterThanA
	
	jmp toLowerUnderscore ; cene nazaj na zanko

.Space:
	add al, 63 ; ascii ' ' + 63 = '_'
	mov byte [rsi-1], al ; zapisemo byte v array
	jmp toLowerUnderscore
	
.GreaterThanA:
	cmp al, 90 ; ce je prebrana crka manjsa ali enaka 90 (ascii Z = 90)
	jle .MakeLower
	jmp toLowerUnderscore
	
.MakeLower:
	add al, 32 ; ce ascii velikim crkam pristejemo 32 dobimo malo razlicino crke
	mov byte [rsi-1], al ; zapisemo byte v array
	jmp toLowerUnderscore

.konec:
	ret

