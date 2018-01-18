// 
// 
// 

#include "text.h"
#include "cube.h"

extern bool origCube[4][4][4];
extern bool cubeA[4][4][4];
extern bool cubeB[4][4][4];
extern bool cubeC[4][4][4];

bool space[4][3] = {
	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 }
};

bool lA[4][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 1 }
};

bool lB[4][3] = {
	{ 1, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};

bool lC[4][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 1, 1 }
};

bool lD[4][3] = {
	{ 1, 1, 0 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 0 }
};

bool lE[4][3] = {
	{ 1, 1, 1 },
	{ 1, 1, 0 },
	{ 1, 0, 0 },
	{ 1, 1, 1 }
};

bool lF[4][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 1, 1, 1 },
	{ 1, 0, 0 }
};

bool lG[4][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};

bool lH[4][3] = {
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 1 }
};

bool lI[4][3] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

bool lJ[4][3] = {
	{ 0, 0, 1 },
	{ 0, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};

bool lK[4][3] = {
	{ 1, 0, 1 },
	{ 1, 1, 0 },
	{ 1, 1, 0 },
	{ 1, 0, 1 }
};

bool lL[4][3] = {
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 1, 1 }
};

bool lM[4][3] = {
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 }
};

bool lN[4][3] = {
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 1 }
};

bool lO[4][3] = {
	{ 0, 1, 0 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 0, 1, 0 }
};

bool lP[4][3] = {
	{ 1, 1, 0 },
	{ 1, 0, 1 },
	{ 1, 1, 0 },
	{ 1, 0, 0 }
};

bool lQ[4][3] = {
	{ 0, 1, 0 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 0, 1, 1 }
};

bool lR[4][3] = {
	{ 1, 1, 0 },
	{ 1, 0, 1 },
	{ 1, 1, 0 },
	{ 1, 0, 1 }
};

bool lS[4][3] = {
	{ 1, 1, 1 },
	{ 0, 1, 0 },
	{ 0, 0, 1 },
	{ 1, 1, 1 }
};

bool lT[4][3] = {
	{ 1, 1, 1 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

bool lU[4][3] = {
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};

bool lV[4][3] = {
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 0, 1, 0 }
};

bool lW[4][3] = {
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 1 },
	{ 0, 1, 0 }
};

bool lX[4][3] = {
	{ 1, 0, 1 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 1, 0, 1 }
};

bool lY[4][3] = {
	{ 1, 0, 1 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

bool lZ[4][3] = {
	{ 1, 1, 1 },
	{ 0, 1, 0 },
	{ 1, 0, 0 },
	{ 1, 1, 1 }
};

bool(*letters[])[3] = { lA, lB, lC, lD, lE, lF, lG, lH, lI, lJ, lK, lL, lM, lN, lO, lP, lQ, lR, lS, lT, lU, lV, lW, lX, lY, lZ };

// 97

void drawLetter(bool(*ltr)[3], long milliseconds) {
	fillEmpty(cube);
	byte atY = 0;
	byte width = 1;

	for (byte z = 0; z < 4; z++) {
		for (byte y = atY; y < atY + width; y++) {
			for (byte x = 1; x < 4; x++) {
				cube[z][y][x] = ltr[z][3-x];
			}
		}
	}

	//rotateY(cubeA, cubeB, 1);
	//rotateZ(cube, cubeA, 3);

	drawCube(cube, milliseconds);
}

void drawTwoLetters(bool(*ltrs)[8], byte initX, byte atY, byte rotate, long milliseconds) {
	fillEmpty(cube);
	byte width = 1;

	for (byte z = 0; z < 4; z++) {
		for (byte y = atY; y < atY + width; y++) {
			for (byte x = 0; x < 4; x++) {
				cube[z][y][x] = ltrs[z][3-x+initX];
			}
		}
	}

	rotateZ(cube, cubeB, rotate);
	//rotateZ(cube, cubeA, 2);

	drawCube(cubeB, milliseconds);
}

void drawLetters(long milliseconds) {
	int fps = 12;
	int mspf = 1000 / fps;
	long totalFrames = milliseconds / mspf;

	char* text = "hello world ";
	int size = strlen(text);
	int stringFrames = size * 4;

	long times = totalFrames / stringFrames;

	byte atY = 0;
	int yInc = 1;

	byte rotate = 0;

	bool(*letter)[3] = space;
	bool(*nextLetter)[3] = space;
	for (long t = 0; t < times; t++) {

		for (byte c = 0; c < size; c++) {
			byte ltr = text[c] - 97;
			nextLetter = letters[ltr];
			if (text[c] == 0x20) {
				nextLetter = space;
			}

			bool part[4][8];
			for (byte y = 0; y < 4; y++) {
				for (byte x = 0; x < 3; x++) {
					part[y][x+1] = letter[y][x];
					part[y][x+5] = nextLetter[y][x];
				}
				part[y][0] = 0;
				part[y][4] = 0;
			}

			for (byte f = 0; f < 4; f++) {
				drawTwoLetters(part, f, atY, rotate, mspf);
				if (t > 1 && c > 0) {
					atY = constrain(atY + yInc, 0, 3);
				}
			}
			
			if (t > 0 && t % 3 == 1) {
				rotate++;
				rotate = rotate % 12;
			}

			if (t > 1 && c > 0) {
				yInc = yInc * -1;
			}

			letter = nextLetter;
		}

		letter = space;
		nextLetter = space;
	}
}