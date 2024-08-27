#define PACKET_HEADER 0xAA    // Example header byte
#define PACKET_FOOTER 0x55    // Example footer byte

#define CRC8_POLY  0x07      // Polynomial used for CRC8 calculation


void Communication::sendPacket(uint8_t command, uint8_t* payload, uint8_t length) {
    uint8_t packetLength = length + 3; // length + command + CRC + footer
    uint8_t packet[packetLength + 3];
    packet[0] = PACKET_HEADER;
    packet[1] = packetLength;
    packet[2] = command;

    // Copy payload
    for (uint8_t i = 0; i < length; i++) {
        packet[3 + i] = payload[i];
    }

    // Calculate CRC
    crc8.reset();
    crc8.add(packet + 1, packetLength); // CRC over length, command, and payload
    uint8_t crc = crc8.getCRC();
    packet[3 + length] = crc;

    // Footer
    packet[4 + length] = PACKET_FOOTER;

    // Send the packet
    for (uint8_t i = 0; i < packetLength + 2; i++) {
        Serial.write(packet[i]);
    }
}

void Communication::processCommand(uint8_t command, uint8_t* payload, uint8_t length) {
    // Process the received command
    switch (command) {
        case CMD_DO_SOMETHING:
            // Do something with the payload
            break;
        case CMD_ANOTHER_COMMAND:
            // Do something else
            break;
        // Add more command processing as needed
    }
}

void Communication::sendAcknowledge(bool success) {
    uint8_t ackPayload[1] = {success ? 0x01 : 0x00};
    sendPacket(success ? CMD_DO_SOMETHING : CMD_ANOTHER_COMMAND, ackPayload, 1);
}

void Communucation::receivePackage(){
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
                state = (packetLength > 3) ? GET_PAYLOAD : GET_CRC;
                break;

            case GET_PAYLOAD:
                payload[payloadIndex++] = receivedByte;
                if (payloadIndex == packetLength - 3) {
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
                    crc8.add(&packetLength, packetLength - 1); // CRC over length, command, and payload
                    uint8_t calculatedCRC = crc8.getCRC();
                    if (receivedCRC == calculatedCRC) {
                        processCommand(commandByte, payload, packetLength - 3);
                        sendAcknowledge(true);
                    } else {
                        sendAcknowledge(false);
                    }
                }
                state = WAIT_HEADER;
                break;
        }
    }
}