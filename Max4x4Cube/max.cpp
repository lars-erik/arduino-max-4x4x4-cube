// 
// 
// 
#include <SPI.h>
#include "max.h"

void setupSpiPins() {
	pinMode(DATA, OUTPUT);
	pinMode(CLK, OUTPUT);
	pinMode(LATCH, OUTPUT);
	digitalWrite(LATCH, LOW);
}

void begin() {
	digitalWrite(LATCH, LOW);
}

void end() {
	digitalWrite(LATCH, HIGH);
	digitalWrite(LATCH, LOW);
}

void output(byte address, byte data)
{
	SPI.transfer(address);
	SPI.transfer(data);
}

void outputAll(byte address, byte data)
{
	begin();
	output(address, data);
	output(address, data);
	end();
}

void outputAB(byte address1, byte data1, byte address2, byte data2)
{
	begin();
	output(address1, data1);
	output(address2, data2);
	end();
}

void initializeDrivers() {
	outputAll(POWER_ON, 0x01);
	outputAll(MAX_TESTMODE, 0x00);
	outputAll(DECODE_MODE, 0x00);
	outputAll(INTENSITY, 0x0F);
	outputAll(SCAN_LIMIT, 0x03);
}

void setIntensity(byte intensity) {
	outputAll(POWER_ON, 0x01);
	outputAll(INTENSITY, intensity);
	outputAll(POWER_ON, 0x00);
}