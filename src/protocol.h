#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <Arduino.h>
#define PAYLOAD_SIZE 32
String createCRTPPacket(uint8_t portID, uint8_t channelID, uint8_t linkID, String payload);
String createControlPayload(int16_t roll, int16_t pitch, int16_t yaw, int16_t throttle,
                            bool aux1, bool aux2, bool aux3, bool aux4,
                            bool aux5, bool aux6, bool aux7, bool aux8);

#endif // PROTOCOL_H