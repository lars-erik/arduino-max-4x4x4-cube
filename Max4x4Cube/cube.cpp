// 
// 
// 
#include "max.h"
#include "cube.h"

byte empty[4][4] = {
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }
};

byte cube[4][4][4];

float minAngle = PI / 6;
float cosVals[] = { 1, .866,	.5,	0, -.5, -.866, -1, -.866, -.5, 0, .5, .866 };
float sinVals[] = { 0, .5, .866, 1, .866, .5, 0, -.5, -.866, -1, -.866, -.5, 0 };
float negSinVals[] = { 0, -.5, -.866, -1, -.866, -.5, 0, .5, .866, 1, .866, .5, 0 };

void setBits(word layer1, word layer2, word layer3, word layer4) {
	outputAB(POWER_ON, 1, POWER_ON, 0);
	outputAB(1, layer1, 0, 0);
	outputAB(2, layer2, 0, 0);
	outputAB(3, layer3, 0, 0);
	outputAB(4, layer4, 0, 0);
	delayMicroseconds(10);
	outputAB(POWER_ON, 0, POWER_ON, 1);
	outputAB(0, 0, 1, layer1 >> 8);
	outputAB(0, 0, 2, layer2 >> 8);
	outputAB(0, 0, 3, layer3 >> 8);
	outputAB(0, 0, 4, layer4 >> 8);
	delayMicroseconds(10);
}

void draw(word layer1, word layer2, word layer3, word layer4, long milliseconds) {
	long times = milliseconds * 5;
	for (long i = 0; i<times; i++) {
		setBits(layer1, layer2, layer3, layer4);
	}
}

void fillLayerWithMatrix(byte(*cube)[4][4], byte(*matrix)[4], int z) {
	for (byte x = 0; x<4; x++) {
		for (byte y = 0; y<4; y++) {
			cube[z][y][x] = matrix[y][x];
		}
	}
}

void fillEmpty(byte(*cube)[4][4]) {
	fillLayerWithMatrix(cube, empty, 0);
	fillLayerWithMatrix(cube, empty, 1);
	fillLayerWithMatrix(cube, empty, 2);
	fillLayerWithMatrix(cube, empty, 3);
}

void multiply(byte(*source)[4][4], byte(*target)[4][4], float(*by)[3]) {
	fillEmpty(target);

	for (int z = 0; z<4; z++) {
		for (int y = 0; y<4; y++) {
			for (int x = 0; x<4; x++) {
				if (source[z][y][x] == 0) {
					continue;
				}

				float vector[3];
				vector[0] = x - 1.5;
				vector[1] = y - 1.5;
				vector[2] = z - 1.5;

				int newVector[3];

				newVector[0] = constrain(round(by[0][0] * vector[0] + by[0][1] * vector[1] + by[0][2] * vector[2] + 1.5), 0, 3);
				newVector[1] = constrain(round(by[1][0] * vector[0] + by[1][1] * vector[1] + by[1][2] * vector[2] + 1.5), 0, 3);
				newVector[2] = constrain(round(by[2][0] * vector[0] + by[2][1] * vector[1] + by[2][2] * vector[2] + 1.5), 0, 3);

				target[newVector[2]][newVector[1]][newVector[0]] = 1;
			}
		}
	}
}

void rotateX(byte(*source)[4][4], byte(*target)[4][4], byte angle) {
	fillEmpty(target);

	for (int z = 0; z<4; z++) {
		for (int y = 0; y<4; y++) {
			for (int x = 0; x<4; x++) {
				if (source[z][y][x] == 0) {
					continue;
				}

				float dy = y - 1.5;
				float dz = z - 1.5;

				byte nx = x;
				byte ny = constrain(round(cosVals[angle] * dy + negSinVals[angle] * dz + 1.5), 0, 3);
				byte nz = constrain(round(sinVals[angle] * dy + cosVals[angle] * dz + 1.5), 0, 3);

				target[nz][ny][nx] = 1;
			}
		}
	}
}

