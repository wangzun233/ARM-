#include "cmd.h"
#include "bled.h"
#include "strcmp.h"
#include "mma8653.h"
//命令一定要带空格，否则无法调用函数
cmd_t cmd_tbl[]={
    {"led on",led_on},
    {"led off",led_off},
    {"led1 on",led1_on},
    {"led1 off",led1_off},
    {"led2 on",led2_on},
    {"led2 off",led2_off},
    {"beep on",beep_on},
    {"beep off",beep_off},
    {"mma id",mma_id},
    {"show acc",mma_acc}
};

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))
cmd_t *find_cmd(const char *name){
    int i;
    for(i=0;i<ARRAY_SIZE(cmd_tbl);i++){
        if(!my_strcmp(cmd_tbl[i].name,name)) return &cmd_tbl[i];
    }
    return 0;
}
