#include "UART.h"
void init_uart(UART_ConfigType *uartconfig)
{
	if(uartconfig->uart_num==u0){
			SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R0;
			SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R0;
			//while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);
			UART0_CTL_R &= ~UART_CTL_UARTEN;
			UART0_IBRD_R=0X68 ;
			UART0_FBRD_R=0XB ;
			if(uartconfig->bit_data == FIVE_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(uartconfig->bit_data == SIXTH_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(uartconfig->bit_data == SEVEN_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(uartconfig->bit_data == EIGHT_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }
        UART0_LCRH_R |= UART_LCRH_FEN;
        UART0_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;	GPIO_PORTA_AFSEL_R|=0X0003;
				GPIO_PORTA_AFSEL_R |= 0x01 | 0x02;                    
				GPIO_PORTA_DEN_R |= 0x01 | 0x02;                          
				GPIO_PORTA_AMSEL_R &= ~(0x01 | 0x02);                     
				GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;  
	}
else if (uartconfig->uart_num == u1_B) {
    // 1. Enable UART1 and Port B
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;   // UART1 clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;   // GPIOB clock

   // while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0); // Wait for GPIOB ready

    // 2. Configure GPIO pins PB0 (RX) and PB1 (TX)
    GPIO_PORTB_AFSEL_R |= 0x03;             // Enable alternate function on PB0, PB1
    GPIO_PORTB_DEN_R   |= 0x03;             // Digital enable for PB0, PB1
    GPIO_PORTB_AMSEL_R &= ~0x03;            // Disable analog on PB0, PB1
    GPIO_PORTB_PCTL_R  = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) | 0x00000011; // PCTL for UART

    // 3. Disable UART1 during configuration
    UART1_CTL_R &= ~UART_CTL_UARTEN;

    // 4. Set baud rate (example: 9600 bps at 16 MHz)
    UART1_IBRD_R = 0x68;
    UART1_FBRD_R = 0x0B;

    // 5. Set word length
    UART1_LCRH_R &= ~UART_LCRH_WLEN_M; // Clear word length
    if (uartconfig->bit_data == FIVE_BITS) {
        UART1_LCRH_R |= UART_LCRH_WLEN_5;
    } else if (uartconfig->bit_data == SIXTH_BITS) {
        UART1_LCRH_R |= UART_LCRH_WLEN_6;
    } else if (uartconfig->bit_data == SEVEN_BITS) {
        UART1_LCRH_R |= UART_LCRH_WLEN_7;
    } else if (uartconfig->bit_data == EIGHT_BITS) {
        UART1_LCRH_R |= UART_LCRH_WLEN_8;
    }

    UART1_LCRH_R |= UART_LCRH_FEN; // Enable FIFOs

    // 6. Enable UART1, TX and RX
    UART1_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;
}
			else if	(uartconfig->uart_num==u1_C) {
			SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R1;
			SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R2;
			//while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0);
			UART1_CTL_R &= ~UART_CTL_UARTEN;
			UART1_IBRD_R=0X68 ;
			UART1_FBRD_R=0XB ;
			if(uartconfig->bit_data == FIVE_BITS)
        {
            UART1_LCRH_R = (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(uartconfig->bit_data == SIXTH_BITS)
        {
            UART1_LCRH_R = (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(uartconfig->bit_data == SEVEN_BITS)
        {
            UART1_LCRH_R = (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(uartconfig->bit_data == EIGHT_BITS)
        {
            UART1_LCRH_R = (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }
        UART1_LCRH_R |= UART_LCRH_FEN;
        UART1_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;
				GPIO_PORTC_AFSEL_R|=0X0003;
				GPIO_PORTC_AFSEL_R |= (1>>4) | (1>>5);                    
				GPIO_PORTC_DEN_R |= (1>>4) | (1>>5);                          
				GPIO_PORTC_AMSEL_R &= ~(1>>4) | (1>>5);                     
				GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;	
	}
	else if (uartconfig->uart_num == u3) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
		while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R2) == 0) {};
    UART3_CTL_R &= ~UART_CTL_UARTEN;
    UART3_IBRD_R = 0x68;
    UART3_FBRD_R = 0x0B;

    if (uartconfig->bit_data == FIVE_BITS) {
        UART3_LCRH_R = (UART3_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_5;
    }
    else if (uartconfig->bit_data == SIXTH_BITS) {
        UART3_LCRH_R = (UART3_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_6;
    }
    else if (uartconfig->bit_data == SEVEN_BITS) {
        UART3_LCRH_R = (UART3_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_7;
    }
    else if (uartconfig->bit_data == EIGHT_BITS) {
        UART3_LCRH_R = (UART3_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_8;
    }

    UART3_LCRH_R |= UART_LCRH_FEN;

    UART3_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

    GPIO_PORTC_AFSEL_R |= 0xC0;
    GPIO_PORTC_DEN_R |= 0xC0;
    GPIO_PORTC_AMSEL_R &= ~0xC0;
		GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000;
	}
	else if (uartconfig->uart_num == u4) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R4;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
		while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R2) == 0) {};
    UART4_CTL_R &= ~UART_CTL_UARTEN;
    UART4_IBRD_R = 0x68;
    UART4_FBRD_R = 0x0B;

    if (uartconfig->bit_data == FIVE_BITS) {
        UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_5;
    }
    else if (uartconfig->bit_data == SIXTH_BITS) {
        UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_6;
    }
    else if (uartconfig->bit_data == SEVEN_BITS) {
        UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_7;
    }
    else if (uartconfig->bit_data == EIGHT_BITS) {
        UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_8;
    }

    UART4_LCRH_R |= UART_LCRH_FEN;

    UART4_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

    GPIO_PORTC_AFSEL_R |= 0x30;
    GPIO_PORTC_DEN_R |= 0x30;
    GPIO_PORTC_AMSEL_R &= ~0x30;
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00110000;
}
	else if (uartconfig->uart_num == u5) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
		while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0) {};
    UART5_CTL_R &= ~UART_CTL_UARTEN;
    UART5_IBRD_R = 0x68;
    UART5_FBRD_R = 0x0B;

    if (uartconfig->bit_data == FIVE_BITS) {
        UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_5;
    }
    else if (uartconfig->bit_data == SIXTH_BITS) {
        UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_6;
    }
    else if (uartconfig->bit_data == SEVEN_BITS) {
        UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_7;
    }
    else if (uartconfig->bit_data == EIGHT_BITS) {
        UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_8;
    }

    UART5_LCRH_R |= UART_LCRH_FEN;

    UART5_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

    GPIO_PORTE_AFSEL_R |= 0x30;
    GPIO_PORTE_DEN_R |= 0x30;
    GPIO_PORTE_AMSEL_R &= ~0x30;
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000;
}
	else if (uartconfig->uart_num == u6) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R6;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
		while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R3) == 0) {};
    UART6_CTL_R &= ~UART_CTL_UARTEN;
    UART6_IBRD_R = 0x68;
    UART6_FBRD_R = 0x0B;

    if (uartconfig->bit_data == FIVE_BITS) {
        UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_5;
    }
    else if (uartconfig->bit_data == SIXTH_BITS) {
        UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_6;
    }
    else if (uartconfig->bit_data == SEVEN_BITS) {
        UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_7;
    }
    else if (uartconfig->bit_data == EIGHT_BITS) {
        UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_8;
    }

    UART6_LCRH_R |= UART_LCRH_FEN;

    UART6_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

    GPIO_PORTD_AFSEL_R |= 0x30;
    GPIO_PORTD_DEN_R |= 0x30;
    GPIO_PORTD_AMSEL_R &= ~0x30;
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x00110000;
}


	else {
		SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
		while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0) {};
    UART7_CTL_R &= ~UART_CTL_UARTEN;
    UART7_IBRD_R = 0x68;
    UART7_FBRD_R = 0x0B;

    if (uartconfig->bit_data == FIVE_BITS) {
        UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_5;
    }
    else if (uartconfig->bit_data == SIXTH_BITS) {
        UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_6;
    }
    else if (uartconfig->bit_data == SEVEN_BITS) {
        UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_7;
    }
    else if (uartconfig->bit_data == EIGHT_BITS) {
        UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M) | UART_LCRH_WLEN_8;
    }
    UART7_LCRH_R |= UART_LCRH_FEN;
    UART7_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;
    GPIO_PORTE_AFSEL_R |= 0x3;
    GPIO_PORTE_DEN_R |= 0x3;
    GPIO_PORTE_AMSEL_R &= ~0x3;
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00)+0x00000011;	
	}
}	
void sendByte_uart (uint8_t data, UART_NUM uart_num)
{	
const GPIO_Config GPIO_RS = {F, P1, 1, 1, 0, 0, 0};
GPIO_Init(&GPIO_RS);

    if(uart_num==u0)
    {
        while((UART0_FR_R & UART_FR_TXFF) != 0);
        UART0_DR_R = data;
    }
    else if(uart_num==u1_B)
    {
        while((UART1_FR_R & UART_FR_TXFF) != 0);
        UART1_DR_R = data;
    }
    else if(uart_num==u1_C)
    {
        while((UART1_FR_R & UART_FR_TXFF) != 0);
        UART1_DR_R = data;
    }
    else if(uart_num == u3)
    {
        while((UART3_FR_R & UART_FR_TXFF) != 0);
        UART3_DR_R = data;
    }
    else if(uart_num == u4)
    {
        while((UART4_FR_R & UART_FR_TXFF) != 0);
        UART4_DR_R = data;
    }
    else if(uart_num == u5)
    {
        while((UART5_FR_R & UART_FR_TXFF) != 0);
        UART5_DR_R = data;
    }
    else if(uart_num == u6)
    {
        while((UART6_FR_R & UART_FR_TXFF) != 0);
        UART6_DR_R = data;
    }
    else
    {
        while((UART7_FR_R & UART_FR_TXFF) != 0);
        UART7_DR_R = data;
    }
	/*	if((UART1_FR_R&UART_FR_RXFE) != 0)
		{const GPIO_Config GPIO_RS = {F, P1, 1, 1, 0, 0, 0};
  GPIO_Init(&GPIO_RS);
  GPIO_Set_Pin(P1, F);
}*/
			
}
uint8_t recieveByte_uart (UART_NUM uart_num)
{		
const GPIO_Config GPIO_RS = {F, P1, 1, 1, 0, 0, 0};
GPIO_Init(&GPIO_RS);
	
		if(uart_num==u0)
    {
        while((UART0_FR_R&UART_FR_RXFE) != 0); 
        return((char)(UART0_DR_R&UART_DR_DATA_M));
			
    }
    else if(uart_num == u1_B)
    {
        while((UART1_FR_R&UART_FR_RXFE) != 0); 
				GPIO_Set_Pin(P1, F);
        return((char)(UART1_DR_R&UART_DR_DATA_M));
    }
    else if(uart_num == u1_C)
    {
        while((UART1_FR_R&UART_FR_RXFE) != 0);      
        return((char)(UART1_DR_R&UART_DR_DATA_M));
    }
    else if(uart_num == u3)
    {
        while((UART3_FR_R&UART_FR_RXFE) != 0);      
        return((char)(UART3_DR_R&UART_DR_DATA_M));
    }
    else if(uart_num == u4)
    {
        while((UART4_FR_R&UART_FR_RXFE) != 0);      
        return((char)(UART4_DR_R&UART_DR_DATA_M));
    }
    else if(uart_num == u5)
    {
        while((UART5_FR_R&UART_FR_RXFE) != 0);      
        return((char)(UART5_DR_R&UART_DR_DATA_M));
    }
    else if(uart_num == u6)
    {
        while((UART6_FR_R&UART_FR_RXFE) != 0);      
        return((char)(UART6_DR_R&UART_DR_DATA_M));
    }
    else
    {
        while((UART7_FR_R&UART_FR_RXFE) != 0);      
        return((char)(UART7_DR_R&UART_DR_DATA_M));
    }
}
void UART_sendword(char *string,UART_ConfigType *uartconfig)
{
    while(*string)
    {
        sendByte_uart(*(string++), uartconfig->uart_num);
    }
}
uint8_t UART_receiveword(char *string, UART_ConfigType *uartconfig)
{
    char ch;
    uint8_t len = 0;
        ch = recieveByte_uart(uartconfig->uart_num);
        if((ch=='\r') || (ch=='\n') || (ch==0)) 
        {
            if(len!=0)                          
            {
								string[len]=0;
            }
        }
        else if((ch=='\b') && (len!=0))
        {
            len--;                            
        }
        else
        {
						string[len]=ch;  
            len++;
        }
				 return len;
    }
