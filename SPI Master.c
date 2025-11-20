/*
 * SPI.c
 *
 * Created: 20-11-2025 09:42:11 AM
 * Author : asath
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void SPI_Write(unsigned char data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

unsigned char SPI_Read()
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

int main(void)
{
	DDRB |= (1<<DDB4) | (1<<DDB5) | (1<<DDB7);  // PB4,PB5,PB7 as Output
	DDRB &= (~(1<<DDB6));
	
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);;
	SPSR &= (~(1<<SPI2X));
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB &= (~(1<<PORTB4));
		SPI_Write('a');
		PORTB |= (1<<PORTB4);
		_delay_ms(1000);
		
		PORTB &= (~(1<<PORTB4));
		SPI_Write('b');
		PORTB |= (1<<PORTB4);
		_delay_ms(1000);
    }
}

