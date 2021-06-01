#ifndef _BLED_H
#define _BLED_H

#define GPIOCOUT    (*(unsigned long *)0XC001C000)
#define GPIOCOUTENB (*(unsigned long *)0XC001C004)
#define GPIOCALTFN0 (*(unsigned long *)0XC001C020)

extern void led_init(void);
extern void led_on(void);
extern void led_off(void);

extern void led1_init(void);
extern void led1_on(void);
extern void led1_off(void);

extern void led2_init(void);
extern void led2_on(void);
extern void led2_off(void);

extern void beep_init(void);
extern void beep_on(void);
extern void beep_off(void);

#endif
