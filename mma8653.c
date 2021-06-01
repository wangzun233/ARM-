
#include "iic.h"
#include "mma8653.h"
#include "itoa.h"

#define     SLAVE_ADDR  (0x1d)
#define     ID_REG_ADDR (0x0d)
#define     CTRL_REG1   (0x2a)
#define     OUT_X_MSB   (0x01)
#define     WFLAG       (0)
#define     RFLAG       (1)

//offset:寄存器地址
//buf：发送数据缓冲区首地址 
//len：发送字节的个数 
void mma8653_write(unsigned char offset,
                    char *buf, int len){
    //1.开始信号+写设备地址
    iic_start(SLAVE_ADDR, WFLAG);
    //2.发送要写入的寄存器地址 
    iic_tx(&offset, 1);
    //3.写入单/多字节数据
    iic_tx(buf, len);
    //4.结束信号
    iic_stop();
}



//从mma8653中读取一个或者多个字节的数据
//offset:要读取数据的寄存器地址
//buf:存储缓冲区首地址
//len:读取字节个数
void mma8653_read(unsigned char offset, char* buf, int len){
    //1.CPU发送start信号+写设备地址 
    iic_start(SLAVE_ADDR, WFLAG);
    //2.CPU发送要读取的寄存器地址（1字节）
    iic_tx(&offset, 1);
    //3.CPU发送start信号+读设备地址
    iic_start(SLAVE_ADDR, RFLAG);
    //4.CPU要读取单字节或者多字节的数据
    iic_rx(buf, len);
    //5.CPU发送stop信号
    iic_stop();
}

void mma_id(void){
    char buf[11]={0};
    unsigned char id = 0;//定义变量用于存储读取到的设备id的值 
    mma8653_read(ID_REG_ADDR, &id, 1);

    itoa(buf, id);
    uart_puts("\nID:");
    uart_puts(buf);
}

void enter_active(void){
    //定义一个变量用于读取从CTRL_REG1中所读取的数据
    unsigned char val = 0;
    //读取CTRL_REG1寄存器中数据到val变量中，读取1字节
    mma8653_read(CTRL_REG1, &val, 1);
    //将其bit[0]=1 
    val |= 1;
    //将修改完的数据写回到CTRL_REG1寄存器中 
    mma8653_write(CTRL_REG1, &val, 1);
}

//buf就是读取到的三轴加速度的值的首地址 
void show_acc(char* buf){
    int x = 0;
    int y = 0;
    int z = 0;
    int flag = 0;//if(flag==0),正数；flag==1，负数
    unsigned char itoa_buf[11] = {0};
    x = buf[0]<<24 | buf[1]<<16;
    x = x>>22;
    if(x&(1<<31)){
        x = 0-x;//此时得到的x是得到加速度的相反数，是正数
        flag = 1;
    }
    itoa(itoa_buf, x);
    uart_puts("\nX:");
    if(flag){
        uart_puts("-");
        flag = 0;
    }
    uart_puts(itoa_buf);

    y = buf[2]<<24 | buf[3]<<16;
    y = y>>22;
    if(y&(1<<31)){
        flag = 1;
        y = 0 - y;//y是读取数据的相反数，是一个正数 
    }
    itoa(itoa_buf, y);
    uart_puts("\nY: ");
    if(flag){
        uart_puts("-");
        flag = 0;
    }
    uart_puts(itoa_buf);

    z = buf[4]<<24 | buf[5]<<16;
    z = z>>22;
    if(z&(1<<31)){
        flag = 1;
        z = 0 - z;//z是读取数据的相反数，是一个正数
    }
    itoa(itoa_buf, z);
    uart_puts("\nZ: ");
    if(flag){
        uart_puts("-");
        flag = 0;
    }
    uart_puts(itoa_buf);
}

void mma_acc(void){
    unsigned char buf[6]= {0};
    //1.切换为active模式 
    enter_active();
    //2.读取三轴加速度的值 
    mma8653_read(OUT_X_MSB, buf, 6);
    //buf[0],[7:0],X[9:2]
    //buf[1],[7:6],X[1:0]
    show_acc(buf);
}




