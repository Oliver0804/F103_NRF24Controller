#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <Arduino.h>
#define PAYLOAD_SIZE 32
String createCRTPPacket(uint8_t portID, uint8_t channelID, uint8_t linkID, String payload);
String createControlPayload(int16_t roll, int16_t pitch, int16_t yaw, int16_t throttle,
                            const bool aux[]);
String parseAndPrintCRTPPacket(const String &crtpPacket);
void parseControlPayload(const String &payload);
#endif // PROTOCOL_H