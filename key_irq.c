
#include "interrupt.h"
#include "uart.h"
#include "key_irq.h"

//GPIOA 28 SW6 KEY?
//
void do_gpioa_irq(void)
{
    uart_puts("\n\rIRQ: 中断成功！！！ \n\r");

    GPIOA_DET |= (1<<28);
    
    uart_puts("\n\rIRQ: 按回车继续/继续输入指令\n：\r");
}

void key_irq_init(void)
{

    GPIOA_INTENB &= ~(1<<28);
    GPIOA_ALTFN1 &= ~(3<<(24));
    GPIOA_OUTEN &= ~(1<<28);

    //清除检测标志位
    GPIOA_DET |= (1<<28);

    //检测下降沿事件，使能检测
    GPIOA_DETMODE1 = (GPIOA_DETMODE1 & ~(3<<24)) | (2<<24);
    GPIOA_DETMODEEX &=  ~(1<<28);
    GPIOA_DETENB |= (1<<28);




    GPIOA_INTENB |= (1<<28);


}
