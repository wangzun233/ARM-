# ARM-
ARM裸板开发完整代码，控制LED、蜂鸣器、三轴加速传感器、按键中断、shell框架、Makefile编写

| 文件名称    | 功能                            |
| ----------- | ------------------------------- |
| bled.c      | 控制LED、蜂鸣器                 |
| cmd.c       | 判断输入的函数，执行对应的功能  |
| iic.c       | 获取mma8653三轴速度传感器设备ID |
| interrupt.c | 各种系统中断                    |
| itoa.c      | 转换成字符串                    |
| key_irq.c   | 按键设置IRQ中断                 |
| mma8653.c   | 获取mma8653X、Y、Z轴的各项数据  |
| stack.s     | 配置各种系统中断                |
| start.s     | 配置各种系统中断                |
| strcmp.c    | 字符串比较                      |
| strcmp.s    | 字符串比较                      |
| uart.c      | 各种输入输出函数功能            |
| main.c      | 功能调用                        |
| shell.lds   | 配置Makefile                    |

