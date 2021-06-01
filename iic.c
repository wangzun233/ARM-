#include "iic.h"

void iic_init(void){
    //1.配置管脚为:SCL和SDA功能(复用功能选择)
    //GPIODALTFN0[15:12]=0101
    GPIODALTFN0 &= ~(3<<14 | 3<<12);//[15:12]=0000
    GPIODALTFN0 |=  (1<<14 | 1<<12);//[15:12]=0101
    //2.使能I2C时钟 
    //I2CCLKENB[3]=1
    I2CCLKENB |= (1<<3);
    //3.复位I2C控制器
    //IPRESETREG0[22]=0
    IPRESETREG0 &= ~(1<<22);//复位 
    IPRESETREG0 |= (1<<22);//取消复位
    //4.I2C控制器的配置
    //I2CCON[8:0]=1 1110 1111
    I2CCON = (1<<8)|(1<<7)|(1<<6)|(1<<5)|0X0F;
    //5.滤波器：使能、延时5个时钟周期
    //I2CLC[2:0]=101
    I2CLC = (1<<2)|1;
}

//参数:
//slave_addr:从设备地址
//rdwr:读写位 
//  ==0:写设备地址
//  ==1:读设备地址
void iic_start(unsigned char slave_addr, 
                unsigned int rdwr){
    //1.发送使能 
    I2CSTAT |= (1<<4);
    //2.使能中断、使能自动ack 
    I2CCON |= (1<<8)|(1<<7)|(1<<5);
    if(rdwr){//读设备地址
        //1.主接收模式配置
        //I2CSTAT[7:6]=10
        I2CSTAT &= ~(3<<6);
        I2CSTAT |= (1<<7);
        //2.读设备地址
        //读设备地址=设备地址<<1|1
        slave_addr = (slave_addr<<1)|1;
    }else{//写设备地址
        //1.主发送模式
        I2CSTAT |= (3<<6);
        //2.写设备地址
        slave_addr = (slave_addr<<1)|0;
    }
    //将从设备地址写入到I2CDS中 
    I2CDS = slave_addr;
    //清除中断到来位 
    I2CCON &= ~(1<<4);
    //发送start信号，然后自动发送I2CDS寄存器中的从设备地址
    I2CSTAT |= (1<<5);
    //通过判断中断是否到来判断数据是否发送成功
    //I2CCON[4]=0, &=0, !=1, 死循环
    //I2CCON[4]=1, &!=0,!=0, 跳出循环
    while(!(I2CCON&(1<<4)));
    //判断是否收到了ack信号 
    if(I2CSTAT&0X01)
        uart_puts("\nnot received ack signal");
}

void iic_stop(void){
    //发送stop信号
    I2CSTAT &= ~(1<<5);
}

//参数：
//buf：发送数据首地址
//len:要发送字节数
//buf[5]="hello";
void iic_tx(unsigned char *buf, unsigned char len){
    int count = 0;//作为循环变量
    for(; count<len; count++){
        //清除中断到来位 
        I2CCON &= ~(1<<4);
        //将要发送的字节写入到I2CDS中 
        I2CDS = buf[count];
        //I2CDS = *(buf+count) 
        //判断数据是否发送成功
        while(!(I2CCON & (1<<4)));
        //判断是否收到ack 
        if(I2CSTAT&0X01)
            uart_puts("\nnot received ack signal");
    }
}
//参数：
//buf：保存读取到的内容
//len：要读取的字节数
void iic_rx(unsigned char * buf, unsigned char len){
    int count = 0;
    while(count<len){
        if(count==(len-1)){
            //禁止自动回复ack，回复nack
            //I2CCON[7]=0
            I2CCON &= ~(1<<7);
        }
        //清除中断到来位，以避免上一个字节的影响 
        I2CCON &= ~(1<<4);
        //轮训判断数据是否接收成功
        while(!(I2CCON & (1<<4)));
        //读取数据
        buf[count]=I2CDS;
        count++;
    }
}












