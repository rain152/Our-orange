[section .text]
[BITS 32]

INT_VECTOR_SYS_CALL equ 0x90
_NR_sendrec equ 1

SEND equ 1
RECEIVE equ 2

EXEC equ 15
TASK_MM equ 4

P_TYPE equ 0x4
P_PATHNAME equ 0x28
P_NAME_LEN equ 0xC
MSG_SIZE equ 176


global _start

_start:
    ; xchg bx, bx
    jmp get_addr

main:
    pop edx
    ; memset(msg, 0, sizeof(msg))
    xor eax, eax
    xor ecx, ecx
    mov cl, MSG_SIZE
    mov edi, edx
    cld
    rep stosb
    ; msg.type = EXEC
    mov edi, edx
    mov byte [edi + P_TYPE], EXEC
    ; msg.PATHNAME = (void *)path
    mov esi, edi
    mov cl, MSG_SIZE
    add esi, ecx
    mov [edi + P_PATHNAME], esi
    ; msg.NAME_LEN = strlen(path)
    mov byte [edi + P_NAME_LEN], NAME_LEN
    
    mov cl, END_POS
    add edi, ecx
    xor eax, eax
    mov byte [edi], al

    ; mov eax, _NR_sendrec
    mov al, _NR_sendrec
    ; mov ebx, SEND
    xor ebx, ebx
    mov bl, SEND
    ; mov ecx, TASK_MM
    xor ecx, ecx
    mov cl, TASK_MM
    ; sendrec
    int INT_VECTOR_SYS_CALL
    
    ; mov eax, _NR_sendrec
    xor eax, eax
    mov al, _NR_sendrec
    ; mov ebx, RECEIVE
    xor ebx, ebx
    mov bl, RECEIVE
    ; mov ecx, TASK_MM
    xor ecx, ecx
    mov cl, TASK_MM
    ; sendrec
    int INT_VECTOR_SYS_CALL

get_addr:
    call main

msg:
    times 176 db 1
pathname:
    db "mario"
NAME_LEN equ $ - pathname
END_POS equ $ - msg

; PUBLIC int exec(const char *path)
; {
;   MESSAGE msg;
;   msg.type = EXEC;
;   msg.PATHNAME = (void *)path;
;   msg.NAME_LEN = strlen(path);
;   msg.BUF = 0;
;   msg.BUF_LEN = 0;
;
;   send_recv(BOTH, TASK_MM, &msg);
;   assert(msg.type == SYSCALL_RET);
;
;   return msg.RETVAL;
; }
