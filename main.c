#include "uart.h"
#include "bled.h"
#include "cmd.h"
#include "mma8653.h"
#include "iic.h"
#include "key_irq.h"
#include "interrupt.h"
static char buf[32];

void main(void){
    //硬件初始化，uart初始化
    uart_init();
    led_init();
    led1_init();
    led2_init();
    beep_init();
    iic_init();
    key_irq_init();
    interrupt_init();
    enable_interrupts();
    cmd_t *pcmd;
    while(1){
        uart_puts("\n WANGZUN:#");
        uart_gets(buf, 32);
        pcmd = find_cmd(buf);
        if(pcmd == 0) uart_puts("NO Command");
        else pcmd->callback();

    }
}
