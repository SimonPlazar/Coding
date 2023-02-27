extern scanf
extern printf

section .data
	txt: db "Vpisi stevilko za N: ", 0
	output: db "%d", 10, 0 ; format za izpis i
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
	
	; eax / ecx (32 bitni registri ker 32 bitne stevilke)
    ; kolicnik eax
    ; ostanek edx
    mov eax, [n] ; shranimo vrednost na n v eax
    mov ecx, 2; shranimo 2 v ecx
    div ecx ; deli N/2
    
    mov DWORD [n], eax ; na mesto n shranimo celi del n/2

loop:
	; preverjanje izhodnega parametra
	mov ecx, DWORD[n] ; v ecx premaknemo vrednost na n
	cmp [i], ecx ; primerjamo ce je enako
	jg exit ; ce je vec potem na exit

	xor edx, edx ; resetiramo register edx
	mov eax, [i] ; eax damo vrednost v i
    mov ebx, 47  ; ebx damo 47
	div ebx    ; i/47
	cmp edx, 0 ; preveri ce je ostanek
	je izpis ; skoci na label izpis
	
	add DWORD [i], 1 ; i++
	jmp loop

izpis:
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
