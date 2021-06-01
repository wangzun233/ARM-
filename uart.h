#ifndef     _UART_H 
#define     _UART_H
//声明寄存器
//UART
#define     ULCON0      (*(unsigned long *)0XC00A1000)
#define     UCON0       (*(unsigned long *)0XC00A1004)
#define     UTRSTAT0    (*(unsigned long *)0XC00A1010)
#define     UTXH0       (*(unsigned long *)0XC00A1020)
#define     URXH0       (*(unsigned long *)0XC00A1024)
#define     UBRDIV0     (*(unsigned long *)0XC00A1028)
#define     UFRACVAL0   (*(unsigned long *)0XC00A102C)
//GPIO
#define     GPIODALTFN0 (*(unsigned long *)0XC001D020)
#define     GPIODALTFN1 (*(unsigned long *)0XC001D024)
//CLOCK
#define     UARTCLKENB  (*(unsigned long *)0XC00A9000)
#define     UARTCLKGEN0L (*(unsigned long *)0XC00A9004)
//函数声明
extern void uart_init(void);
extern void uart_putc(char c);
extern void uart_puts(char* str);
extern char uart_getc(void);//读取一个字符
extern void uart_gets(char buf[], int len);//读取一个字符串 

#endif
