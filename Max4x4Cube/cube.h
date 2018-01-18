// cube.h

#ifndef _CUBE_h
#define _CUBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

extern byte cube[4][4][4];

void drawCube(byte(*cube)[4][4], long milliseconds);
void fillEmpty(byte(*cube)[4][4]);
void fillLayerWithMatrix(byte(*cube)[4][4], byte(*matrix)[4], int z);

void rotateX(byte(*source)[4][4], byte(*target)[4][4], byte angle);
void rotateY(byte(*source)[4][4], byte(*target)[4][4], byte angle);
void rotateZ(byte(*source)[4][4], byte(*target)[4][4], byte angle);

#endif

