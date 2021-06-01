
#ifndef __KEY_IRQ_H__
#define __KEY_IRQ_H__

#define GPIOA_OUTEN    (*((volatile unsigned int *)0xC001A004))
#define GPIOA_DETMODE0  (*((volatile unsigned int *)0xC001A008))
#define GPIOA_DETMODE1  (*((volatile unsigned int *)0xC001A00C))
#define GPIOA_INTENB    (*((volatile unsigned int *)0xC001A010))
#define GPIOA_DET       (*((volatile unsigned int *)0xC001A014))
#define GPIOA_PAD       (*((volatile unsigned int *)0xC001A018))

#define GPIOA_ALTFN0   (*((volatile unsigned int *)0xC001A020))
#define GPIOA_ALTFN1   (*((volatile unsigned int *)0xC001A024))

#define GPIOA_DETMODEEX (*((volatile unsigned int *)0xC001A028))
#define GPIOA_DETENB    (*((volatile unsigned int *)0xC001A03C))

#define GPIOA_PULLSEL  (*((volatile unsigned int *)0xC001A058))
#define GPIOA_PULLENB  (*((volatile unsigned int *)0xC001A060))


extern void do_gpioa_irq(void);

extern void key_irq_init(void);

extern void do_key_irq(void);

#endif //__KEY_IRQ_H__
