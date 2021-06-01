
#include "uart.h"
#include "key_irq.h"
#include "interrupt.h"


void do_undefined_instruction (void)
{
    uart_puts ("undefined instruction\n\r");
    while(1);
}

void do_software_interrupt (void)
{
    uart_puts ("software interrupt\n\r");
    while(1);
}

void do_prefetch_abort (void)
{
    uart_puts ("prefetch abort\n\r");
    while(1);
}

void do_data_abort (void)
{
    uart_puts ("data abort\n\r");
    while(1);
}

void do_not_used (void)
{
    uart_puts ("not used\n\r");
    while(1);
}

void do_fiq (void)
{
    uart_puts ("fast interrupt request\n\r");
    while(1);
}

void do_irq (void)
{
    uart_puts ("IRQ: ϵͳ�ж�\n\r");

    if (GICD_ISPENDR2 & (1<<21))
    {
        do_gpioa_irq();
        GICD_ICPENDERR2 |= (1<<21);
    }
}

int interrupt_init (void)
{
    int i;
    unsigned int *ptr;

    //�ر�GIC400�ж�
    //���÷ַ�����
    GICD_CTRL &= ~3;

    //�жϷ��䵽 GROUP0
    GICD_IGROUPR0 = 0;
    GICD_IGROUPR1 = 0;
    GICD_IGROUPR2 = 0;
    GICD_IGROUPR3 = 0;
    GICD_IGROUPR4 = 0;

    //���͵��ĸ�cpu
    ptr = (unsigned int *)GICD_ITARGETSR;
    for (i = 32/4; i < 40; i++) //��8��ʼ,Ҳ����0-31����SGI,PPI��������
    {
        ptr[i] = 0x01010101; //һ������4���ж�,ȫ�����͸�CPU0
    }

    //�����ж����ȼ�
    ptr = (unsigned int *)GICD_IPRIORITYR;
    for (i = 0; i < 40; i++)
    {
        ptr[i] = 0xa0a0a0a0;
    }

    //����жϱ�־
    GICD_ICPENDERR0 = GICD_ISPENDR0;
    GICD_ICPENDERR1 = GICD_ISPENDR1;
    GICD_ICPENDERR2 = GICD_ISPENDR2;
    GICD_ICPENDERR3 = GICD_ISPENDR3;
    GICD_ICPENDERR4 = GICD_ISPENDR4;

    //GROUP0 ��IRQ�ж� FIQEN  Disabel GROUP0 GROUP1
    GICC_CTRL = 0;

    //�ж����ȼ���ֵ
    GICC_PMR = 0xF0;
    //GIC400����
    //GPIOA �ж�Դ 53
    GICD_ISENABLER2 |= (1<<21);

    //ʹ��GROUP0�ж�
    GICD_CTRL |= 1;
    GICC_CTRL |= 1;

}

