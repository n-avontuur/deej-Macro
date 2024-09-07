package deej

// CRC8 function calculates CRC-8 using polynomial 0x07
func calculateCRC8(data []byte) byte {
	var crc byte = 0xFF
	for _, b := range data {
		crc ^= b
		for i := 0; i < 8; i++ {
			if crc&0x80 != 0 {
				crc = (crc << 1) ^ CRC8_POLY
			} else {
				crc <<= 1
			}
		}
	}
	return crc
}

// ParsePacket parses a packet and returns header, command, payload, and CRC.
func ParsePacket(data []byte) (byte, []byte, bool) {
	if len(data) < 5 {
		return 0, nil, false
	}

	if data[0] != PACKET_HEADER || data[len(data)-1] != PACKET_FOOTER {
		return 0, nil, false
	}

	length := data[1]
	if len(data) != int(length)+4 {
		return 0, nil, false
	}

	command := data[2]
	payload := data[3 : len(data)-2]
	receivedCRC := data[len(data)-2]

	calculatedCRC := calculateCRC8(data[1 : len(data)-2])

	return command, payload, calculatedCRC == receivedCRC
}
