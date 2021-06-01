/*1.告诉链接器如何组织可执行文件
 *2.描述了程序在内存中执行时的大致内存布局
 */
SECTIONS
{
    . =0x48000000;
    .text :
    {
        start.o(.text);
        *.o(.text);
    }
    .rodata :
    {
        *.o(.rodata);
    }

    . =ALIGN(4);
    .data :
    {
        *.o(.data);
    }
    . =ALIGN(4);
    __bss_start =.;
    .bss :
    {
        *.o(.bss);
    }
    __end =.;
}

