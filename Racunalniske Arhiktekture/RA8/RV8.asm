extern scanf
extern printf

section .data
	output: db "Rezultat: %d", 10, 0 ; format za izpis
	
section .bss
	i resb 4 ; 4 byti za int i
	n resb 4 ; 4 byti za int i

section .text
global main
global recursion

main:
	; pripravimo stack in rezerviramo pomnilnik za i
	push rbp
	mov rbp, rsp
	
	mov DWORD [i], 10 ; inicializiramo vrednost i na 3
	mov DWORD [n], 3 ; inicializiramo vrednost i na 10
	
loop:	
	; preverjanje izhodnega parametra
	mov ecx, DWORD[n] ; v ecx premaknemo vrednost na n
	cmp [i], ecx ; primerjamo
	jl exit ; ce je vecje potem na exit

	mov rdi, [n]
	call recursion ; klic funkcije
	
	; izpis rezultata funkcije
	mov rdi, output ; dolocimo format (stevilka)
	mov rsi, rax ; podamo stevilko na naslovu rax (rezultat)
	xor eax, eax ; eax damo 0
	call printf ; klic funkcije
	
	add DWORD [n], 1 ; dodamo 1 spremenljivki i
	jmp loop ; skocimo na label loop
	
exit:
	; ponastavimo stack
	mov rsp, rbp
	pop rbp
	
	ret

recursion:
	; rax = rezultat
	; rdi = n

	cmp rdi, 0 ; ce je n = 0
	je .Nic
	cmp rdi, 1 ; ce je n = 1
	je .Ena 
	cmp rdi, 2 ; ce je n = 2
	je .Dva
	
	; f(n-2)
	
	push rdi ; shranimo n v stack 
	sub rdi, 2 ; zmanjsamo rdi za 2 (n-2)
	call recursion ; f(n-2)
	pop rdi ; pridobimo n nazaj iz stacka (rdi = n)
	
	; f(n-3)
	push rax ; shranimo rezultat f(n-2) na stack
	push rdi ; shranimo n v stack
	sub rdi, 3 ; zmanjsamo rdi za 3 (n-3)
	call recursion ; f(n-3)
	pop rdi ; pridobimo n nazaj iz stacka (rdi = n)
	
	; rezultat
	pop rdi ; pridobimo f(n-2) nazaj iz stacka
	add rax, rdi ; pristejemo f(n-2) k f(n-3)
	add rax, 1 ; pristejemo 1 zgornji vsoti
	ret ; vrnemo nazaj rezultat
	
.Nic:
	mov rax, 12 ; damo vrednost za vracanje na 12
	ret ; vrnemo f(0) = 12
.Ena:
	mov rax, 22 ; damo vrednost za vracanje na 22
	ret ; vrnemo f(1) = 22
.Dva:
	mov rax, 45 ; damo vrednost za vracanje na 45
	ret ; vrnemo f(2) = 45
	
	
