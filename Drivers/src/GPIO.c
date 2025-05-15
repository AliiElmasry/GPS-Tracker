#include "GPIO.h"

void GPIO_Init(const GPIO_Config	*GPIO) {
		//Enable Port Clock
		SYSCTL_RCGCGPIO_R |= (1 << GPIO->port);
		//Delay for port to be ready
		while((SYSCTL_PRGPIO_R & (1 << GPIO->port)) == 0) {};
		
		//UNLOCK PORT
		switch(GPIO->port) {
				case A:
					GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
					break;
				case B:
					GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
					break;
				case C:
					GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
					break;
				case D:
					GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
					break;
				case E:
					GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
					break;
				case F:
					GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
					break;
		}
		
		//UNLOCK PINS
		switch(GPIO->port) {
				case A:
					GPIO_PORTA_CR_R |= GPIO->pin;
					break;
				case B:
					GPIO_PORTB_CR_R |= GPIO->pin;
					break;
				case C:
					GPIO_PORTC_CR_R |= GPIO->pin;
					break;
				case D:
					GPIO_PORTD_CR_R |= GPIO->pin;
					break;
				case E:
					GPIO_PORTE_CR_R |= GPIO->pin;
					break;
				case F:
					GPIO_PORTF_CR_R |= GPIO->pin;
					break;
		}
			
		//Configure pin directions
		if (GPIO->dir) {
			switch(GPIO->port) {
				case A:
					GPIO_PORTA_DIR_R |= GPIO->pin;
					break;
				case B:
					GPIO_PORTB_DIR_R |= GPIO->pin;
					break;
				case C:
					GPIO_PORTC_DIR_R |= GPIO->pin;
					break;
				case D:
					GPIO_PORTD_DIR_R |= GPIO->pin;
					break;
				case E:
					GPIO_PORTE_DIR_R |= GPIO->pin;
					break;
				case F:
					GPIO_PORTF_DIR_R |= GPIO->pin;
					break;
			}
		} else {
			switch(GPIO->port) {
				case A:
					GPIO_PORTA_DIR_R &= ~GPIO->pin;
					break;
				case B:
					GPIO_PORTB_DIR_R &= ~GPIO->pin;
					break;
				case C:
					GPIO_PORTC_DIR_R &= ~GPIO->pin;
					break;
				case D:
					GPIO_PORTD_DIR_R &= ~GPIO->pin;
					break;
				case E:
					GPIO_PORTE_DIR_R &= ~GPIO->pin;
					break;
				case F:
					GPIO_PORTF_DIR_R &= ~GPIO->pin;
					break;
			}
		}
		
		//DIGITAL ENABLE/DISABLE
		if (GPIO->den) {
			switch(GPIO->port) {
				case A:
					GPIO_PORTA_DEN_R |= GPIO->pin;
					break;
				case B:
					GPIO_PORTB_DEN_R |= GPIO->pin;
					break;
				case C:
					GPIO_PORTC_DEN_R |= GPIO->pin;
					break;
				case D:
					GPIO_PORTD_DEN_R |= GPIO->pin;
					break;
				case E:
					GPIO_PORTE_DEN_R |= GPIO->pin;
					break;
				case F:
					GPIO_PORTF_DEN_R |= GPIO->pin;
					break;
			}
		} else {
			switch(GPIO->port) {
				case A:
					GPIO_PORTA_DEN_R &= ~GPIO->pin;
					break;
				case B:
					GPIO_PORTB_DEN_R &= ~GPIO->pin;
					break;
				case C:
					GPIO_PORTC_DEN_R &= ~GPIO->pin;
					break;
				case D:
					GPIO_PORTD_DEN_R &= ~GPIO->pin;
					break;
				case E:
					GPIO_PORTE_DEN_R &= ~GPIO->pin;
					break;
				case F:
					GPIO_PORTF_DEN_R &= ~GPIO->pin;
					break;
			}
		}
		//ANALOG ON/OFF
		if (GPIO->amsel) {
			switch(GPIO->port) {
				case A:
					GPIO_PORTA_AMSEL_R |= GPIO->pin;
					break;
				case B:
					GPIO_PORTB_AMSEL_R |= GPIO->pin;
					break;
				case C:
					GPIO_PORTC_AMSEL_R |= GPIO->pin;
					break;
				case D:
					GPIO_PORTD_AMSEL_R |= GPIO->pin;
					break;
				case E:
					GPIO_PORTE_AMSEL_R |= GPIO->pin;
					break;
				case F:
					GPIO_PORTF_AMSEL_R |= GPIO->pin;
					break;
			}
		} else {
				switch(GPIO->port) {
					case A:
						GPIO_PORTA_AMSEL_R &= ~GPIO->pin;
						break;
					case B:
						GPIO_PORTB_AMSEL_R &= ~GPIO->pin;
						break;
					case C:
						GPIO_PORTC_AMSEL_R &= ~GPIO->pin;
						break;
					case D:
						GPIO_PORTD_AMSEL_R &= ~GPIO->pin;
						break;
					case E:
						GPIO_PORTE_AMSEL_R &= ~GPIO->pin;
						break;
					case F:
						GPIO_PORTF_AMSEL_R &= ~GPIO->pin;
						break;
			}
		}
		// ALTERNATE FUNCTION ENABLE/DISABLE
		if (GPIO->afsel) {
			switch(GPIO->port) {
				case A:
					GPIO_PORTA_AFSEL_R |= GPIO->pin;
					break;
				case B:
					GPIO_PORTB_AFSEL_R |= GPIO->pin;
					break;
				case C:
					GPIO_PORTC_AFSEL_R |= GPIO->pin;
					break;
				case D:
					GPIO_PORTD_AFSEL_R |= GPIO->pin;
					break;
				case E:
					GPIO_PORTE_AFSEL_R |= GPIO->pin;
					break;
				case F:
					GPIO_PORTF_AFSEL_R |= GPIO->pin;
					break;
			}
		} else {
				switch(GPIO->port) {
					case A:
					GPIO_PORTA_AFSEL_R &= ~GPIO->pin;
					break;
				case B:
					GPIO_PORTB_AFSEL_R &= ~GPIO->pin;
					break;
				case C:
					GPIO_PORTC_AFSEL_R &= ~GPIO->pin;
					break;
				case D:
					GPIO_PORTD_AFSEL_R &= ~GPIO->pin;
					break;
				case E:
					GPIO_PORTE_AFSEL_R &= ~GPIO->pin;
					break;
				case F:
					GPIO_PORTF_AFSEL_R &= ~GPIO->pin;
					break;
			}
		}
		//PULL-UP (1) OR PULL-DOWN (2) OR NEITHER (0)
		if (GPIO->pull) {
			//Pull up
			if (GPIO->pull == 1) {
				switch(GPIO->port) {
					case A:
						GPIO_PORTA_PUR_R |= GPIO->pin;
						break;
					case B:
						GPIO_PORTB_PUR_R |= GPIO->pin;
						break;
					case C:
						GPIO_PORTC_PUR_R |= GPIO->pin;
						break;
					case D:
						GPIO_PORTD_PUR_R |= GPIO->pin;
						break;
					case E:
						GPIO_PORTE_PUR_R |= GPIO->pin;
						break;
					case F:
						GPIO_PORTF_PUR_R |= GPIO->pin;
						break;
				}
				//Pull Down
			} else if (GPIO->pull == 2) {
					switch(GPIO->port) {
						case A:
							GPIO_PORTA_PDR_R |= GPIO->pin;
							break;
						case B:
							GPIO_PORTB_PDR_R |= GPIO->pin;
							break;
						case C:
							GPIO_PORTC_PDR_R |= GPIO->pin;
							break;
						case D:
							GPIO_PORTD_PDR_R |= GPIO->pin;
							break;
						case E:
							GPIO_PORTE_PDR_R |= GPIO->pin;
							break;
						case F:
							GPIO_PORTF_PDR_R |= GPIO->pin;
							break;
				}
			} else {
					switch(GPIO->port) {
						case A:
							GPIO_PORTA_PDR_R &= ~GPIO->pin;
							break;
						case B:
							GPIO_PORTB_PDR_R &= ~GPIO->pin;
							break;
						case C:
							GPIO_PORTC_PDR_R &= ~GPIO->pin;
							break;
						case D:
							GPIO_PORTD_PDR_R &= ~GPIO->pin;
							break;
						case E:
							GPIO_PORTE_PDR_R &= ~GPIO->pin;
							break;
						case F:
							GPIO_PORTF_PDR_R &= ~GPIO->pin;
							break;
				}
			}
		}	
}


