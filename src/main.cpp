#include <Arduino.h>
#include <SevSeg.h>

#define __BUFLEN 3

SevSeg sevseg;

void setup(){
	Serial.begin(9600);
	uint8_t digitPins[] = {2,3,4,5};
	uint8_t segmentPins[] = {6,7,8,9,10,11,12,13};
	sevseg.begin(COMMON_ANODE, 4, digitPins, segmentPins,false,false,true);
}

void loop(){
	uint8_t bytes[__BUFLEN];
	if(Serial.available() >= __BUFLEN){
		uint8_t bitCount = 1;
		while(Serial.available()){
			uint8_t buffer = Serial.read();
			if (buffer == 255 || bitCount > __BUFLEN){
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