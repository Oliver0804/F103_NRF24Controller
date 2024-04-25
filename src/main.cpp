#include <Arduino.h>
#include <SPI.h>

#include "printf.h"

#include "RF24.h"
//         +-------+-------+-------+-------+
//         | ROLL  | PITCH |  YAW  |THRUST |
//         +-------+-------+-------+-------+
// Length      4       4       4       2      bytes
// Name	Byte	Size	Type	Comment
// ROLL	0-3	4	float	The pitch set-point
// PITCH	4-7	4	float	The roll set-point
// YAW	8-11	4	float	The yaw set-point
// THRUST	12-13	2	uint16_t	The thrust set-point

#include "gpio.h"
#include "buzzer.h"
#include "adc.h"
#include "button.h"

#include "eeprom.h"

RF24 radio(CE_PIN, CSN_PIN);
Buzzer buzzer;
Button button;
ADC joycon;
int yaw, throttle, pitch, roll;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Hello World");
  joycon.init();
  // eepromWriteByte(0x10, 0xA5);
  readAndPrintAllData();
  delay(1000);
}

void loop()
{
  // buzzer.play(100);
  if (button.getCombinationKeyString() != NULL)
  {
    Serial.println(button.getCombinationKeyString());
  }

  joycon.readAll(&yaw, &throttle, &pitch, &roll);
}