//Function to set pin HIGH
void GPIO_Set_Pin(GPIO_PIN pin, GPIO_PORT port) {
			switch(port) {
				case A:
					GPIO_PORTA_DATA_R |= pin;
					break;
				case B:
					GPIO_PORTB_DATA_R |= pin;
					break;
				case C:
					GPIO_PORTC_DATA_R |= pin;
					break;
				case D:
					GPIO_PORTD_DATA_R |= pin;
					break;
				case E:
					GPIO_PORTE_DATA_R |= pin;
					break;
				case F:
					GPIO_PORTF_DATA_R |= pin;
					break;
			}
}

//Function to set pin LOW
void GPIO_Clear_Pin(GPIO_PIN pin, GPIO_PORT port) {
			switch(port) {
				case A:
					GPIO_PORTA_DATA_R &= ~pin;
					break;
				case B:
					GPIO_PORTB_DATA_R &= ~pin;
					break;
				case C:
					GPIO_PORTC_DATA_R &= ~pin;
					break;
				case D:
					GPIO_PORTD_DATA_R &= ~pin;
					break;
				case E:
					GPIO_PORTE_DATA_R &= ~pin;
					break;
				case F:
					GPIO_PORTF_DATA_R &= ~pin;
					break;
			}
}

void GPIO_Toggle_Pin(GPIO_PIN pin, GPIO_PORT port) {

			switch(port) {
				case A:
					GPIO_PORTA_DATA_R ^= pin;
					break;
				case B:
					GPIO_PORTB_DATA_R ^= pin;
					break;
				case C:
					GPIO_PORTC_DATA_R ^= pin;
					break;
				case D:
					GPIO_PORTD_DATA_R ^= pin;
					break;
				case E:
					GPIO_PORTE_DATA_R ^= pin;
					break;
				case F:
					GPIO_PORTF_DATA_R ^= pin;
					break;
			}
}

uint8_t GPIO_Read_Pin(GPIO_PIN pin, GPIO_PORT port) {
		switch(port) {
				case A:
					return GPIO_PORTA_DATA_R & pin;
					break;
				case B:
					return GPIO_PORTB_DATA_R & pin;
					break;
				case C:
					return GPIO_PORTC_DATA_R & pin;
					break;
				case D:
					return GPIO_PORTD_DATA_R & pin;
					break;
				case E:
					return GPIO_PORTE_DATA_R & pin;
					break;
				case F:
					return GPIO_PORTF_DATA_R & pin;
					break;
			}		
}