#ifndef GPIO_H_
#define GPIO_H_
#include "tm4c123gh6pm.h"
#include "stdint.h"

typedef enum {
	A, B, C, D, E, F
} GPIO_PORT;

typedef enum {
		P0 = (1 << 0),
    P1 = (1 << 1),
    P2 = (1 << 2),
    P3 = (1 << 3),
    P4 = (1 << 4),
    P5 = (1 << 5),
    P6 = (1 << 6),
    P7 = (1 << 7),
    ALL_PINS = 0xFF
}	GPIO_PIN;

typedef struct {
		GPIO_PORT port;
		uint8_t	pin; //Pins P0 -> P7
		uint8_t dir;	//Direction 0 = input, 1 = output
		uint8_t den;	//Digital enable, 1 = enabled
		uint8_t	amsel;//Analog mode, 1 = enabled
		uint8_t	afsel;//Alternate function
		uint8_t	pull; //Pull resistors, 0= neither, 1 = pull down, 2 = pull up
} GPIO_Config;

/*******************************************************************************
*										Default Values																						 *
*******************************************************************************/
#define RED_LED     0x02           
#define BLUE_LED    0x04           
#define GREEN_LED   0x08

/*******************************************************************************
*										Function Prototypes
*******************************************************************************/
void GPIO_Init(const GPIO_Config	*Config_Ptr);
void GPIO_Set_Pin(GPIO_PIN pin, GPIO_PORT port);
void GPIO_Clear_Pin(GPIO_PIN pin, GPIO_PORT port);
void GPIO_Toggle_Pin(GPIO_PIN pin, GPIO_PORT port);
uint8_t GPIO_Read_Pin(GPIO_PIN pin, GPIO_PORT port);
#endif



