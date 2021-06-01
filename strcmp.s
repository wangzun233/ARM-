.text 
.code 32
.global my_strcmp
my_strcmp:
cmp_loop:
    ldrb r2,[r0],#1
    ldrb r3,[r1],#1
    cmp r2, #0
    beq cmp_end
    cmp r2, r3
    beq cmp_loop
cmp_end:
    sub r0, r2, r3
    bx lr
.end

