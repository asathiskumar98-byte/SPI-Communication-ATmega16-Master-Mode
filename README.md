SPI Communication – ATmega16 (Master Mode) 🔄
Introduction

This program demonstrates SPI communication using the ATmega16 microcontroller in Master Mode.
In this example, the microcontroller sends two characters ('a' and 'b') repeatedly over SPI with a 1-second delay.
This is a basic experiment to understand SPI initialization and data transfer.

Requirements ⚙️

ATmega16

Atmel Studio 7

Proteus 8 Professional

SPI Slave device (optional for testing)

Jumper wires / simulation setup

SPI Pin Connections (ATmega16) 🔌
Pin	Function	Direction
PB5	MOSI	Output
PB6	MISO	Input
PB7	SCK	Output
PB4	SS	Output (used to control slave)
Circuit Layout (Simple Text)
ATmega16 (Master)
PB5 → MOSI → Slave MOSI
PB6 ← MISO ← Slave MISO
PB7 → SCK  → Slave SCK
PB4 → SS   → Slave SS
VCC → +5V
GND → Ground

Program Code (SPI Master) 🧑‍💻
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
    SPDR = 0xFF; // Dummy write
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

int main(void)
{
    DDRB |= (1<<DDB4) | (1<<DDB5) | (1<<DDB7);  // SS, MOSI, SCK as Outputs
    DDRB &= ~(1<<DDB6);  // MISO as Input

    SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);  // Enable SPI, Master mode
    SPSR &= ~(1<<SPI2X);  // Normal speed

    while (1)
    {
        PORTB &= ~(1<<PORTB4);   // SS LOW
        SPI_Write('a');
        PORTB |= (1<<PORTB4);    // SS HIGH
        _delay_ms(1000);

        PORTB &= ~(1<<PORTB4);   // SS LOW
        SPI_Write('b');
        PORTB |= (1<<PORTB4);    // SS HIGH
        _delay_ms(1000);
    }
}

How It Works 📘

SPI is initialized in Master Mode.

SS pin manually selects/deselects the slave.

The program sends 'a' and 'b' alternately through MOSI.

_delay_ms(1000) creates a visible timing gap for testing.

Proteus Simulation 🖥️

Place ATmega16 (Master)

Add any SPI slave (e.g., another ATmega16, shift register 74HC595, etc.)

Connect MOSI/MISO/SCK/SS pins

Load HEX file into Master

Run simulation

Output ✔️

The SPI Master transmits 'a' and 'b' continuously with 1-second delay.
Data can be monitored using virtual terminals, slave devices, or logic analyzers in Proteus.
