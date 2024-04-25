// EEPROMHandler.cpp
#include "eeprom.h"

void eepromWriteByte(uint8_t address, uint8_t data)
{
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((int)address); // 发送EEPROM的内部地址
    Wire.write(data);         // 发送要写入的数据
    Wire.endTransmission();
    delay(5); // 等待EEPROM完成写入
}

uint8_t eepromReadByte(uint8_t address)
{
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((int)address); // 设置EEPROM的读取地址
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_ADDRESS, 1); // 请求1字节的数据
    while (Wire.available() == 0)
        ;               // 等待数据到达
    return Wire.read(); // 读取并返回数据
}

void readAndPrintAllData()
{
    Serial.println("Reading EEPROM data...");
    Serial.println(" Addr | 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07"); // 表头
    Serial.println("-----------------------------------------------");

    for (int address = 0; address < 256; address++)
    {
        if (address % 8 == 0)
        {
            if (address != 0)
            {
                Serial.println(); // 在开始新的一行之前结束旧的一行
            }
            // 打印行首的地址
            Serial.print(" 0x");
            if (address < 16)
                Serial.print("0"); // 补充前导零
            Serial.print(address, HEX);
            Serial.print(" | ");
        }

        // 读取一个字节并打印
        uint8_t data = eepromReadByte(address);
        if (data < 16)
            Serial.print("0"); // 补充前导零使其看起来更整齐
        Serial.print(data, HEX);
        Serial.print(" ");
    }
    Serial.println(); // 确保最后一行也被正确结束
    Serial.println("-----------------------------------------------");
}
