#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "gpio.h"
#include "buzzer.h"
#include "adc.h"
#include "button.h"
RF24 radio(CE_PIN, CSN_PIN);
Buzzer buzzer;
Button button;
ADC joycon;
int yaw, throttle, pitch, roll;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World");
  joycon.init();
}

void loop()
{
  // buzzer.play(100);
  Serial.println(button.getCombinationKeyString());
  joycon.readAll(&yaw, &throttle, &pitch, &roll);
  // Serial.print("Yaw: ");
  // Serial.print(yaw);
  // Serial.print(" Throttle: ");
  // Serial.print(throttle);
  // Serial.print(" Pitch: ");
  // Serial.print(pitch);
  // Serial.print(" Roll: ");
  // Serial.println(roll);
  // delay(1000);
}