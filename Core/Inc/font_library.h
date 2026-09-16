
typedef struct
{
	char character;
	const uint8_t *glyph;
} Character_to_Font;



// 5x7 Font
// Each character is 5 pixels wide and 7 pixels tall.

const uint8_t FONT_A[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001,
    0b10001
};

const uint8_t FONT_B[7] = {
    0b11110,
    0b10001,
    0b10001,
    0b11110,
    0b10001,
    0b10001,
    0b11110
};

const uint8_t FONT_C[7] = {
    0b01111,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b01111
};

const uint8_t FONT_D[7] = {
    0b11110,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11110
};

const uint8_t FONT_E[7] = {
    0b11111,
    0b10000,
    0b10000,
    0b11110,
    0b10000,
    0b10000,
    0b11111
};

const uint8_t FONT_F[7] = {
    0b11111,
    0b10000,
    0b10000,
    0b11110,
    0b10000,
    0b10000,
    0b10000
};

const uint8_t FONT_G[7] = {
    0b01111,
    0b10000,
    0b10000,
    0b10111,
    0b10001,
    0b10001,
    0b01111
};

const uint8_t FONT_H[7] = {
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001,
    0b10001
};

const uint8_t FONT_I[7] = {
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b11111
};

const uint8_t FONT_J[7] = {
    0b00111,
    0b00010,
    0b00010,
    0b00010,
    0b10010,
    0b10010,
    0b01100
};

const uint8_t FONT_K[7] = {
    0b10001,
    0b10010,
    0b10100,
    0b11000,
    0b10100,
    0b10010,
    0b10001
};

const uint8_t FONT_L[7] = {
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b11111
};

const uint8_t FONT_M[7] = {
    0b10001,
    0b11011,
    0b10101,
    0b10101,
    0b10001,
    0b10001,
    0b10001
};

const uint8_t FONT_N[7] = {
    0b10001,
    0b11001,
    0b10101,
    0b10011,
    0b10001,
    0b10001,
    0b10001
};

const uint8_t FONT_O[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01110
};

const uint8_t FONT_P[7] = {
    0b11110,
    0b10001,
    0b10001,
    0b11110,
    0b10000,
    0b10000,
    0b10000
};

const uint8_t FONT_Q[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b10101,
    0b10010,
    0b01101
};

const uint8_t FONT_R[7] = {
    0b11110,
    0b10001,
    0b10001,
    0b11110,
    0b10100,
    0b10010,
    0b10001
};

const uint8_t FONT_S[7] = {
    0b01111,
    0b10000,
    0b10000,
    0b01110,
    0b00001,
    0b00001,
    0b11110
};

const uint8_t FONT_T[7] = {
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100
};

const uint8_t FONT_U[7] = {
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01110
};

const uint8_t FONT_V[7] = {
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01010,
    0b00100
};

const uint8_t FONT_W[7] = {
    0b10001,
    0b10001,
    0b10001,
    0b10101,
    0b10101,
    0b11011,
    0b10001
};

const uint8_t FONT_X[7] = {
    0b10001,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b10001
};

const uint8_t FONT_Y[7] = {
    0b10001,
    0b10001,
    0b01010,
    0b00100,
    0b00100,
    0b00100,
    0b00100
};

const uint8_t FONT_Z[7] = {
    0b11111,
    0b00001,
    0b00010,
    0b00100,
    0b01000,
    0b10000,
    0b11111
};


const uint8_t FONT_0[7] = {
    0b01110,
    0b10001,
    0b10011,
    0b10101,
    0b11001,
    0b10001,
    0b01110
};

const uint8_t FONT_1[7] = {
    0b00100,
    0b01100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b01110
};

const uint8_t FONT_2[7] = {
    0b01110,
    0b10001,
    0b00001,
    0b00010,
    0b00100,
    0b01000,
    0b11111
};

const uint8_t FONT_3[7] = {
    0b11110,
    0b00001,
    0b00001,
    0b01110,
    0b00001,
    0b00001,
    0b11110
};

const uint8_t FONT_4[7] = {
    0b00010,
    0b00110,
    0b01010,
    0b10010,
    0b11111,
    0b00010,
    0b00010
};

const uint8_t FONT_5[7] = {
    0b11111,
    0b10000,
    0b10000,
    0b11110,
    0b00001,
    0b00001,
    0b11110
};

const uint8_t FONT_6[7] = {
    0b01110,
    0b10000,
    0b10000,
    0b11110,
    0b10001,
    0b10001,
    0b01110
};

const uint8_t FONT_7[7] = {
    0b11111,
    0b00001,
    0b00010,
    0b00100,
    0b01000,
    0b01000,
    0b01000
};

const uint8_t FONT_8[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b01110,
    0b10001,
    0b10001,
    0b01110
};

const uint8_t FONT_9[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b01111,
    0b00001,
    0b00001,
    0b01110
};

const uint8_t *FONT[] = {
    FONT_A, FONT_B, FONT_C, FONT_D, FONT_E, FONT_F,
    FONT_G, FONT_H, FONT_I, FONT_J, FONT_K, FONT_L,
    FONT_M, FONT_N, FONT_O, FONT_P, FONT_Q, FONT_R,
    FONT_S, FONT_T, FONT_U, FONT_V, FONT_W, FONT_X,
    FONT_Y, FONT_Z,
    FONT_0, FONT_1, FONT_2, FONT_3, FONT_4,
    FONT_5, FONT_6, FONT_7, FONT_8, FONT_9
};

const Character_to_Font FONT_5x7[] =
{
		{'A', FONT_A},
		{'B', FONT_B},
		{'C', FONT_C},
		{'D', FONT_D},
		{'E', FONT_E},
		{'F', FONT_F},
		{'G', FONT_G},
		{'H', FONT_H},
		{'I', FONT_I},
		{'J', FONT_J},
		{'K', FONT_K},
		{'L', FONT_L},
		{'M', FONT_M},
		{'N', FONT_N},
		{'O', FONT_O},
		{'P', FONT_P},
		{'Q', FONT_Q},
		{'R', FONT_R},
		{'S', FONT_S},
		{'T', FONT_T},
		{'U', FONT_U},
		{'V', FONT_V},
		{'W', FONT_W},
		{'X', FONT_X},
		{'Y', FONT_Y},
		{'Z', FONT_Z},
		{'0', FONT_0},
		{'1', FONT_1},
		{'2', FONT_2},
		{'3', FONT_3},
		{'4', FONT_4},
		{'5', FONT_5},
		{'6', FONT_6},
		{'7', FONT_7},
		{'8', FONT_8},
		{'9', FONT_9}
};


