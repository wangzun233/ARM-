#include "uart.h"

//初始化函数定义
void uart_init(void){
    //1.先关闭时钟，待配置完成后再打开时钟
    UARTCLKENB &= ~(1<<2);
    //2.引脚配置为UARTTXD0和UARTRXD0
    //GPIODALTFN1[5:4]=01-->UARTTXD0
    //GPIODALTFN0[29:28]=01--->UARTRXD0
    GPIODALTFN1 &= ~(3<<4);//[5:4]=00
    GPIODALTFN1 |= (1<<4); //[5:4]=01
    GPIODALTFN0 &= ~(3<<28);//[29:28]=00
    GPIODALTFN0 |= (1<<28);//[29:28]=01
    //3.数据线配置：ULCON0
    //7654 3210 BIT位 
    //0000 0011
    ULCON0 = 3;//0000 0000 0000 0011
    //4.读写配置：UCON0 
    //7654 3210
    //0000 0101
    UCON0 = 5;//0000 0101 
    //5.波特率配置
    //5.1.时钟配置
    //UARTCLKGEN0L[4:2]=000,配置时钟源为PLL[0]
    UARTCLKGEN0L &= ~(7<<2);
    //输入时钟源为800MHz，想要目的时钟SCLK_UART=50MHz,此时分频系数为16
    //分频系数n=UARTCLKGEN0L[12:5]+1 [12:5]=15=0000 1111
    UARTCLKGEN0L &= ~(0xff<<5);//[12:5]=0000 0000
    //UARTCLKGEN0L &= ~(0XF<<9);
    UARTCLKGEN0L |= (0xf<<5);//[12:5]=0000 1111 
    //5.2.UBRDIV0和UFRACVAL0配置
    //配置得到bps=115200 
    UBRDIV0 = 26;
    UFRACVAL0 = 2;
    //6.打开时钟
    UARTCLKENB |= (1<<2);
}

//发送字符函数
//参数，c：想要发送的字符
void uart_putc(char c){
    //[1]=0,死循环
    //[1]=1,跳出循环 
    while(!(UTRSTAT0 & 0X02));
    //将要发送的字符放到发送缓冲区上即可 
    UTXH0 = c;
    //若发送‘\n'字符，追加'\r'字符
    if(c == '\n')
        uart_putc('\r');
}

//发送字符串函数
//参数：str，想要发送的字符串
//char *str = "hello,world\n";'\0'
void uart_puts(char *str){
    while(*str){
        uart_putc(*str);
        str++;//地址加1，表示下一个字符的地址
    }
}

//读取字符函数定义
char uart_getc(void){
    //[0]=0,接收缓冲区没有数据，轮训死等，陷入死循环
    //[0]=1,接收缓冲区中有数据，读取数据，跳出死循环
    while(!(UTRSTAT0&0X01));
    //返回读取到的字符
    return URXH0&0XFF;
}

//读取字符串函数定义 
//char buf[32]; uart_gets(buf, 32);
//最多读取31个字符，[31]='\0'
void uart_gets(char buf[], int len){
    int i;
    for(i=0;i<len-1;i++){
        buf[i] = uart_getc();
        //添加回显
        uart_putc(buf[i]);
        if(buf[i] == '\r')
            break;
    }
    buf[i] = '\0';
}









