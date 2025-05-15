#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <stdint.h>
#include "tm4c123gh6pm.h"
void systick_init();
void systick_delay10ms(void);
void systick_delay1ms(void);
void systick_delaysec(uint8_t );
void systick_delaymsec(uint8_t delay);
#endif