#ifndef UART_H_
#define UART_H_
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "GPIO.h"

typedef enum
{
    FIVE_BITS,SIXTH_BITS, SEVEN_BITS, EIGHT_BITS
}UART_BIT_DATA;

typedef enum
{
    ONE_STOP_BIT, TWO_STOP_BIT
}UART_STOP_BIT;

typedef enum
{
    u0, u1_B, u1_C, u3, u4, u5, u6, u7
}UART_NUM;

typedef struct
{
    UART_BIT_DATA bit_data;
    UART_STOP_BIT stop;
    UART_NUM uart_num;
}UART_ConfigType;

void init_uart(UART_ConfigType*);
uint8_t  recieveByte_uart(UART_NUM);
void sendByte_uart (uint8_t , UART_NUM);
void UART_sendword(char*,UART_ConfigType*);
uint8_t UART_receiveword(char* ,UART_ConfigType*);

#endif 
