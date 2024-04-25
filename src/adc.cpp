#include <Arduino.h> // 包含 Arduino 函式庫，如果你使用的是其他平台，可能需要更換或修改這個包含

#include "gpio.h"
#include "adc.h"
#include <stdint.h> // Include the standard type definitions

void ADC::init()
{
    // 初始化 ADC 硬件，如果需要的話（在某些平台上，可能不需要明確初始化）
    // 例如，STM32的一些系列可能需要配置 ADC 的時鐘和分辨率
    analogReadResolution(10); // 設定 ADC 分辨率為 10 位（如果適用）
}

//< LOW HIGH >
int ADC::readYaw()
{
    return analogRead(YAW_PIN); // 讀取 YAW 引腳的 ADC 值
}
// v LOW  HIGH ^
int ADC::readThrottle()
{
    return analogRead(THR_PIN); // 讀取 THROTTLE 引腳的 ADC 值
}

// v LOW  HIGH ^
int ADC::readPitch()
{
    return analogRead(PITCH_PIN); // 讀取 PITCH 引腳的 ADC 值
}

//< LOW HIGH >
int ADC::readRoll()
{
    return analogRead(ROLL_PIN); // 讀取 ROLL 引腳的 ADC 值
}

// get all the values
void ADC::readAll(int16_t *yaw, int16_t *throttle, int16_t *pitch, int16_t *roll)
{
    *yaw = analogRead(YAW_PIN);
    *throttle = analogRead(THR_PIN);
    *pitch = analogRead(PITCH_PIN);
    *roll = analogRead(ROLL_PIN);
}