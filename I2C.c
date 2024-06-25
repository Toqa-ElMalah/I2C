#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "std_macrous.h"
#define prescalar 1

void I2C_Masterinit (unsigned long scl_clk){
	
	TWBR = (unsigned char) (((F_CPU/scl_clk)-16) / (2*prescalar));
	if (prescalar == 1){
		TWSR=0;
	}
	else if (prescalar == 4){
		TWSR=1;
	}
	else if (prescalar == 16){
		TWSR=2;
	}
	else if (prescalar == 64){
		TWSR=3;
	}
}

void I2C_start (void){
	
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while (READ_BIT(TWCR,TWINT) == 0);
	while ((TWSR & 0xF8)!=0x08); //start condition has been transmitted
}

void I2C_writeaddress (unsigned char address){
	TWDR=address;
	TWCR=(1<<TWINT) | (1<<TWEN);
	while (READ_BIT(TWCR,TWINT) == 0);
	while ((TWSR & 0xF8)!=0x18); //sla+w has been transmitted & ack has been received
}


void I2C_writedata (unsigned char data){
	TWDR=data;
	TWCR=(1<<TWINT) | (1<<TWEN);
	while (READ_BIT(TWCR,TWINT) == 0);
	while ((TWSR & 0xF8)!=0x28); //data has been transmitted & ack has been received
}

void I2C_stop (void){
	TWCR=(1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2C_setaddress (unsigned char address){
	TWAR=address;
}

unsigned char I2C_Slaveread (void){
	TWCR=(1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (READ_BIT(TWCR,TWINT) == 0);
	while ((TWSR & 0xF8)!=0x60); //own sla+w has been received & ack has been returned
	TWCR=(1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (READ_BIT(TWCR,TWINT) == 0);
	while ((TWSR & 0xF8)!=0x80); //previously addressed with own sla+w : data has been received  & ack has been returned
	return TWDR;
}
