#include "led.h"
#include "timer.h"
#include "key.h"

int main(void)
{
    Timer0Init();//��ʱ��0��ʼ��
    key_init();//������ʼ��
    XBYTE[0x7f03] = 0x80;//������ƶ˿�
    while(1)//��ѭ��
    {
        key_action();//���ö�ȡ��������
        refresh();//ˢ���������ʾ
        alarm();//�������캯��
    }
}