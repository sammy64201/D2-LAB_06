/*
 * D2-LAB06.c
 *
 * Created: 3/25/2025 3:59:47 PM
 * Author : samue
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// LIBRERIAS INCLUIDAS
#include "UART/UART.h"

void setup(void){
	cli();
	initUART9600(); 
	// BOTONES
	DDRD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTD |= ((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	// INTERRUPCIONES 
	// PD2
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01);
	// PD3
	EICRA &= ~(1 << ISC00);
	EIMSK |= (1 << INT1);
	// PD4-PD7
	EICRA |= (1 << ISC11);
	EICRA &= ~(1 << ISC10);
	PCICR |= (1 << PCIE2); 
	PCMSK2 |= (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23);
	sei();
}

int main(void)
{
	setup();
	
    while (1) 
    {
		
    }
}
/*
ISR(INT0_vect){
	WriteTextUART("ARRIBA\r\n");
}

ISR(INT1_vect){
	WriteTextUART("ABAJO\r\n");
}
ISR(PCINT2_vect){
	uint8_t estado = PIND;
	
	if (!(estado & (1 << PD4))){
		WriteTextUART("IZQUIERDA\r\n");
	}
	if (!(estado & (1 << PD5))){
		WriteTextUART("DERECHA\r\n");
	}
	if (!(estado & (1 << PD6))){
		WriteTextUART("BOTON A\r\n");
	}
	if (!(estado & (1 << PD7))){
		WriteTextUART("BOTON B\r\n");
	}
}*/

ISR(INT0_vect){
	writeUART('U'); // Arriba / UP
}

ISR(INT1_vect){
	writeUART('D'); // Abajo / DOWN
}

ISR(PCINT2_vect){
	uint8_t estado = PIND;

	if (!(estado & (1 << PD4))){
		writeUART('L'); // Izquierda / LEFT
	}
	if (!(estado & (1 << PD5))){
		writeUART('R'); // Derecha / RIGHT
	}
	if (!(estado & (1 << PD6))){
		writeUART('A'); // Botón A 
	}
	if (!(estado & (1 << PD7))){
		writeUART('B'); // Botón B
	}
}
