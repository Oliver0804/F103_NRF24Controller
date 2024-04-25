#include <Arduino.h>
#include <SPI.h>
#include "main.h"
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
bool auxChannels[KEY_NUM_MAX] = {true, false, true, false, true, true, false, true}; // Example states

void byteToBoolArray(uint8_t byteVal, bool auxChannels[KEY_NUM_MAX])
{
  for (int i = 0; i < KEY_NUM_MAX; i++)
  {
    // 检查byteVal的每一位
    auxChannels[i] = byteVal & (1 << i);
  }
}

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
  byteToBoolArray(button.getCombinationKey(), auxChannels);
  joycon.readAll(&yaw, &throttle, &pitch, &roll);
  // 创建控制数据的 payload
  String payload = createControlPayload(roll, pitch, yaw, throttle, auxChannels);

  // 使用特定的端口和通道信息创建完整的CRTP数据包
  String crtpPacket = createCRTPPacket(PORT_ID, CHANNEL_ID, LINK_ID, payload);

  // 打印出CRTP数据包以便查看内容
  Serial.print("\nPacket:");
  for (int i = 0; i < payload.length(); i++)
  {
    Serial.print((uint8_t)payload[i], HEX);
    Serial.print("\t");
  }
  parseControlPayload(parseAndPrintCRTPPacket(crtpPacket));
  // parseControlPayload(payload);
  delay(1000);
}