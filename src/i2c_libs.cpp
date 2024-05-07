#include <avr/io.h>
#include "i2c_libs.h"

void I2C_Libs::i2c_write(unsigned char data)
{
  TWDR = data ;
  TWCR = (1<< TWINT)|(1<<TWEN);
  while ((TWCR & (1 <<TWINT)) == 0);
}

//***************************************************
unsigned char I2C_Libs::i2c_read(unsigned char isLast)
{
  if (isLast == 0)	//send ACK
    TWCR = (1<< TWINT)|(1<<TWEN)|(1<<TWEA); //send ACK
  else			
    TWCR = (1<< TWINT)|(1<<TWEN); //send NACK
  while ((TWCR & (1 <<TWINT)) == 0);
  return TWDR;
}

void I2C_Libs::i2c_start()
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}

void I2C_Libs::i2c_stop()
{
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void I2C_Libs::i2c_init()
{
  TWSR=0x00;	//set prescaler bits  to zero
  TWBR=152;	//SCL frequency is 50K for XTAL = 16M
  TWCR=0x04;	//enable the TWI module
}
