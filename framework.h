#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>    
#include <avr/power.h>    
#include <avr/sleep.h>  
#include <avr/pgmspace.h>   
#define delay(time)	_delay_ms(time);
#define interruptOn() sei();
#define interruptOff() cli();
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
#define ENABLE_SERIAl



enum m {
	OUTPUT, 
	INPUT
};

enum s {
	HIGH, 
	LOW
};


static void pinMode(uint8_t pin, uint8_t m){

if(pin<=7 ){

	if(m==INPUT){
	DDRD &= ~(1 << pin);	
	} 
	else{
		DDRD |=(1<<pin);
		}
	}

else if(pin<14){
	if(m==INPUT){
	DDRB &= ~(1 << pin-8);	
	} 
	else{
		DDRB |=(1<<pin-8);
	}
}
else{
	if(m==INPUT){
	DDRC &= ~(1 << pin-16);	
	} 
	else{
		DDRC |=(1<<pin-16);
	}
}
}


static void digitalWrite(uint8_t pin, uint8_t s) { 
	if(s==LOW){//low
    

	if(pin<=7){
		 PORTD &=~(1<<pin);
	}
	else if(pin<14){
		 PORTB &=~(1<<pin-8);
	}
	else{
		 PORTC &=~(1<<pin-16);
	}
	


	}//high
	else{

		if(pin<=7){
		 PORTD |=(1<<pin);
	}
	else if(pin<14){
		 PORTB |=(1<<pin-8);
	}
	else{
		 PORTC |=(1<<pin-16);
	}


	}
}

//static uint8_t digitalRead(uint8_t pin) {
//	uint8_t state;
//	if(pin<=7){
//		 state=((PIND & (1<<pin)));
//		 return state;
//	}
//	else if(pin<14){
//		  state=((PINB & (1<<pin-8)));
//		   return state;
//	}
//	else{
//		 state=((PINC & (1<<pin-16)));
//		 return state;
//	}
	

	

//	return 0;
//}


static void serialInit(uint16_t baud){

uint16_t _ubr = ((16000000/(16/baud))-1); 

UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);

UBRR0H = (_ubr>>8);
UBRR0L = _ubr; 


	// TODO:
}
static void serialWrite(uint8_t data){

while(!((UCSR0A)&(1<<UDRE0)));
				UDR0 = data;

	// TODO:
}
static void serialPrintStr(char *text){

int i=0;
	while( *(text+i) != '\0')
	{
		serialWrite(text[i]);
		++i;
	}

	// TODO:
}
static void serialPrintInt(uint16_t value){

	char buffer[6];
	itoa(value,buffer,10);
	serialPrintStr(buffer);


	// TODO:
}

