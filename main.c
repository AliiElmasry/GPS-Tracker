#include "GPIO.h"
#include "stdint.h"
#include "stdio.h"
#include "GPS_Module.h"
#include "LCD.h"
#include "stdlib.h"
#include "floattostring.h"
#include "strintofloat.h"

#define max_led_interval 750
#define min_blinking_distance 30

//********FUNCTION PROTOTYPES & GLOBAL VARIABLES*********//
int data_out();
float min_dis=0.0;


int main(void) {	
	
	//********VARIABLE DECLARATIONS*********//
	char  str[20];
	
	uint8_t led_interval;
	
	uint8_t previous_location = 0;
	uint8_t current_location = 0;
	
	//List of pre-set locations
	char locations[12][20] = {
			"NO SIGNAL",
			"LIBRARY",
			"HALL A",
			"HALL C",
			"LUBAN ",
			"CREDIT",
			"WORKSHOPS",
			"FIELD",
			"FOUNTAIN",
			"KHRASANA",
			"OLD BUILDING",
			"MOSQUE"
	};
	// GPIO FEATURES
	GPIO_Config buzzer = {
		.port = C,
		.pin = P7,
		.dir = 1,
		.den = 1,
		.amsel = 0,
		.afsel = 0,
		.pull = 0
	};
	
	GPIO_Config leds = {
		.port = C,
		.pin = P5 | P6,	// P5 => RED LED, P6 => BLUE LED
		.dir = 1,
		.den = 1,
		.amsel = 0,
		.afsel = 0,
		.pull = 0
	};
	
	
	
	//********INITIALIZATIONS*********//
	GPIO_Init(&buzzer);	
	GPIO_Init(&leds);
	systick_init();
	lcd_init();
	lcd_clear();
	
	
	/////////////////////////////////////
	//********WHILE LOOP START*********//
	/////////////////////////////////////
	while(1){
		
		int locationIndex=data_out();	// Catch the location array index, returns index (integer) & distance to nearest location (float)
		floatToString(min_dis,str,3); // Convert distanceto string
		
		
		// If (lat,long) = (0,0) display text until signal recieved
		if (locationIndex == 0) {
			
			lcd_send_word("       NO       ");
			lcd_send_command(0xC0);
			lcd_send_word("     SIGNAL     ");
			if (GPIO_Read_Pin(P6, C) == 1) GPIO_Clear_Pin(P6, C); // Turn OFF signal indicator (RED LED)
			systick_delaysec(1);
			lcd_clear();
			continue;
			
		}
		
		if (GPIO_Read_Pin(P5, C) == 0) GPIO_Set_Pin(P5, C); // Toggle signal indicator ON (RED LED)
		
		/*Logic for buzzer*/
		
		current_location = locationIndex;
		
		if (previous_location != current_location) {
			
			previous_location = current_location; // Set previous location for use in next iteration
			
			GPIO_Set_Pin(P7, C);	//Buzzer ON
			systick_delaymsec(200); //200ms buzz-time
			GPIO_Clear_Pin(P7, C);	//Buzzer OFF
			
			systick_delaymsec(50);	//Beeping delay
			
			GPIO_Set_Pin(P7, C);	//Buzzer ON
			systick_delaymsec(200);	//200ms buzz-time
			GPIO_Clear_Pin(P7, C);	//Buzzer OFF
						
		}
		
		// Display LOCATION & DISTANCE from
		lcd_send_word(locations[locationIndex]);
		
		lcd_send_command(0xc0);	//Next LCD line
			
		lcd_send_word("Distance: ");
		lcd_send_word(str);
		
		
		/*BLINKING LED LOGIC*/
		
		if (min_dis <= min_blinking_distance) { // Detect distance to start blinking
				if (min_dis <= 1) {	
					GPIO_Set_Pin(P6, C); //Constantly on within 1m of location
				} else {
					GPIO_Clear_Pin(P6, C);
					led_interval = (uint8_t) (max_led_interval * (min_dis/min_blinking_distance)); //blinking intervals => linear relation w/ distance
					
					//Blinking @ 150ms interval 
					GPIO_Set_Pin(P6, C);
					systick_delaymsec(led_interval);
					GPIO_Clear_Pin(P6, C);
					
					systick_delaymsec(150);
					
					GPIO_Set_Pin(P6, C);
					systick_delaymsec(led_interval);
					GPIO_Clear_Pin(P6, C);
					
					systick_delaymsec(150);
					
					GPIO_Set_Pin(P6, C);
					systick_delaymsec(led_interval);
					GPIO_Clear_Pin(P6, C);
				
				}

		} else {
			GPIO_Clear_Pin(P6, C); //Turn OFF BLUE LED
		}
		systick_delaysec(2);
		lcd_clear();
		
	}
	return 0;
}
	/////////////////////////////////////
	//*********WHILE LOOP END**********//
	/////////////////////////////////////


int data_out() {
	
	
	//Default values at 0,0
	double current_lat=0.0;
	double current_long=0.0;
	//Initialize character array to store gps string
	char GPS[80];
	
	////////////[TEST CASE]/////////////
	//char GPS[80]="$GPGGA,123519,3003.80790,N,03116.78148,E,1,08,0.9,545.4,M,46.9,M,,*47";
	
	strcpy(GPS, GPS_read()); //Copy string from parsing function to pre-initialized array
	
	//Parse longitude and latitude values from string and store into variables
	current_lat=GPS_format_lattitude(GPS);
	current_long=GPS_format_longitude(GPS);

	//If GPS reads (0,0) return Location Index [0], equivalent to "NO SIGNAL"
	if (current_lat == 0.0 || current_long == 0.0) {
			return 0;
	}
	
	return NearerTo(current_lat,current_long,&min_dis);
}






