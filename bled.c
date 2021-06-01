#include "bled.h"

void led_init(void){
    GPIOCALTFN0 &= ~(0X3 << 24);
    GPIOCALTFN0 |= (1<<24);
    GPIOCOUTENB |= (1<<12);
    GPIOCOUT |= (1<<12);
}
void led_on(void){
    GPIOCOUT &= ~(1<<12);
}
void led_off(void){
    GPIOCOUT |= (1<<12);
}
void led1_init(void){
    GPIOCALTFN0 &= ~(0x3<<14);
    GPIOCALTFN0 |= (1<<14);
    GPIOCOUTENB |= (1<<7);
    GPIOCOUT |= (1<<7);
}
void led1_on(void){
    GPIOCOUT &= ~(1<<7);
}
void led1_off(void){
    GPIOCOUT |= (1<<7);
}
void led2_init(void){
    GPIOCALTFN0 &= ~(0x3<<22);
    GPIOCALTFN0 |= (1<<22);
    GPIOCOUTENB |= (1<<11);
    GPIOCOUT |= (1<<11);
}
void led2_on(void){
    GPIOCOUT &= ~(1<<11);
}
void led2_off(void){
    GPIOCOUT |= (1<<11);
}

void beep_init(void){
    GPIOCALTFN0 &= ~(3<<28);
    GPIOCALTFN0 |= (1<<28);
    GPIOCOUTENB |= (1<<14);
}
void beep_on(void){
    GPIOCOUT |= (1<<14);
}
void beep_off(void){
    GPIOCOUT &= ~(1<<14);
}

