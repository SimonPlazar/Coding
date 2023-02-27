section .data
    message: db "Simon Plazar E1136441", 10, 0 ; podamo sporocilo

section .text
    extern printf ; razsirimo da podpira printf
    global main
    
main:
    push rbp ; pripravimo ogrodje za stack

    mov	rdi, message ; podamo sporocilo za izpis
    xor	rax, rax ; vrednost 0 shranimo v rax (std_out)

    call printf ; klicemo printf
    
    pop	rbp ; ponastavimo nazaj

    xor	rax, rax ; v rax shranimo 0 za return vrednost
    ret
