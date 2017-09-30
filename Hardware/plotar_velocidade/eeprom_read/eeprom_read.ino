/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it 
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>

void setup()
{
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  // read a byte from the current address of the EEPROM
  for(int i = 0; i < 256; i+= 2)
  {
    int vesq = 256 * (int) EEPROM.read(i) + (int) EEPROM.read(i + 1);
    int vdir = 256 * (int) EEPROM.read(i + 256) + (int) EEPROM.read(i + 1 + 256);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(vesq);
    Serial.print(" ");
    Serial.println(vdir);
  }
  while(1);
}
