#ifndef _IIC_H
#define _IIC_H
//宏定义
#define I2CCON          (*(unsigned long *)0xc00a6000)
#define I2CSTAT         (*(unsigned long *)0xc00a6004)
#define I2CADD          (*(unsigned long *)0xc00a6008)
#define I2CDS           (*(unsigned long *)0xc00a600c)
#define I2CLC           (*(unsigned long *)0xc00a6010)
//GPIO/CLOCK/IPRET
#define GPIODALTFN0     (*(unsigned long *)0xc001d020)
#define I2CCLKENB       (*(unsigned long *)0xc00b0000)
#define IPRESETREG0     (*(unsigned long *)0xc0012000)
//函数声明
extern void iic_init(void);//iic硬件初始化函数 
extern void iic_start(unsigned char, unsigned int);
extern void iic_stop(void);
extern void iic_tx(unsigned char*, unsigned char);
extern void iic_rx(unsigned char*, unsigned char);

#endif  //_IIC_H 
