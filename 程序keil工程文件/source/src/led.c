#include "led.h"
#include "math.h"

const uint8_t choose[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//扫描位置选择

const uint8_t value[] = {
    0xC0,0xF9,0xA4,0xB0,0x99,
    0x92,0x82,0xF8,0x80,0x98
};//数字真值

uint8_t alarm_flag = 0;

/*
* 对pcb中内容解释:
* status 0 正常切换显示    1       按键强制切换显示
* who    0 year显示          1 time显示
*/
show_pcb led_pcb;

/*
* 函数功能:年份显示
*/
void yea_show(year_t year)
{
    static uint8_t i = 0;   //计数变量
    uint8_t larg = 0,smal = 0;

    larg = (uint8_t)(year.year / 100); //数字截取
    smal = (uint8_t)(year.year % 100); //数字截取

    if(i > 7) i = 0;
    
    XBYTE[0x7f01] = choose[i];

    switch (i/2)
    {

        case 0:
            if(i % 2)XBYTE[0x7f00] = value[larg%10];
            else     XBYTE[0x7f00] = value[larg/10] ;  
            ;break;
        case 1:
            if(i % 2)XBYTE[0x7f00] = value[smal%10];
            else     XBYTE[0x7f00] = value[smal/10] ;
            break;
        case 2:
            if(i % 2)XBYTE[0x7f00] = value[year.mons%10];
            else     XBYTE[0x7f00] = value[year.mons/10] ;
            break;
        case 3:
            if(i % 2)XBYTE[0x7f00] = value[year.days%10];
            else     XBYTE[0x7f00] = value[year.days/10] ;
            break;
    }
    i++;
}

/*
* 函数功能:时间显示
*/
void tim_show(time_t time)
{
    static uint8_t i = 0;   //计数变量
    if(!led_pcb.mode && time.hou > 12) time.hou -= 12; 
    if(i > 7) i = 0;
    XBYTE[0x7f01] = choose[i];
    switch (i/2)
    {
        case 0:
            if(i % 2) XBYTE[0x7f00] = value[time.hou%10];
            else      XBYTE[0x7f00] = value[time.hou/10];
            break;
        case 1:        
            if(i % 2) XBYTE[0x7f00] = value[time.min/10];
            else      XBYTE[0x7f00] = 0xBF;                        //显示 ' - '
            break;
        case 2:
            if(i % 2) XBYTE[0x7f00] = 0xBF;                       //显示 ' - '
            else      XBYTE[0x7f00] = value[time.min%10];
            break;
        case 3:
            if(i % 2)
            {
                if(!key_flag.k4) XBYTE[0x7f00] = value[time.sec%10] & 0x7F;
                else              XBYTE[0x7f00] = value[time.sec%10];  
            }
            else     XBYTE[0x7f00] = value[time.sec/10];
            break;
    }
    i++;
}

/*普通显示*/
void nomal_show(void)
{
    if(led_pcb.who)
    {
        tim_show(time);       
    }
    else 
    {
        yea_show(year);
    }
}

/*特殊显示*/
void special_show(void)
{
     if(led_pcb.who)
     {
        tim_show(time);        
     }
     else
     {
        yea_show(year); 
     }
}

/*时钟计时*/
void time_add(void)
{
    if(++time.sec == 60) 
    {
        time.sec = 0;
        if(++time.min == 60)
        {
            time.min = 0;
            if(++time.hou == 24)
                time.hou = 0;
        }
    }
}

/*闹钟倒计时*/
void clock_sub(void)
{
    if(tim_clk.sec > 0)
    {
        tim_clk.sec--;return;
    }
    else
    {
        if(tim_clk.min > 0)
        {
            tim_clk.sec = 60;
            tim_clk.min--;
            return;
        }
        if(tim_clk.hou > 0)
        {
            tim_clk.hou--;
            tim_clk.min = 59;
            tim_clk.sec = 60;
        }
    }
}

void alarm(void)
{
    if(!key_flag.k4 && tim_clk.sec == 0 && tim_clk.min == 0 && tim_clk.hou == 0)
    {
        alarm_flag = 1;
        P17 = 0;
    }
    if(alarm_flag == 2 | key_flag.k4)
    {
        P17 = 1;
    }
}

/*
* 函数功能:数码管刷新
*/
void refresh(void)
{
    if(tim_flag.ms3)
    {
        tim_flag.ms3 = 0;
        switch(led_pcb.status)
        {
            case 0:nomal_show();break;
            case 1:special_show();break;
            default:break;
        }
    }
    
}



