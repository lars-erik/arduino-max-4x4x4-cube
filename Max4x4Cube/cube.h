// cube.h

#ifndef _CUBE_h
#define _CUBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

extern bool cube[4][4][4];

void drawCube(bool(*cube)[4][4], long milliseconds);
void fillEmpty(bool(*cube)[4][4]);
void fillLayerWithMatrix(bool(*cube)[4][4], bool(*matrix)[4], byte z);

void rotateX(bool(*source)[4][4], bool(*target)[4][4], byte angle);
void rotateY(bool(*source)[4][4], bool(*target)[4][4], byte angle);
void rotateZ(bool(*source)[4][4], bool(*target)[4][4], byte angle);

#endif

