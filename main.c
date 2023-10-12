#define ENABLE_BASIC
#include "framework.h"

uint8_t a = 0;
uint8_t b = 0;


ISR(USART_RX_vect){
    // TODO:
    b = 1;
	char value = UDR0;
    a = value;
}

int main(void) {
    pinMode(13, OUTPUT);
	serialInit(9600);
	interruptOn();
   

    while (1) {
		serialWrite('A');
		serialWrite('\n');
		serialPrintStr("Ala  kota\n");
		serialPrintInt(128);
		serialWrite('\n');
		
		serialPrintStr("Dioda LOW \n");
		digitalWrite(13, LOW);
		delay(500);
		
        	serialPrintStr("Dioda HIGH \n");
        	digitalWrite(13, HIGH);
 		delay(500);
		
       
		
		
	
		
		
		
		
    }

    return 0;
}
