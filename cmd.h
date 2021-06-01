#ifndef _CMD_H
#define _CMD_H

typedef void (*cb_t)(void);//函数指针
typedef struct _cmd{
    const char *name;//命令名称
    cb_t callback;//使用函数指针调用执行的函数
}cmd_t;

cmd_t *find_cmd(const char *name);

#endif
