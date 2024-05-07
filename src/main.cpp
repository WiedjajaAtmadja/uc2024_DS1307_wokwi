#include <Arduino.h>
#include "i2c_libs.h"

I2C_Libs i2c;

void ds1703_setTime(uint8_t h, uint8_t m, uint8_t s)
{
  i2c.i2c_start();
  i2c.i2c_write(0xD0); // DS1307 address
  i2c.i2c_write(0);
  i2c.i2c_write(s);
  i2c.i2c_write(m);
  i2c.i2c_write(h);
  i2c.i2c_stop();
}

void ds1703_getTime(uint8_t *h, uint8_t *m, uint8_t *s)
{
  i2c.i2c_start();
  i2c.i2c_write(0xD0); // DS1307 address
  i2c.i2c_write(0);
  i2c.i2c_start();
  i2c.i2c_write(0xD1); // DS1307 address
  *s = i2c.i2c_read(0);
  *m = i2c.i2c_read(0);
  *h = i2c.i2c_read(1);
  i2c.i2c_stop();
} 

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  i2c.i2c_init();
  ds1703_setTime(12, 30, 0);
}

void loop() {
  uint8_t h, m, s;
  ds1703_getTime(&h, &m, &s);
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.println(s);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(900);
}
