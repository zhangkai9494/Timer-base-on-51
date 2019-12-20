#ifndef __LED_H__
#define __LED_H__

#include "CTypes.h"
#include "timer.h"

//显示内容的进程控制块
typedef struct
{
    uint8_t who;
    uint8_t status;
    uint8_t back;
    uint8_t mode;
}show_pcb;

extern show_pcb led_pcb;
extern uint8_t alarm_flag;

void refresh(void);
void time_add(void);
void clock_sub(void);
void alarm(void);

#endif /*__LED_H__*/

