extern scanf
extern printf

section .data
	txt: db "Vpisi stevilko za N: ", 0
	output: db "%d", 10, 0 ; format za ispis i
	input: db "%d", 0 ; format za branje N

section .bss
	i resb 4 ; 4 byti za int i
	n resb 4 ; 4 byti za int N

section .text
global main

main:
	; pripravimo stack in rezerviramo pomnilnik za i
	push rbp
	mov rbp, rsp
	sub rsp, 16

	; izpisi navodila za vnos
	xor eax, eax ; eax shranimo 0
	mov rdi, txt ; podamo besedilo
	call printf ; klic funkcije

	; branje vnosa uporabnika
	xor eax, eax ; eax damo 0
	mov rdi, input ; format prebranega niza
	mov rsi, n ; mesto, kam bomo shranili vneseno stevilko
	call scanf ; klic funkcije

	mov DWORD [i], 1 ; inicializiramo vrednost i na 1 

loop:
	; preverjanje izhodnega parametra
	mov ecx, DWORD[n] ; v ecx premaknemo vrednost na n
	cmp [i], ecx ; primerjamo ce je enako
	je exit ; ce je enako potem na exit
	
	; izpis spremenljivke i
	xor eax, eax ; eax damo 0
	mov rdi, output ; dolocimo format (stevilka)
	mov rsi, [i] ; podamo stevilko na naslovu i
	call printf ; klic funkcije
	
	add DWORD [i], 1 ; dodamo 1 spremenljivki i
	jmp loop ; skocimo na label loop

exit:
	; ponastavimo stack
	add rsp, 16
	mov rsp, rbp
	pop rbp
	
	ret
