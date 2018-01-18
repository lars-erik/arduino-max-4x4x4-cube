// max.h

#ifndef _MAX_h
#define _MAX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define CLK 13
#define DATA 11
#define LATCH 10

#define NOOP 0x00
#define D0 0x01
#define D1 0x02
#define D2 0x03
#define D3 0x04
#define D4 0x05
#define D5 0x06
#define D6 0x07
#define D7 0x08
#define DECODE_MODE 0x09
#define INTENSITY 0x0A
#define SCAN_LIMIT 0x0B
#define POWER_ON 0x0C
#define MAX_TESTMODE 0x0F

void setupSpiPins();
void initializeDrivers();

void output(byte address, byte data);
void outputAll(byte address, byte data);
void outputAB(byte address1, byte data1, byte address2, byte data2);
void setIntensity(byte intensity);

#endif

