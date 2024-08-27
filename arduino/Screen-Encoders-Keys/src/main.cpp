#include "Communication.h"

Communication comm;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);

    // Wait for the Serial Monitor to open
    while (!Serial) {
        ; // Wait for Serial to be ready
    }

    // Print a message to the Serial Monitor
    Serial.println("Communication Test Starting...");

    // Example payload: the string "Spotify"
    char payload[] = "Spotify";
    uint8_t payloadLength = strlen(payload);

    // Send a test packet
    comm.sendPacket(UPDATE_VOLUME, (uint8_t*)payload, payloadLength);
}

int i = 0; 

void loop() {
    // Continuously check for incoming packets and process them
    comm.receivePackage();
      
    
}