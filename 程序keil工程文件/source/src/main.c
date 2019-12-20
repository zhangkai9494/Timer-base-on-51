#include "led.h"
#include "timer.h"
#include "key.h"

int main(void)
{
    Timer0Init();//定时器0初始化
    key_init();//按键初始化
    XBYTE[0x7f03] = 0x80;//定义控制端口
    while(1)//主循环
    {
        key_action();//调用读取按键函数
        refresh();//刷新数码管显示
        alarm();//蜂鸣器响函数
    }
}