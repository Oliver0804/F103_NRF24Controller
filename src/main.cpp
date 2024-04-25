#include <Arduino.h>
#include <SPI.h>

#include "printf.h"

#include "RF24.h"

#include "gpio.h"
#include "buzzer.h"
#include "adc.h"
#include "button.h"

#include "eeprom.h"
#include "protocol.h"

RF24 radio(CE_PIN, CSN_PIN);
Buzzer buzzer;
Button button;
ADC joycon;
int16_t yaw, throttle, pitch, roll;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
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
  // 创建控制数据的 payload
  String payload = createControlPayload(roll, pitch, yaw, throttle, false, false, false, true, false, false, false, true);

  // 使用特定的端口和通道信息创建完整的CRTP数据包
  String crtpPacket = createCRTPPacket(0x01, 0x00, 0x00, payload);

  // 打印出CRTP数据包以便查看内容
  // Serial.println("CRTP Packet:");
  for (int i = 0; i < payload.length(); i++)
  {
    Serial.print((uint8_t)payload[i], HEX);
    Serial.print(" ");
  }
  delay(1000);
}