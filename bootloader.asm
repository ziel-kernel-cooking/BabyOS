[bits 16]
org 0x7c00

mov ah, 0x06
mov al, 0
mov bh, 0x0F
mov cx, 0x0000
mov dx, 0x184F
int 0x10

mov ah, 0x02
mov bh, 0x00
mov dh, 0
mov dl, 0
int 0x10

K_LOC equ 0x7e00 ; kernel location 0x7e00

mov bx, menumsg
mov ah, 0x0e
mov ecx, menu
jmp disp

menu:
    mov ah, 0x02
    inc dh
    mov dl, 0
    mov bh, 0
    int 0x10
    
    mov ah, 0
    int 0x16

    cmp al, 'a'
    je floppy

    cmp al, 'b'
    je disk0

    cmp al, 'c'
    je disk1

    mov bx, stupidmsg
    mov ah, 0x0e
    mov ecx, menu
    jmp disp

floppy:
    mov si, 0x00
    mov bx, menu2msg
    mov ah, 0x0e
    mov ecx, menu2
    jmp disp

disk0:
    mov si, 0x80
    mov bx, menu2msg
    mov ah, 0x0e
    mov ecx, menu2
    jmp disp

disk1:
    mov si, 0x81
    mov bx, menu2msg
    mov ah, 0x0e
    mov ecx, menu2
    jmp disp 

menu2:
    mov ah, 0x02
    inc dh
    mov dl, 0
    mov bh, 0
    int 0x10

    mov ah, 0
    int 0x16

    cmp al, '1'
    je protectedch

    cmp al, '0'
    je realch

    mov bx, stupidmsg
    mov ah, 0x0e
    mov ecx, menu2
    jmp disp

protectedch:
    mov bp, 1
    jmp startboot

realch:
    mov bp, 2
    jmp startboot

startboot:
    mov dx, si
    mov ah, 2
    mov al, 100 ;number of sectors to read
    mov ch, 0 ;cylinder number
    mov cl, 2 ;starting sector number(1)
    mov dh, 0 ; head number
    xor bx, bx
    mov es, bx
    mov bx, K_LOC ; load adress
    int 0x13
    jc unsucread

    mov bx, K_LOC
    mov di, [bx]
    cmp di, 1
    jne unsucload

    jmp sucload

errormsg:
    db "read_err", 0

sucmsg:
    db "succ_load", 0

errormsgl:
    db "load_err", 0

menumsg:
    db "drive?: A-0x00 B-0x80 C-0x81", 0

menu2msg:
    db "1-p32b / 0-r16b ?", 0

stupidmsg:
    db "Are you dumb?", 0

disp:
    mov al, [bx]
    cmp al, 0
    je sjump
    int 0x10
    inc bx
    jmp disp

sjump:
    jmp ecx

unsucread:
    mov bx, errormsg
    mov ah, 0x0e
    mov ecx, exitloop
    jmp disp

unsucload:
    mov bx, errormsgl
    mov ah, 0x0e
    mov ecx, exitloop
    jmp disp

sucload:
    mov bx, sucmsg
    mov ah, 0x0e
    mov ecx, exitloop2
    jmp disp

exitloop2:
    mov ah, 0x03
    mov bh, 0x00
    int 0x10
    mov dl, 0
    inc dh
    mov ah, 0x02
    int 0x10

    cmp bp, 1
    je startprotectedmode
    cmp bp, 2
    je K_LOC

exitloop:
    jmp exitloop

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 10011010b
        db 11001111b
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 10010010b
        db 11001111b
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1 
    dd GDT_start

startprotectedmode:
    mov ah, 1
    mov cx, 0x2000
    int 0x10

    CODE_SEG equ GDT_code - GDT_start
    DATA_SEG equ GDT_data - GDT_start

    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    lgdt [GDT_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:load_32program

[bits 32]
load_32program:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x90000
    mov esp, ebp

    in al, 0x92
    or al, 0x02
    out 0x92, al

    jmp CODE_SEG:K_LOC

times 510-($-$$) db 0
db 0x55, 0xaa