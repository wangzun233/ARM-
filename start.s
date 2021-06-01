.equ	USR_MODE,		0x10	/* normal user mode */
.equ 	FIQ_MODE,		0x11	/* fiq fast interrupts mode */
.equ 	IRQ_MODE,		0x12	/* irq standard interrupts mode */
.equ 	SVC_MODE,		0x13	/* supervisor interrupts mode */
.equ 	ABT_MODE,		0x17	/* abort processing memory faults mode */
.equ 	UDF_MODE,		0x1b	/* undefined instructions mode */
.equ 	MODE_MASK,		0x1f	/* system running in priviledged operating mode */
.equ 	NO_INT,			0xc0
.equ    CPSR_IRQ_EN,	0x80
.equ    CPSR_IRQ_MASK,	0x40	/* disable interrupt mode (irq) */
.equ    CPSR_FIQ_MASK,	0x80	/* disable fast interrupt mode (fiq) */

.text
.code 32

/*异常向量表*/
.globl	_start
_start:
	b 	reset
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction:	
    .word undefined_instruction
_software_interrupt:	
    .word software_interrupt
_prefetch_abort:	
    .word prefetch_abort
_data_abort:		
    .word data_abort
_not_used:		 
    .word not_used
_irq:			
    .word irq
_fiq:			
    .word fiq

	.balignl 16,0xdeadbeef


/*执行 go 0x48000000执行的入口*/
reset:
	
        /*设置CPU为SVC模式*/
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr,r0
	
        /* 修改异常向量表的入口地址从0改为0x48000000*/
	ldr r0, =0x48000000
	mcr p15, 0, r0, c12, c0, 0

	mrc p15, 0, r0, c1, c0, 0
	bic r0, #(1<<13)
	mcr p15, 0, r0, c1, c0, 0


	/* 初始化栈*/
        bl	init_stacks

        bl  main

init_stacks:
	mrs	r0, cpsr
	bic	r0, r0, #MODE_MASK | NO_INT
	orr	r1, r0, #UDF_MODE
	msr	cpsr, r1
	ldr	sp, _stack_und_end

	bic	r0, r0, #MODE_MASK | NO_INT
	orr	r1, r0, #ABT_MODE
	msr	cpsr, r1
	ldr	sp, _stack_abt_end

	bic	r0, r0, #MODE_MASK | NO_INT
	orr	r1, r0, #IRQ_MODE
	msr	cpsr, r1
	ldr	sp, _stack_irq_end

	bic	r0, r0, #MODE_MASK | NO_INT
	orr	r1, r0, #FIQ_MODE
	msr	cpsr, r1
	ldr	sp, _stack_fiq_end

	bic	r0, r0, #MODE_MASK | NO_INT
	orr	r1, r0, #SVC_MODE
	msr	cpsr, r1
	ldr	sp, _stack_srv_end
	mov	pc, lr

    .extern __stack_und_end
    .extern __stack_abt_end
    .extern __stack_irq_end
    .extern __stack_fiq_end
    .extern __stack_srv_end

_stack_und_end:
    .word __stack_und_end
_stack_abt_end:
    .word __stack_abt_end

_stack_irq_end:
    .word __stack_irq_end
_stack_fiq_end:
    .word __stack_fiq_end
_stack_srv_end:
    .word __stack_srv_end

undefined_instruction:
	b	do_undefined_instruction

software_interrupt:
	b	do_software_interrupt

prefetch_abort:
	b	do_prefetch_abort

data_abort:
	b	do_data_abort

not_used:
	b	do_not_used

irq:
    sub lr, lr, #4
    stmfd sp!, {r0-r12, lr}

	bl	do_irq

    ldmfd sp!, {r0-r12, r15}^

fiq:
    sub lr, lr, #4
    stmfd sp!, {r0-r12, lr}

	bl	do_fiq

    ldmfd sp!, {r0-r12, r15}^

.globl enable_interrupts
enable_interrupts:
mrs r0, cpsr
bic r0, r0, #0xC0
msr cpsr_c, r0
mov pc, lr        

.end
