extern scanf
extern printf

section .data
	txt: db "Vpisi stevilko: ", 0
	output: db "Najmanjse stevilo je: %d", 10, 0 ; format za izpis najmanjsega stevila
	input: db "%d", 0 ; format za branje stevil

section .bss
	num1 resb 4 ; 4 byti za prvo stevilo
	num2 resb 4 ; 4 byti za drugo stevilo
	num3 resb 4 ; 4 byti za tretje stevilo

section .text
	global main
	global min3

main:
	; pripravimo stack in rezerviramo pomnilnik za i
	push rbp
	mov rbp, rsp
	sub rsp, 48
	
	;----------------------Vnos-Stevil--------------------------
	; izpisi navodila za vnos
	xor eax, eax ; eax shranimo 0
	mov rdi, txt ; podamo besedilo
	call printf ; klic funkcije

	; branje vnosa uporabnika
	xor eax, eax ; eax damo 0
	mov rdi, input ; format prebranega niza
	mov rsi, num1 ; mesto, kam bomo shranili vneseno stevilko
	call scanf ; klic funkcije
	
	; izpisi navodila za vnos
	xor eax, eax ; eax shranimo 0
	mov rdi, txt ; podamo besedilo
	call printf ; klic funkcije

	; branje vnosa uporabnika
	xor eax, eax ; eax damo 0
	mov rdi, input ; format prebranega niza
	mov rsi, num2 ; mesto, kam bomo shranili vneseno stevilko
	call scanf ; klic funkcije
	
	; izpisi navodila za vnos
	xor eax, eax ; eax shranimo 0
	mov rdi, txt ; podamo besedilo
	call printf ; klic funkcije

	; branje vnosa uporabnika
	xor eax, eax ; eax damo 0
	mov rdi, input ; format prebranega niza
	mov rsi, num3 ; mesto, kam bomo shranili vneseno stevilko
	call scanf ; klic funkcije
	
	;--------------Iskanje-Najmanjsega-Stevila------------------
	
	xor rax, rax
	mov rdi, num1
	mov rsi, num2
	mov rdx, num3
    call min3
	
	mov rbx, rax
	
	;-------------------Izpis--Stevilke-------------------------
	
	xor eax, eax ; eax shranimo 0
	mov rdi, output ; dolocimo format (stevilka)
    mov rsi, [rbx] ; podamo stevilko na naslovu num1
	call printf ; klic funkcije

	; ponastavimo stack
	mov rsp, rbp
	pop rbp
	
	ret
	
min3:
	; rdi   rsi   rdx
	push rbp
	
	mov eax, [rdi] ; v eax shranimo vrednost na num1
    cmp eax, [rsi] ; primerjava med num1 in num2
    jl Min1 ; num1 < num2
    jmp Min2 ; num1 >= num2
    
Min1:
	mov eax, [rdi] ; v eax shranimo vrednost na num1
    cmp eax, [rdx] ; primerjava med num1 in num3
    jl Save1 ; num1 < num3
    mov rax, rdx ; num1 >= num3
    jmp Return

Min2:
	mov eax, [rsi] ; v eax shranimo vrednost na num2
    cmp eax, [rdx] ; primerjava med num2 in num3
    jl Save2 ; num2 < num3
    mov rax, rdx ; num2 >= num3
    jmp Return
    
Save1:
	mov rax, rdi
	jmp Return
	
Save2:
	mov rax, rsi

Return:	
	pop rbp
	ret
	

