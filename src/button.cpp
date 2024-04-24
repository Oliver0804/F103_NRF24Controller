#include "Arduino.h"
#include "button.h"
#include "gpio.h"
#define AUX1 1
#define AUX2 2
#define AUX3 8
#define AUX4 4

#define Front 128
#define Back 64
#define Left 16
#define Right 32
// Constructor
Button::Button()
{
    // Initialize the pins as inputs
    pinMode(KEY1_PIN, INPUT);
    pinMode(KEY2_PIN, INPUT);
    pinMode(KEY3_PIN, INPUT);
    pinMode(KEY4_PIN, INPUT);
    pinMode(KEY5_PIN, INPUT);
    pinMode(KEY6_PIN, INPUT);
    pinMode(KEY7_PIN, INPUT);
    pinMode(KEY8_PIN, INPUT);
}

// Get the combination key as a byte
byte Button::getCombinationKey()
{
    byte key = 0;

    // Read the state of each key pin and set the corresponding bit in the key byte
    key |= !digitalRead(KEY1_PIN) << 0;
    key |= !digitalRead(KEY2_PIN) << 1;
    key |= !digitalRead(KEY3_PIN) << 2;
    key |= !digitalRead(KEY4_PIN) << 3;
    key |= !digitalRead(KEY5_PIN) << 4;
    key |= !digitalRead(KEY6_PIN) << 5;
    key |= !digitalRead(KEY7_PIN) << 6;
    key |= !digitalRead(KEY8_PIN) << 7;

    return key;
}

// Get the combination key as a byte
String Button::getCombinationKeyString()
{
    byte key = 0;
    String keyString = "";
    // Read the state of each key pin and set the corresponding bit in the key byte
    key |= !digitalRead(KEY1_PIN) << 0;
    key |= !digitalRead(KEY2_PIN) << 1;
    key |= !digitalRead(KEY3_PIN) << 2;
    key |= !digitalRead(KEY4_PIN) << 3;
    key |= !digitalRead(KEY5_PIN) << 4;
    key |= !digitalRead(KEY6_PIN) << 5;
    key |= !digitalRead(KEY7_PIN) << 6;
    key |= !digitalRead(KEY8_PIN) << 7;

    if (key & AUX1)
    {
        keyString += "AUX1 ";
    }
    if (key & AUX2)
    {
        keyString += "AUX2 ";
    }
    if (key & AUX3)
    {
        keyString += "AUX3 ";
    }
    if (key & AUX4)
    {
        keyString += "AUX4 ";
    }
    if (key & Front)
    {
        keyString += "Front ";
    }
    if (key & Back)
    {
        keyString += "Back ";
    }
    if (key & Left)
    {
        keyString += "Left ";
    }
    if (key & Right)
    {
        keyString += "Right ";
    }

    return keyString;
}