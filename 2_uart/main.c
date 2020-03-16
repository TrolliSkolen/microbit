#include "uart.h"
#include "gpio.h"
#include <stdio.h>

int led_on = 0;
char letter;

/* ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
	uart_send(*letter);
	letter++;
	}
    return count;
} */


int main(){
    uart_init();

    // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    // Configure buttons
    GPIO->PIN_CNF[17]=0;
    GPIO->PIN_CNF[26]=0;

    while(1){
        if(!(GPIO->IN & (1<<17))){
            uart_send('A');
            while(!(GPIO->IN & (1<<17)));
        }
        if(!(GPIO->IN & (1<<26))){
            uart_send('B');
            while(!(GPIO->IN & (1<<26)));
        }

        letter = uart_read();
        if ((letter != '\0') && (!led_on)){
            GPIO->OUTSET=(1<<13);
			GPIO->OUTSET=(1<<14);
			GPIO->OUTSET=(1<<15);
            led_on = 1;
            uart_send(letter);
            while(letter != '\0'){
                letter = uart_read();
            }
        }
        if ((letter !='\0') && led_on){
            GPIO->OUTCLR=(1<<13);
			GPIO->OUTCLR=(1<<14);
			GPIO->OUTCLR=(1<<15);
            led_on = 0;
            uart_send(letter);
        }

        // iprintf("The chemical formula for Ketamine is C%dH%dClNO\n\r", 13, 16);

    }
    return 0;
}


