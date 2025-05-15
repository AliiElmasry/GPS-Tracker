#include "systick.h"
void systick_init(void)
{
		NVIC_ST_CTRL_R = 0; 
		NVIC_ST_RELOAD_R = 0x00FFFFFF; 
		NVIC_ST_CURRENT_R = 0;
		NVIC_ST_CTRL_R = 0x00000005;	
}
void systick_delay10ms(void)
{
		NVIC_ST_RELOAD_R = (160000-1); 
		NVIC_ST_CURRENT_R = 0;
		while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
}
void systick_delay1ms(void)
{
		NVIC_ST_RELOAD_R = (16000-1); 
		NVIC_ST_CURRENT_R = 0;
		while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
}
void systick_delaysec(uint8_t delay)
{
		int x=delay*100;
		int i;
		//systick_init();

		for(i=0; i<x ; i++)
			systick_delay10ms();
}
void systick_delaymsec(uint8_t delay)
{
		int i;
		//systick_init();
		for(i=0; i<delay ; i++)
			systick_delay1ms();
}

