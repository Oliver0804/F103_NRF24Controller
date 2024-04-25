#include "protocol.h"
#include "gpio.h"
#include "main.h"
String createCRTPPacket(uint8_t portID, uint8_t channelID, uint8_t linkID, String payload)
{
    if (payload.length() > PAYLOAD_SIZE - 1)
    {
        payload = payload.substring(0, PAYLOAD_SIZE - 1); // 确保payload不超过31字节
    }

    uint8_t header = 0;
    header |= (portID & 0x0F) << 4;    // 将Port ID放在高4位
    header |= (channelID & 0x03) << 2; // 将Channel ID放在中间2位
    header |= (linkID & 0x03);         // 将Link ID放在低2位

    // 构建完整的CRTP消息
    String crtpMessage = "";
    crtpMessage += char(header); // 添加header
    crtpMessage += payload;      // 添加payload

    return crtpMessage;
}

// 定义一个函数来创建包含飞行控制数据和简化的AUX通道数据的payload

//         +-------+-------+-------+-------+
//         | ROLL  | PITCH |  YAW  |THRUST |
//         +-------+-------+-------+-------+
// Length      4       4       4       2      bytes
// Name	Byte	Size	Type	Comment
// ROLL	0-3	4	float	The pitch set-point
// PITCH	4-7	4	float	The roll set-point
// YAW	8-11	4	float	The yaw set-point
// THRUST	12-13	2	uint16_t	The thrust set-point

String createControlPayload(int16_t roll, int16_t pitch, int16_t yaw, int16_t throttle,
                            const bool aux[])
{
    String payload = "";
    // Serial.println(throttle);
    //  添加ROLL, PITCH, YAW, THROTTLE
    payload += char(roll & 0xFF);
    payload += char((roll >> 8) & 0xFF);
    payload += char(pitch & 0xFF);
    payload += char((pitch >> 8) & 0xFF);
    payload += char(yaw & 0xFF);
    payload += char((yaw >> 8) & 0xFF);
    payload += char(throttle & 0xFF);
    payload += char((throttle >> 8) & 0xFF);

    int numBytes = (KEY_NUM_MAX + 7) / 8; // Calculate the number of bytes needed
    for (int byteIndex = 0; byteIndex < numBytes; byteIndex++)
    {
        uint8_t auxBits = 0;
        for (int bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            int auxIndex = byteIndex * 8 + bitIndex;
            if (auxIndex >= KEY_NUM_MAX)
                break; // Stop if we've processed all AUX channels
            auxBits |= (aux[auxIndex] & 1) << bitIndex;
        }
        payload += char(auxBits); // Add compressed AUX state byte to payload
    }

    return payload;
}

String parseAndPrintCRTPPacket(const String &crtpPacket)
{
    if (crtpPacket.length() < 1)
    {
        Serial.println("Empty packet");
        return "";
    }

    // 提取头部字节
    uint8_t header = crtpPacket[0];

    // 解析Port ID, Channel ID, 和 Link ID
    uint8_t portID = (header >> 4) & 0x0F;    // 提取高4位
    uint8_t channelID = (header >> 2) & 0x03; // 提取中间2位
    uint8_t linkID = header & 0x03;           // 提取低2位

    // 使用 byte 数组处理 payload
    uint8_t payloadBytes[crtpPacket.length() - 1];
    for (int i = 1; i < crtpPacket.length(); i++)
    {
        payloadBytes[i - 1] = (uint8_t)crtpPacket[i];
    }

    // 打印解析结果
    Serial.println("CRTP Packet:");
    Serial.print("Header byte: 0x");
    Serial.println(header, HEX);
    Serial.print("Port ID: ");
    Serial.println(portID);
    Serial.print("Channel ID: ");
    Serial.println(channelID);
    Serial.print("Link ID: ");
    Serial.println(linkID);
    Serial.print("Payload: ");
    for (int i = 0; i < sizeof(payloadBytes); i++)
    {
        Serial.print(payloadBytes[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // 返回 payload 的十六进制表示
    String payloadHexString = "";
    Serial.println("Payload in hex:");
    for (int i = 0; i < sizeof(payloadBytes); i++)
    {
        if (payloadBytes[i] < 0x10)
        {
            payloadHexString += "0"; // 补零
        }
        payloadHexString += String(payloadBytes[i], HEX);
        Serial.print(payloadBytes[i], HEX);
        Serial.print("\t");
    }
    return payloadHexString;
}

// Function to parse the payload created by createControlPayload
void parseControlPayload(const String &payload)
{
    if (payload.length() < 8)
    {
        Serial.println("Payload is too short to contain all control data.");
        return;
    }

    // Extracting ROLL, PITCH, YAW, THROTTLE
    int16_t roll = (uint8_t)payload[0] | ((uint8_t)payload[1] << 8);
    int16_t pitch = (uint8_t)payload[2] | ((uint8_t)payload[3] << 8);
    int16_t yaw = (uint8_t)payload[4] | ((uint8_t)payload[5] << 8);
    int16_t throttle = (uint8_t)payload[6] | ((uint8_t)payload[7] << 8);

    // Print extracted values
    Serial.print("Roll: ");
    Serial.println(roll);
    Serial.print("Pitch: ");
    Serial.println(pitch);
    Serial.print("Yaw: ");
    Serial.println(yaw);
    Serial.print("Throttle: ");
    Serial.println(throttle);

    // Extracting AUX bits
    bool aux[KEY_NUM_MAX] = {false};
    int numBytes = (KEY_NUM_MAX + 7) / 8; // Calculate the number of bytes needed
    int auxIndex = 0;

    for (int byteIndex = 0; byteIndex < numBytes; byteIndex++)
    {
        if (8 + byteIndex >= payload.length())
        {
            Serial.println("Payload does not contain enough data for AUX states.");
            break;
        }
        uint8_t auxBits = payload[8 + byteIndex];
        for (int bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            if (auxIndex >= KEY_NUM_MAX)
                break; // Stop if we've processed all AUX channels
            aux[auxIndex++] = (auxBits >> bitIndex) & 1;
        }
    }

    // Print AUX states
    Serial.println("AUX States:");
    for (int i = 0; i < KEY_NUM_MAX; i++)
    {
        Serial.print("AUX");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(aux[i] ? "true" : "false");
    }
}
