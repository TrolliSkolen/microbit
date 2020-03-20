#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(){

    //Konfigurer jordingspinnene som output og sett til logisk lave
    for(int i = 4; i<=12; i++){
        GPIO->DIRSET = (1 << i);
        GPIO->OUTCLR = (1 << i);
    }

    //knapp A er pin 17
    //Når denne går fra høt til lav, skal det genereres en event
    GPIOTE->CONFIG[0] = 0x21101;
    //bit 17 =1 ,bit 16 = 0, bit 9 og 8 = 1. bit 0 = 1. 

    //konfigurere resterende 3 GPIOTE-kanaler som oppgaver koblet til hver sin LED-forsyningspinne
    //Forsyningsspenning skal veksle hver gang oppgaven aktiveres. Sett en initialverdi...
    GPIOTE->CONFIG[1] = 0x30D03;
    //PINNE 13, FORSYNINGSPINNE FOR RAD 1
    GPIOTE->CONFIG[2] = 0x30E03;
    //pinne 14, forsyningspinne for rad 2
    GPIOTE->CONFIG[3] = 0x30F03;
    //pinne 15, forsyningspinne for rad 3. Valgte initialverdi lik 0 og Toggle som polarity

    //Aktivere PPI-kanaler
    PPI->CHENSET = (1 << 0);
    PPI->CHENSET = (1 << 1);
    PPI->CHENSET = (1 << 2);

    PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
    PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

    PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
    PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

    PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
    PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

    while(1);




    return 0;
}