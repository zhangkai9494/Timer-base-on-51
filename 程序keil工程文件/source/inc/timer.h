#ifndef __TIMER_H__
#define __TIMER_H__

#include "CTypes.h"
#include "key.h"

typedef struct
{
    uint8_t ms3   : 1;       //用于数码管刷新计时
    uint8_t s10   : 1;       //10S,切换显示时长
    uint8_t s30   : 1;       //30S 只有在闹钟响起时才有效
    uint8_t key   : 1;       //按键扫描时间到标志
    uint8_t flash : 1;       //闪烁光标时间
}Tim_flag_t;

typedef struct 
{
    uint16_t year;  //年份
    uint8_t  mons;  //月份
    uint8_t  days;  //日期
}year_t;

typedef struct
{
    uint8_t hou;    //小时
    uint8_t min;    //分钟
    uint8_t sec;    //秒
}time_t;

extern year_t year,year_m; //日期, 正在变更的日期
extern time_t time,time_m; //时间, 正在变更的时间
extern Tim_flag_t tim_flag;
extern time_t tim_clk;

void Timer0Init(void);	

#endif /*__TIMER_H__*/













