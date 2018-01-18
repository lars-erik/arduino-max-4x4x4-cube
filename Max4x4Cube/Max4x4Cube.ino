#include "text.h"
#include "cube.h"
#include <SPI.h>
#include <math.h>
#include "max.h"
#include "cube.h"
#include "text.h"

extern bool cube[4][4][4];

bool origCube[4][4][4];
bool cubeA[4][4][4];
bool cubeB[4][4][4];
bool cubeC[4][4][4];

void rain(long milliseconds) {
	fillEmpty(cube);

	byte angle = 0;

	int fps = 18;
	int mspf = 1000 / fps;
	long times = milliseconds / mspf;
	long goSideways = times / 3 - 30;
	long goUpward = times / 3 * 2 - 30;

	for (long t = 0; t<times; t++) {
		for (byte z = 3; z>0; z--) {
			for (byte y = 0; y<4; y++) {
				for (byte x = 0; x<4; x++) {
					cube[z][y][x] = cube[z - 1][y][x];
				}
			}
		}

		for (byte y = 0; y<4; y++) {
			for (byte x = 0; x<4; x++) {
				byte score = random(0, 100);
				cube[0][y][x] = score < 10 ? 1 : 0;
			}
		}

		if (t >= goSideways && angle < 3 && t % 15 == 0) {
			angle++;
		} 
		if (t >= goUpward && angle < 6 && t % 15 == 0) {
			angle++;
		}

		rotateX(cube, cubeA, angle);
		drawCube(cubeA, mspf);

	}
}

int newAdjacent(int original) {
	int newVal;
	
	do
	{
		int step = random(0, 2) == 0 ? -1 : 1;
		newVal = original + step;
	}
	while (newVal < 0 || newVal > 3);
	
	return newVal;
}

void randomWalk(long milliseconds) {
	fillEmpty(cube);

	byte x = random(0, 4);
	byte y = random(0, 4);
	byte z = random(0, 4);

	cube[z][y][x] = 1;

	long times = milliseconds / 50;
	for (long t = 0; t<times; t++) {
		
		int dir = random(0, 3);

		cube[z][y][x] = 0;

		if (dir == 0) {
			x = newAdjacent(x);
		}
		else if (dir == 1) {
			y = newAdjacent(y);
		}
		else {
			z = newAdjacent(z);
		}
		
		cube[z][y][x] = 1;

		drawCube(cube, 50);
	}
}

byte incAngle(byte angle) {
	angle++;
	angle = angle % 12;
	return angle;
}

byte decAngle(byte angle) {
	if (angle == 0)
	{
		return 11;
	}
	angle--;
	return angle;
}

void rotatingPlane(long milliseconds) {

	byte angleY = 0;
	byte angleZ = 0;

	fillEmpty(origCube);
	for (int z = 0; z<4; z++) {
		for (int y = 0; y<4; y++) {
			for (int x = 0; x<4; x++) {
				origCube[z][y][x] = x == z ? 1 : 0;
			}
		}
	}

	int fps = 12;
	int mspf = 1000 / fps;
	long time = milliseconds / mspf;
	for (long t = 0; t<time; t++) {

		angleY = incAngle(angleY);

		if (t % 6 == 0)
		{ 
			angleZ = incAngle(angleZ);
		}

		rotateY(origCube, cubeA, angleY);
		rotateZ(cubeA, cubeB, angleZ);

		drawCube(cubeB, mspf);
	}
}

void grower(long milliseconds) {
	double angx = 0;
	double angy = 0;
	double angz = 0;

	int prev;

	int fps = 12;
	long mspf = 1000 / fps;
	long time = milliseconds / (mspf * 6);
	for (long t = 0; t<time; t++) {

		for (int max = 3; max > 1; max--) {
			fillEmpty(cube);
			for (int z = 0; z<max; z++) {
				for (int y = 0; y<max; y++) {
					for (int x = 0; x<max; x++) {
						cube[z][y][x] = 1;
					}
				}
			}

			rotateX(cube, cubeA, angx);
			rotateZ(cubeA, cubeB, angz);

			drawCube(cubeB, mspf);
		}

		for (int max = 0; max < 4; max++) {
			fillEmpty(cube);
			for (int z = 0; z <= max; z++) {
				for (int y = 0; y <= max; y++) {
					for (int x = 0; x <= max; x++) {
						cube[z][y][x] = 1;
					}
				}
			}

			rotateX(cube, cubeA, angx);
			rotateZ(cubeA, cubeB, angz);

			drawCube(cubeB, mspf);
		}

		int rnd;
		do {
			rnd = random(0, 8);
		} while (rnd == prev);

		angx = 0;
		angz = 0;

		if (rnd / 4 == 1) {
			angx = 6;
		}

		angz = (rnd % 4) * 3;
	}

}

void umbracoLogo(long milliseconds) {

	bool top[4][4] = {
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 1 },
		{ 1, 0, 0, 1 },
		{ 0, 0, 0, 0 }
	};

	bool bottom[4][4] = {
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	};

	setIntensity(0x08);

	fillEmpty(origCube);
	fillLayerWithMatrix(origCube, top, 0);
	fillLayerWithMatrix(origCube, top, 1);
	fillLayerWithMatrix(origCube, top, 2);
	fillLayerWithMatrix(origCube, bottom, 3);

	byte angx = 0;
	byte angz = 0;

	int fps = 36;
	int mspf = 1000 / fps;
	long times = milliseconds / mspf;
	long t = 0;

	int incRate = 1;
	int incFrames = 24;

	for (t = 0; t < times; t++) {

		rotateX(origCube, cubeB, angx);
		drawCube(cubeB, mspf);

		if (t % incFrames == 0) {
			incRate++;
		}

		if (t % incRate == 0) {
			angx = decAngle(angx);
		}

		if (angx == 0 && t > 60)
		{
			break;
		}
	}
	
	drawCube(cubeB, mspf * fps / 4);
	
	for (; t < times; t++) {
		if (t % 6 == 0) {
			angz = incAngle(angz);
		}
		rotateZ(origCube, cubeB, angz);
		drawCube(cubeB, mspf);
	}
}

void setup() {
	// put your setup code here, to run once:

	pinMode(A0, INPUT);
	setupSpiPins();

	SPI.begin();

	initializeDrivers();

	fillEmpty(cube);

	randomSeed(analogRead(A0));

	Serial.begin(9600);
}

void runAll() {
	setIntensity(0x1f);
	
	drawLetters(16000);

	rain(12000);
	randomWalk(6000);
	
	setIntensity(0x18);
	
	rotatingPlane(6000);
	
	setIntensity(0x04);
	
	grower(6000);
	
	setIntensity(0x0f);
	
	umbracoLogo(10000);
}

void loop() {
	runAll();
}

