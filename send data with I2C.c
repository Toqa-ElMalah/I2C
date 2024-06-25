/*
 * send_data_with_I2C.c
 */ 


#include <avr/io.h>
#include "I2C.h"
#define F_CPU 8000000UL
#include "util/delay.h"

int main(void){
	
	char counter=0;
	I2C_Masterinit(50000);
	
    while(counter<10){
		
		_delay_ms(500);
		I2C_start();
		I2C_writeaddress(0b11100000);
		I2C_writedata(counter+48);
		I2C_stop();
		counter++;
    }
}