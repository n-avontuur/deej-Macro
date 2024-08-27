#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <CRC8.h>

CRC8 crc8;

enum CommandType {
    CMD_DO_SOMETHING = 0x01,  // Example command
    CMD_ANOTHER_COMMAND = 0x02
};

enum ReceiverState {
    WAIT_HEADER,
    GET_LENGTH,
    GET_COMMAND,
    GET_PAYLOAD,
    GET_CRC,
    GET_FOOTER
};


class Communication {
public:
    void Communication();
    void sendPacket(uint8_t command, uint8_t* payload, uint8_t length);
    void receivePackage();
private:
    void processCommand(uint8_t command, uint8_t* payload, uint8_t length);
    void sendAcknowledge(bool success);
    ReceiverState state = WAIT_HEADER;
    uint8_t packetLength = 0;
    uint8_t commandByte = 0;
    uint8_t payload[255];
    uint8_t payloadIndex = 0;
    uint8_t receivedCRC = 0;
};

#endif // COMMUNICATION_H
