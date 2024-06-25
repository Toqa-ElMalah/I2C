#ifndef I2C_H_
#define I2C_H_

void I2C_Masterinit (unsigned long scl_clk);
void I2C_start (void);
void I2C_writeaddress (unsigned char address);
void I2C_writedata (unsigned char data);
void I2C_stop (void);
void I2C_setaddress (unsigned char address);
unsigned char I2C_Slaveread (void);

#endif /* I2C_H_ */
