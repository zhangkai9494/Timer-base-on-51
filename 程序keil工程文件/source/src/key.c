#include "key.h"

key_t key;
key_flag_t key_flag;

/*
* 函数功能:按键初始化
* 函数参数:无
* 函数返回:无
*/
void key_init(void)
{
    P10 = 1;
    P11 = 1;
    P12 = 1;
    P13 = 1;
}

/*
* 函数功能:读取按键键值
* 函数参数:无
* 函数返回:按下的键值
*/
static uint8_t read_key(void)
{
    if(P10 == 0) return 1;
    if(P11 == 0) return 2;
    if(P12 == 0) return 3;
    if(P13 == 0) return 4;       //按键按下记录键值
    return 0;                   //没有按键按下返回0
}

/*
* 函数功能:按下按键消抖确认
* 函数参数:无
* 函数返回:无
* 注:因为程序简单,按键放在主循环,
*    当程序复杂可以直接放在中断提
*    高按键实时性
*/
static void cfm_key(void)
{
    static uint8_t mand;
    uint8_t buf = 0;
    if(tim_flag.key)
    {
        tim_flag.key = 0;          //记录值清零
        buf = read_key();
        if(mand == buf) 
        {
            key.vlaue = mand;       //确认按键按下,记录键值
            mand = 0;
        }
        else
        {
            mand = buf;             //更改记录值
        }
    }
}

/*
* 函数功能:按键1动作
* 执行日期时间切换操作
*/
void k1_act(void)
{
    led_pcb.back = led_pcb.who;
    led_pcb.status = 1;
    if(led_pcb.who) led_pcb.who = 0;
    else            led_pcb.who = 1;
    key.vlaue = 0;
    if(alarm_flag) alarm_flag = 2;
}

/*
* 函数功能:按键2动作
* 12/24 小时显示切换键
*/
void k2_act(void)
{
    if(led_pcb.mode)
    {
        led_pcb.mode = 0;
    }
    else 
    {
        led_pcb.mode = 1;
    }
    key.vlaue = 0;
    if(alarm_flag) alarm_flag = 2;
}

/*
* 函数功能:按键3动作
* 修改时间,日期功能键
*/
void k3_act(void)
{
    if(key.vlaue == 3)
    {
        key_flag.k3 += 1;
        if(key_flag.k3 == 3)
            key_flag.k3 = 0;
        if(alarm_flag) alarm_flag = 2;
        key.left_count = 0;
        key.vlaue = 0;
    }
}

/*
* 函数功能:按键4动作
* 闹钟功能开关控制键
*/
void k4_act(void)
{
    key_flag.k4 = !key_flag.k4;
    key.vlaue = 0;
    alarm_flag = 0;
}

/*K1 修改参数时移动光标*/
void k1_chang(void)
{
    key.vlaue = 0;
    if(++key.left_count >= 7)
    {
        key.left_count = 0;
    }
}

/*K2 修改参数*/
void k2_chang(void)
{
    switch (key.left_count)
    {
        case 1:year_m.year++;break;
        case 2:year_m.mons++;break;
        case 3:year_m.days++;break;
        case 4:time_m.hou++;break;
        case 5:time_m.min++;break;
        case 6:time_m.sec++;break;
        default:break;
    }
    key.vlaue = 0;
}

/*K4 确认修改*/
void k4_sure(void)
{
    year.days = year_m.days;
    year.mons = year_m.mons;
    year.year = year_m.year;
    time.hou = time_m.hou;
    time.min = time_m.min;
    time.sec = time_m.sec;
    key_flag.k3 = 0;
    key.left_count = 0;
    key.vlaue = 0;
}

/*对日期,年份,定时时间进行修改*/
void change_num(void)
{
    switch(key.vlaue)
    {
        case 1:k1_chang();break;
        case 2:k2_chang();break;
        case 3:key_flag.k3++;key.vlaue = 0;break;
        case 4:k4_sure();break;
        default:break;
    }
}

/*
* 函数功能:执行按键对应操作
* 函数参数:无
* 函数返回:无
*/
void key_action(void)
{
    cfm_key();          //执行按键获取操作

    if(key_flag.k3 == 1)     //处于参数修改模式
    {
        change_num();
    }
    else if(key_flag.k3 == 0)
    {
        switch (key.vlaue)
        {
            case 1:k1_act();break;
            case 2:k2_act();break;
            case 4:k4_act();break;
            default: break;
        }
    }
    k3_act();
}





















