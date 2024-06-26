#include <Arduino.h>
#include <SevSeg.h>

const uint8_t PAYLOAD_LENGTH = 2;
const uint8_t STOP_LENGTH = 1;

SevSeg sevseg;

void setup(){
	Serial.begin(9600);
	uint8_t digitPins[] = {2,3,4,5};
	uint8_t segmentPins[] = {6,7,8,9,10,11,12,13};
	sevseg.begin(COMMON_ANODE, 4, digitPins, segmentPins,0,0,1);
}

void loop(){
	const uint8_t BUFFER_LENGTH = PAYLOAD_LENGTH + STOP_LENGTH;
	uint8_t bytes[BUFFER_LENGTH];
	if(Serial.available() >= BUFFER_LENGTH){
		uint8_t bitCount = 1;
		while(Serial.available()){
			uint8_t buffer = Serial.read();
			if(buffer == 255 || bitCount > BUFFER_LENGTH){
				/*TODO: change how the "stopbyte" should be handeled!!*/
				break;
			}
			bytes[bitCount] = buffer;
			bitCount++;
		}
	}

	uint16_t zahl = bytes[1] * 100 + bytes[2];

	sevseg.setNumber(zahl, 2);
	sevseg.refreshDisplay();
}