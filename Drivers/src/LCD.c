#include "LCD.h"


void lcd_enable_pulse() {
    GPIO_Set_Pin(EN_PIN, PORT_CTRL);    // Set EN high
    systick_delaymsec(1);               // Wait 1ms
    GPIO_Clear_Pin(EN_PIN, PORT_CTRL);  // Set EN low
    systick_delaymsec(1);               // Wait 1ms
}

void lcd_send_nibble(uint8_t nibble) {
    // Clear data pins
    GPIO_Clear_Pin(D4_PIN, PORT_DATA);
    GPIO_Clear_Pin(D5_PIN, PORT_DATA);
    GPIO_Clear_Pin(D6_PIN, PORT_DATA);
    GPIO_Clear_Pin(D7_PIN, PORT_DATA);
    
    // Set data pins according to the lower 4 bits of the nibble
    if (nibble & 0x01) GPIO_Set_Pin(D4_PIN, PORT_DATA);
    if (nibble & 0x02) GPIO_Set_Pin(D5_PIN, PORT_DATA);
    if (nibble & 0x04) GPIO_Set_Pin(D6_PIN, PORT_DATA);
    if (nibble & 0x08) GPIO_Set_Pin(D7_PIN, PORT_DATA);
    
    lcd_enable_pulse();
}

void lcd_send_command(uint8_t cmd) {
    GPIO_Clear_Pin(RS_PIN, PORT_CTRL);  // RS = 0 for command
    GPIO_Clear_Pin(RW_PIN, PORT_CTRL);  // RW = 0 for write
    
    lcd_send_nibble(cmd >> 4);          // Upper nibble
    lcd_send_nibble(cmd & 0x0F);        // Lower nibble
    
    systick_delaymsec(2);               // Wait for command to complete
}

void lcd_send_char(char data) {
    GPIO_Set_Pin(RS_PIN, PORT_CTRL);    // RS = 1 for data
    GPIO_Clear_Pin(RW_PIN, PORT_CTRL);  // RW = 0 for write
    
    lcd_send_nibble(data >> 4);         // Upper nibble
    lcd_send_nibble(data & 0x0F);       // Lower nibble
    
    systick_delaymsec(2);               // Wait for data to be written
}

void lcd_send_word(const char *str) {
    uint8_t i = 0;
    while(str[i] != '\0') {
        lcd_send_char(str[i]);
        i++;
    }
}

void lcd_init() {
    // Configure GPIO pins
    const GPIO_Config GPIO_RS = {PORT_CTRL, RS_PIN, 1, 1, 0, 0, 0};
    const GPIO_Config GPIO_RW = {PORT_CTRL, RW_PIN, 1, 1, 0, 0, 0};
    const GPIO_Config GPIO_EN = {PORT_CTRL, EN_PIN, 1, 1, 0, 0, 0};
    const GPIO_Config GPIO_D4 = {PORT_DATA, D4_PIN, 1, 1, 0, 0, 0};
    const GPIO_Config GPIO_D5 = {PORT_DATA, D5_PIN, 1, 1, 0, 0, 0};
    const GPIO_Config GPIO_D6 = {PORT_DATA, D6_PIN, 1, 1, 0, 0, 0};
    const GPIO_Config GPIO_D7 = {PORT_DATA, D7_PIN, 1, 1, 0, 0, 0};
    
    GPIO_Init(&GPIO_RS);
    GPIO_Init(&GPIO_RW);
    GPIO_Init(&GPIO_EN);
    GPIO_Init(&GPIO_D4);
    GPIO_Init(&GPIO_D5);
    GPIO_Init(&GPIO_D6);
    GPIO_Init(&GPIO_D7);
    
    systick_delaymsec(50);  // Wait for LCD to power up [ 20 -> 50 ]
    
    // LCD initialization sequence (4-bit mode)
    // Send 0x3 three times (part of the LCD initialization protocol)
    lcd_send_nibble(0x03);
    systick_delaymsec(5);
    lcd_send_nibble(0x03);
    systick_delaymsec(5);
    lcd_send_nibble(0x03);
    systick_delaymsec(5);
    
    lcd_send_nibble(0x02);     // Set 4-bit mode
		systick_delaymsec(5);			 //EXTRA DELAY
    lcd_send_command(0x28);    // Function set: 4-bit, 2-line, 5x8 dots
    lcd_send_command(0x0C);    // Display ON, cursor OFF, blink OFF
    lcd_send_command(0x06);    // Entry mode: increment cursor, no display shift
    lcd_send_command(0x01);    // Clear display
    systick_delaymsec(2);      // Wait for clear to complete
}

// Additional useful functions

void lcd_clear() {
    lcd_send_command(0x01);    // Clear display command
    systick_delaymsec(2);      // Need to wait after clear command
}

void lcd_home() {
    lcd_send_command(0x02);    // Return cursor to home position
    systick_delaymsec(2);      // Need to wait after home command
}
