extern printf
global main
section .data
msg_start db "Starting", 10, 0
msg_simple db "Normal instruction cycles: %llu", 10, 0
msg_vmexit db "CPUID (VMExit) cycles: %llu", 10, 0
msg_result db "Detected overhead: %llu times slower.", 10, 0
section .text
main:
push rbp
mov rbp, rsp
mov rdi, msg_start
xor rax, rax
call printf
cpuid
7
rdtsc
shl rdx, 32
or rax, rdx
mov r12, rax
mov rbx, rbx
rdtsc
shl rdx, 32
or rax, rdx
sub rax, r12
mov r13, rax ; время обычной команды
mov rdi, msg_simple
mov rsi, r13
xor rax, rax
call printf
cpuid
rdtsc
shl rdx, 32
or rax, rdx
mov r12, rax ; время старта
mov eax, 0
cpuid ; VMEXIT
rdtsc
shl rdx, 32
or rax, rdx
8
sub rax, r12
mov r14, rax ; r14 = время с VMExit
mov rdi, msg_vmexit
mov rsi, r14
xor rax, rax
call printf
mov rax, r14
xor rdx, rdx
div r13 ; делим время VMExit на обычное время
mov rdi, msg_result
mov rsi, rax
xor rax, rax
call printf
xor rax, rax
leave
ret
section .note.GNU-stack noalloc noexec nowrite progbits
