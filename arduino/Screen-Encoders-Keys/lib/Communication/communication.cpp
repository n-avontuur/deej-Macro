#include "Communication.h"
#include <CRC8.h>

Communication::Communication() {
    // Initialization code if needed
}

void Communication::sendPacket(uint8_t command, uint8_t* payload, uint8_t length) {
    uint8_t packetLength = length + 2; // Command + CRC
    uint8_t packet[packetLength + 2];  // +2 for header and footer
    
    packet[0] = PACKET_HEADER;
    packet[1] = packetLength;
    packet[2] = command;

    // Copy payload
    for (uint8_t i = 0; i < length; i++) {
        packet[3 + i] = payload[i];
    }

    // Calculate CRC
    crc8.reset();
    crc8.add(packet + 2, packetLength); // CRC over command and payload
    uint8_t crc = crc8.getCRC();
    packet[3 + length] = crc;

    // Footer
    packet[4 + length] = PACKET_FOOTER;

    // Send the packet
    for (uint8_t i = 0; i < packetLength + 2; i++) {
        Serial.write(packet[i]);
    }
}

void Communication::receivePackage() {
    if (Serial.available() > 0) {
        uint8_t receivedByte = Serial.read();

        switch (state) {
            case WAIT_HEADER:
                if (receivedByte == PACKET_HEADER) {
                    state = GET_LENGTH;
                }
                break;

            case GET_LENGTH:
                packetLength = receivedByte;
                state = GET_COMMAND;
                break;

            case GET_COMMAND:
                commandByte = receivedByte;
                payloadIndex = 0;
                state = (packetLength > 2) ? GET_PAYLOAD : GET_CRC;
                break;

            case GET_PAYLOAD:
                payload[payloadIndex++] = receivedByte;
                if (payloadIndex == packetLength - 2) {  // Command + CRC
                    state = GET_CRC;
                }
                break;

            case GET_CRC:
                receivedCRC = receivedByte;
                state = GET_FOOTER;
                break;

            case GET_FOOTER:
                if (receivedByte == PACKET_FOOTER) {
                    crc8.reset();
                    crc8.add(&commandByte, packetLength - 1); // CRC over command and payload
                    uint8_t calculatedCRC = crc8.getCRC();
                    if (receivedCRC == calculatedCRC) {
                        processCommand(commandByte, payload, packetLength - 2);
                        sendAcknowledge(true);
                    } else {
                        sendAcknowledge(false);
                    }
                }
                state = WAIT_HEADER;
                packetLength = 0;
                payloadIndex = 0;
                commandByte = 0;
                receivedCRC = 0;
                break;
        }
    }
}

void Communication::processCommand(uint8_t command, uint8_t* payload, uint8_t length) {
    switch (command) {
        case RECEIVED_CONFIG:
            // Process RECEIVED_CONFIG
            break;
        case UPDATE_VOLUME:
            // Process UPDATE_VOLUME
            break;
        case CMD_ANOTHER_COMMAND:
            // Process CMD_ANOTHER_COMMAND
            break;
        // Add more cases as needed
    }
}

void Communication::sendAcknowledge(bool success) {
    uint8_t ackPayload[1] = {success ? 0x01 : 0x00};
    sendPacket(success ? RECEIVED_CONFIG : CMD_ANOTHER_COMMAND, ackPayload, 1);
}
