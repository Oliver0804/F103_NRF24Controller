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
                            bool aux1, bool aux2, bool aux3, bool aux4,
                            bool aux5, bool aux6, bool aux7, bool aux8)
{
    String payload = "";
    Serial.println(throttle);
    // 添加ROLL, PITCH, YAW, THROTTLE
    payload += char(roll & 0xFF);
    payload += char((roll >> 8) & 0xFF);
    payload += char(pitch & 0xFF);
    payload += char((pitch >> 8) & 0xFF);
    payload += char(yaw & 0xFF);
    payload += char((yaw >> 8) & 0xFF);
    payload += char(throttle & 0xFF);
    payload += char((throttle >> 8) & 0xFF);

    // 添加AUX1, AUX2, AUX3, AUX4（每个AUX用一个bit表示）
    uint8_t auxBits = 0;
    auxBits |= (aux1 & 1) << 0; // 将AUX1的状态设置在第0位
    auxBits |= (aux2 & 1) << 1; // 将AUX2的状态设置在第1位
    auxBits |= (aux3 & 1) << 2; // 将AUX3的状态设置在第2位
    auxBits |= (aux4 & 1) << 3; // 将AUX4的状态设置在第3位
    auxBits |= (aux5 & 1) << 4; // 将AUX1的状态设置在第0位
    auxBits |= (aux6 & 1) << 5; // 将AUX2的状态设置在第1位
    auxBits |= (aux7 & 1) << 6; // 将AUX3的状态设置在第2位
    auxBits |= (aux8 & 1) << 7; // 将AUX4的状态设置在第3位
    payload += char(auxBits);   // 添加压缩后的AUX状态

    return payload;
}
