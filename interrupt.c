
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
    uart_puts ("IRQ: 系统中断\n\r");

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

    //关闭GIC400中断
    //配置分发部分
    GICD_CTRL &= ~3;

    //中断分配到 GROUP0
    GICD_IGROUPR0 = 0;
    GICD_IGROUPR1 = 0;
    GICD_IGROUPR2 = 0;
    GICD_IGROUPR3 = 0;
    GICD_IGROUPR4 = 0;

    //发送到哪个cpu
    ptr = (unsigned int *)GICD_ITARGETSR;
    for (i = 32/4; i < 40; i++) //从8开始,也就是0-31属于SGI,PPI不管设置
    {
        ptr[i] = 0x01010101; //一次设置4个中断,全部发送给CPU0
    }

    //设置中断优先级
    ptr = (unsigned int *)GICD_IPRIORITYR;
    for (i = 0; i < 40; i++)
    {
        ptr[i] = 0xa0a0a0a0;
    }

    //清除中断标志
    GICD_ICPENDERR0 = GICD_ISPENDR0;
    GICD_ICPENDERR1 = GICD_ISPENDR1;
    GICD_ICPENDERR2 = GICD_ISPENDR2;
    GICD_ICPENDERR3 = GICD_ISPENDR3;
    GICD_ICPENDERR4 = GICD_ISPENDR4;

    //GROUP0 走IRQ中断 FIQEN  Disabel GROUP0 GROUP1
    GICC_CTRL = 0;

    //中断优先级阈值
    GICC_PMR = 0xF0;
    //GIC400配置
    //GPIOA 中断源 53
    GICD_ISENABLER2 |= (1<<21);

    //使能GROUP0中断
    GICD_CTRL |= 1;
    GICC_CTRL |= 1;

}

