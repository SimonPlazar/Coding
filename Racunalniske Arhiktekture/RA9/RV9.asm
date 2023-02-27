extern scanf
extern printf

section .data
	OutputGetBesedilo: db "Vnesi besedilo: ", 0 ; format za vnos besedila
	InputBesedilo: db "%s", 0 ; format v katerem bo besedilo prebrano
	OutputFinal: db "Obrnjeno: %s", 10, 0 ; format za izpis obrnjenega besedila
	OutputSize: db "Dolzina: %d", 10, 0 ; format za izpis obrnjenega besedila
	
section .bss
	besedilo: resb 1024 ; pripravljen prostor za besedilo
	obrnjeno: resb 1024 ; pripravljen prostor za obrnjeno besedilo
	size: resb 4 ; pripravljen prostor za dolzino besedilo

section .text
global main
global obrni

main:
	; pripravimo stack
	push rbp
	mov rbp, rsp
	
	mov rdi, OutputGetBesedilo ; format za izpis
	xor rax, rax ; rax postavimo na 0
	call printf
	
	mov rdi, InputBesedilo ; format za vnos
	mov rsi, besedilo ; lokacija za vnos
	xor rax, rax ; rax postavimo na 0
	call scanf
	
	
	; prestejemo dolzino besedila
	mov DWORD [size], -1 ; inicializiramo vrednost size na 0
	mov rsi, besedilo ; shranimo kazalec na besedilo v rsi
	cld ; zbrisemo zastavico za premik
.count:
	add DWORD [size], 1 ; dodamo 1
	lodsb ; preberemo črko in rsi++
	cmp al, 0 ; ce je znak 0 potem konec besedila
	jnz .count


	; klic funkcije
	mov rdi, besedilo ; kazalec na polje besedilo
	mov rsi, obrnjeno ; kazalec na polje obrnjeno
	mov rdx, size ; kazalec na size
	call obrni
	
	
	; izpis
	mov rdi, OutputSize ; format za izpis
	mov rsi, [size]
	xor rax, rax ; rax postavimo na 0
	call printf
	
	mov rdi, OutputFinal ; format za izpis
	mov rsi, obrnjeno
	xor rax, rax ; rax postavimo na 0
	call printf
	
exit:
	; ponastavimo stack
	mov rsp, rbp
	pop rbp
	ret

obrni:
	;rdi, besedilo
	;rsi, obrnjeno
	;rdx, size
	;rcx
	
	mov rcx, rdi ; shranimo kazalec do zacetka besedila
	add rsi, [rdx] ; pomaknemo se na konec obrnjenega niza
	
loop:
	; prenese en byte in premakne kazalce
	mov byte dl, [rdi] ; shranimo znak v dl
	std ; nastavimo zastavico za premik
	lodsb ; nalozi byte (rsi--)
	mov byte [rsi], dl ; shranimo na lokacijo rsi
	cld ; zbrisemo zastavico za premik
	stosb ; shrani byte (rdi++)
	
	; preveri izhodni pogoj
	cmp rsi, rdi ; preverimo če smo na zadnjem znaku
	jle .konec ; skocimo n konec label
	
	;ponovi zanko
	jmp loop ; skoci na label loop
	
.konec:
	mov rdi, rcx ; ponastavimo kazalec do zacetka besedila
	ret ; se vrnemo v glavni program

	