void rotateY(byte(*source)[4][4], byte(*target)[4][4], byte angle) {
	fillEmpty(target);

	for (int z = 0; z<4; z++) {
		for (int y = 0; y<4; y++) {
			for (int x = 0; x<4; x++) {
				if (source[z][y][x] == 0) {
					continue;
				}

				float dx = x - 1.5;
				float dz = z - 1.5;

				byte nx = constrain(round(cosVals[angle] * dx + sinVals[angle] * dz + 1.5), 0, 3);
				byte ny = y;
				byte nz = constrain(round(negSinVals[angle] * dx + cosVals[angle] * dz + 1.5), 0, 3);

				target[nz][ny][nx] = 1;
			}
		}
	}
}

void rotateZ(byte(*source)[4][4], byte(*target)[4][4], byte angle) {
	fillEmpty(target);

	for (int z = 0; z<4; z++) {
		for (int y = 0; y<4; y++) {
			for (int x = 0; x<4; x++) {
				if (source[z][y][x] == 0) {
					continue;
				}

				float dx = x - 1.5;
				float dy = y - 1.5;

				byte nx = constrain(round(cosVals[angle] * dx + negSinVals[angle] * dy + 1.5), 0, 3);
				byte ny = constrain(round(sinVals[angle] * dx + cosVals[angle] * dy + 1.5), 0, 3);
				byte nz = z;

				target[nz][ny][nx] = 1;
			}
		}
	}
}

/*
* 0b10000000 - 2, 1 - 0, 1
* 0b01000000 - 3, 3 - 1, 3
* 0b00100000 - 3, 1 - 1, 1
* 0b00010000 - 2, 3 - 0, 3
* 0b00001000 - 2, 0 - 0, 0
* 0b00000100 - 2, 2 - 0, 2
* 0b00000010 - 3, 2 - 1, 2
* 0b00000001 - 3, 0 - 1, 0
*
*/

byte pins[4][2] = {
	{ 0b00001000, 0b00000001 },
	{ 0b10000000, 0b00100000 },
	{ 0b00000100, 0b00000010 },
	{ 0b00010000, 0b01000000 }
};

word toWord(byte(*matrix)[4]) {
	word layer = 0;
	layer |= (matrix[0][0] * 0xFF) & pins[0][0];
	layer |= (matrix[0][1] * 0xFF) & pins[0][1];
	layer |= (matrix[1][0] * 0xFF) & pins[1][0];
	layer |= (matrix[1][1] * 0xFF) & pins[1][1];
	layer |= (matrix[2][0] * 0xFF) & pins[2][0];
	layer |= (matrix[2][1] * 0xFF) & pins[2][1];
	layer |= (matrix[3][0] * 0xFF) & pins[3][0];
	layer |= (matrix[3][1] * 0xFF) & pins[3][1];

	layer = layer << 8;

	layer |= (matrix[0][2] * 0xFF) & pins[0][0];
	layer |= (matrix[0][3] * 0xFF) & pins[0][1];
	layer |= (matrix[1][2] * 0xFF) & pins[1][0];
	layer |= (matrix[1][3] * 0xFF) & pins[1][1];
	layer |= (matrix[2][2] * 0xFF) & pins[2][0];
	layer |= (matrix[2][3] * 0xFF) & pins[2][1];
	layer |= (matrix[3][2] * 0xFF) & pins[3][0];
	layer |= (matrix[3][3] * 0xFF) & pins[3][1];
	return layer;
}

void drawCube(byte(*cube)[4][4], long milliseconds) {
	word layer1 = toWord(cube[0]);
	word layer2 = toWord(cube[1]);
	word layer3 = toWord(cube[2]);
	word layer4 = toWord(cube[3]);

	draw(layer1, layer2, layer3, layer4, milliseconds);
}