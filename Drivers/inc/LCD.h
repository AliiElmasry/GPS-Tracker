#ifndef LCD_H_
#define LCD_H_
#include <stdint.h>
#include "GPIO.h"
#include "systick.h"  // Include for systick functions
#include <string.h>
#include "tm4c123gh6pm.h"
#define RS_PIN P5  // PA5
#define RW_PIN P6  // PA6
#define EN_PIN P7  // PA7
#define PORT_CTRL A

#define D4_PIN P0  // PB4
#define D5_PIN P1  // PB5
#define D6_PIN P2  // PB6
#define D7_PIN P3  // PB7
#define PORT_DATA D
void delayMs(uint32_t time);
void lcd_enable_pulse();
void lcd_send_nibble(uint8_t nibble);
void lcd_send_command(uint8_t cmd);
void lcd_send_char(char data);
void lcd_send_word(const char *Str);
void lcd_init();
void lcd_clear();
void lcd_home();
#endif