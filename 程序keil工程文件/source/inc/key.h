#ifndef __KEY_H__
#define __KEY_H__

#include "CTypes.h"
#include "led.h"

typedef struct
{
    uint8_t vlaue;  //键值
    uint8_t left_count;
//    uint8_t state;  //按键状态队列,在使用矩阵按键时扩展使用
}key_t;

typedef struct 
{
    uint8_t k1 : 1;
    uint8_t k2 : 1;
    uint8_t k3 : 2;
    uint8_t k4 : 1;
}key_flag_t;

extern key_t key;
extern key_flag_t key_flag;

void key_action(void);
void key_init(void);

#endif  /*__KEY_H__*/






















