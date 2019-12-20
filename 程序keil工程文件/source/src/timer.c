#include "timer.h"

year_t year = {2019,12,10},year_m = {0,0,0};
time_t time = {9,30,50},time_m = {0,0,0};
time_t tim_clk = {0,0,10};

Tim_flag_t tim_flag;    //时间标志

/*
* 函数功能:  定时器初始化
* 函数参数:无
* 函数返回:无
*/
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    
    ET0 = 1;        //开启定时器0中断
    EA = 1;         //使能总中断
}

/*
* 函数功能:定时器0中断服务函数
*/
void Timer0_interupt(void)  interrupt 1
{
    static uint32_t s1 = 0,count = 0,s10 = 0,s30 = 0;
    static uint8_t ms = 0,key_tim = 0;
    
	TL0 = 0xCD;	TH0 = 0xD4;		//重置定时器	
    ms++,key_tim++;
    if(!key_flag.k3)
    {
        s1++;
        if(!led_pcb.status)
        {
            count++;s10 = 0;
            if(count == 3000)
            {
                led_pcb.who = 1;
            }
            if(count == 10000)
            {
                count = 0;
                led_pcb.who = 0;
            }
        }
        else
        {
            s10++;
            if(s10 == 10000)
            {
                led_pcb.status = 0;
                led_pcb.who = led_pcb.back;
            }
        }
        if(s1 >= 1000)
        {
            s1 = 0;
            if(led_pcb.status != 3)
            {
                time_add();
                clock_sub();
            }
        }
    }
    if(alarm_flag == 1)
    {
        if(ms == 8)
        {
            ms = 0;
            tim_flag.ms3 = 1;   //5ms
        }
    }
    else
    {
        if(ms == 3) 
        {
            ms = 0;
            tim_flag.ms3 = 1;   //5ms
        }
    }
    if(key_tim == 50)
    {
        key_tim = 0;        //清除计数
        tim_flag.key = 1;   //按键扫描时间到
    }

    if(alarm_flag == 1)
    {
        s30++;
        if(s30 == 30000)
            tim_flag.s30 = 2;                       //30S到
    }
    else
        s30 = 0;                                    //闹钟没有开启时,不进行30S计时
}


















