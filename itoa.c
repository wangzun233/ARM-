#include "itoa.h"

//0X5A
//0123456789A
//0X0000005A\0

void itoa(char buf[], unsigned int num){
    int i;
    unsigned int tmp;
    buf[0] = '0';
    buf[1] = 'X';
    i = 9;
    while(num){
        tmp = num%16;
        if(tmp >= 10){
            buf[i] = tmp-10+'A';
        }
        else{
            buf[i] = tmp + '0';
        }
        i--;
        num /= 16;
    }
    while(i>=2){
        buf[i--] = '0';
    }
    buf[10]= 0;
}
