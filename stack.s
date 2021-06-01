
    .bss 

    .global	__stack_und_end
    .global	__stack_und_start
__stack_und_start:
    .space 0x400
__stack_und_end:
    .space 8

    .global __stack_abt_end
    .global __stack_abt_start

__stack_abt_start:
    .space 0x400
__stack_abt_end:
    .space 8

	.global	__stack_irq_end
	.global	__stack_irq_start
__stack_irq_start:
    .space 0x400
__stack_irq_end:
    .space 8

    .global __stack_fiq_end
    .global __stack_fiq_start
__stack_fiq_start:
    .space 0x400
__stack_fiq_end:
    .space 8

    .global __stack_srv_end
    .global __stack_srv_start

__stack_srv_start:
    .space 0x400
__stack_srv_end:
    .space 8

    .end


