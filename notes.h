
#include <avr/pgmspace.h>

// Octaves notes definition
int note01 [] = {0, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36}; // Notes from C0 to C2
int note23 [] = {0, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60}; // Notes from C2 to C4
int note45 [] = {0, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84}; // Notes from C4 to C6
int note67 [] = {0, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108}; // Notes from C6 to C8
int note89 [] = {0, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127}; // Notes from C8 to G9


// Instruments names are going to be saved on PROGMEM to save space on SRAM (variables)
const char notes01_1[] PROGMEM = "C0";
const char notes01_2[] PROGMEM = "C#0";
const char notes01_3[] PROGMEM = "D0";
const char notes01_4[] PROGMEM = "D#0";
const char notes01_5[] PROGMEM = "E0";
const char notes01_6[] PROGMEM = "F0";
const char notes01_7[] PROGMEM = "F#0";
const char notes01_8[] PROGMEM = "G0";
const char notes01_9[] PROGMEM = "G#0";
const char notes01_10[] PROGMEM = "A0";
const char notes01_11[] PROGMEM = "A#0";
const char notes01_12[] PROGMEM = "B0";
const char notes01_13[] PROGMEM = "C1";
const char notes01_14[] PROGMEM = "C#1";
const char notes01_15[] PROGMEM = "D1";
const char notes01_16[] PROGMEM = "D#1";
const char notes01_17[] PROGMEM = "E1";
const char notes01_18[] PROGMEM = "F1";
const char notes01_19[] PROGMEM = "F#1";
const char notes01_20[] PROGMEM = "G1";
const char notes01_21[] PROGMEM = "G#1";
const char notes01_22[] PROGMEM = "A1";
const char notes01_23[] PROGMEM = "A#1";
const char notes01_24[] PROGMEM = "B1";
const char notes01_25[] PROGMEM = "C2";


const char *const notes01_table[] PROGMEM = {0, notes01_1, notes01_2, notes01_3, notes01_4, notes01_5, notes01_6, notes01_7, notes01_8,
                                             notes01_9, notes01_10, notes01_11, notes01_12, notes01_13, notes01_14, notes01_15, notes01_16,
                                             notes01_17, notes01_18, notes01_19, notes01_20, notes01_21, notes01_22, notes01_23, notes01_24,
                                             notes01_25};

const char notes23_1[] PROGMEM = "C2";
const char notes23_2[] PROGMEM = "C#2";
const char notes23_3[] PROGMEM = "D2";
const char notes23_4[] PROGMEM = "D#2";
const char notes23_5[] PROGMEM = "E2";
const char notes23_6[] PROGMEM = "F2";
const char notes23_7[] PROGMEM = "F#2";
const char notes23_8[] PROGMEM = "G2";
const char notes23_9[] PROGMEM = "G#2";
const char notes23_10[] PROGMEM = "A2";
const char notes23_11[] PROGMEM = "A#2";
const char notes23_12[] PROGMEM = "B2";
const char notes23_13[] PROGMEM = "C3";
const char notes23_14[] PROGMEM = "C#3";
const char notes23_15[] PROGMEM = "D3";
const char notes23_16[] PROGMEM = "D#3";
const char notes23_17[] PROGMEM = "E3";
const char notes23_18[] PROGMEM = "F3";
const char notes23_19[] PROGMEM = "F#3";
const char notes23_20[] PROGMEM = "G3";
const char notes23_21[] PROGMEM = "G#3";
const char notes23_22[] PROGMEM = "A3";
const char notes23_23[] PROGMEM = "A#3";
const char notes23_24[] PROGMEM = "B3";
const char notes23_25[] PROGMEM = "C4";

const char *const notes23_table[] PROGMEM = {0, notes23_1, notes23_2, notes23_3, notes23_4, notes23_5, notes23_6, notes23_7, notes23_8,
                                             notes23_9, notes23_10, notes23_11, notes23_12, notes23_13, notes23_14, notes23_15, notes23_16,
                                             notes23_17, notes23_18, notes23_19, notes23_20, notes23_21, notes23_22, notes23_23, notes23_24,
                                             notes23_25};

const char notes45_1[] PROGMEM = "C4";
const char notes45_2[] PROGMEM = "C#4";
const char notes45_3[] PROGMEM = "D4";
const char notes45_4[] PROGMEM = "D#4";
const char notes45_5[] PROGMEM = "E4";
const char notes45_6[] PROGMEM = "F4";
const char notes45_7[] PROGMEM = "F#4";
const char notes45_8[] PROGMEM = "G4";
const char notes45_9[] PROGMEM = "G#4";
const char notes45_10[] PROGMEM = "A4";
const char notes45_11[] PROGMEM = "A#4";
const char notes45_12[] PROGMEM = "B4";
const char notes45_13[] PROGMEM = "C5";
const char notes45_14[] PROGMEM = "C#5";
const char notes45_15[] PROGMEM = "D5";
const char notes45_16[] PROGMEM = "D#5";
const char notes45_17[] PROGMEM = "E5";
const char notes45_18[] PROGMEM = "F5";
const char notes45_19[] PROGMEM = "F#5";
const char notes45_20[] PROGMEM = "G5";
const char notes45_21[] PROGMEM = "G#5";
const char notes45_22[] PROGMEM = "A5";
const char notes45_23[] PROGMEM = "A#5";
const char notes45_24[] PROGMEM = "B5";
const char notes45_25[] PROGMEM = "C6";

const char *const notes45_table[] PROGMEM = {0, notes45_1, notes45_2, notes45_3, notes45_4, notes45_5, notes45_6, notes45_7, notes45_8,
                                             notes45_9, notes45_10, notes45_11, notes45_12, notes45_13, notes45_14, notes45_15, notes45_16,
                                             notes45_17, notes45_18, notes45_19, notes45_20, notes45_21, notes45_22, notes45_23, notes45_24,
                                             notes45_25};

const char notes67_1[] PROGMEM = "C6";
const char notes67_2[] PROGMEM = "C#6";
const char notes67_3[] PROGMEM = "D6";
const char notes67_4[] PROGMEM = "D#6";
const char notes67_5[] PROGMEM = "E6";
const char notes67_6[] PROGMEM = "F6";
const char notes67_7[] PROGMEM = "F#6";
const char notes67_8[] PROGMEM = "G6";
const char notes67_9[] PROGMEM = "G#6";
const char notes67_10[] PROGMEM = "A6";
const char notes67_11[] PROGMEM = "A#6";
const char notes67_12[] PROGMEM = "B6";
const char notes67_13[] PROGMEM = "C7";
const char notes67_14[] PROGMEM = "C#7";
const char notes67_15[] PROGMEM = "D7";
const char notes67_16[] PROGMEM = "D#7";
const char notes67_17[] PROGMEM = "E7";
const char notes67_18[] PROGMEM = "F7";
const char notes67_19[] PROGMEM = "F#7";
const char notes67_20[] PROGMEM = "G7";
const char notes67_21[] PROGMEM = "G#7";
const char notes67_22[] PROGMEM = "A7";
const char notes67_23[] PROGMEM = "A#7";
const char notes67_24[] PROGMEM = "B7";
const char notes67_25[] PROGMEM = "C8";

const char *const notes67_table[] PROGMEM = {0, notes67_1, notes67_2, notes67_3, notes67_4, notes67_5, notes67_6, notes67_7, notes67_8,
                                             notes67_9, notes67_10, notes67_11, notes67_12, notes67_13, notes67_14, notes67_15, notes67_16,
                                             notes67_17, notes67_18, notes67_19, notes67_20, notes67_21, notes67_22, notes67_23, notes67_24,
                                             notes67_25};

const char notes89_1[] PROGMEM = "C8";
const char notes89_2[] PROGMEM = "C#8";
const char notes89_3[] PROGMEM = "D8";
const char notes89_4[] PROGMEM = "D#8";
const char notes89_5[] PROGMEM = "E8";
const char notes89_6[] PROGMEM = "F8";
const char notes89_7[] PROGMEM = "F#8";
const char notes89_8[] PROGMEM = "G8";
const char notes89_9[] PROGMEM = "G#8";
const char notes89_10[] PROGMEM = "A8";
const char notes89_11[] PROGMEM = "A#8";
const char notes89_12[] PROGMEM = "B8";
const char notes89_13[] PROGMEM = "C9";
const char notes89_14[] PROGMEM = "C#9";
const char notes89_15[] PROGMEM = "D9";
const char notes89_16[] PROGMEM = "D#9";
const char notes89_17[] PROGMEM = "E9";
const char notes89_18[] PROGMEM = "F9";
const char notes89_19[] PROGMEM = "F#9";
const char notes89_20[] PROGMEM = "G9";


const char *const notes89_table[] PROGMEM = {0, notes89_1, notes89_2, notes89_3, notes89_4, notes89_5, notes89_6, notes89_7, notes89_8,
                                             notes89_9, notes89_10, notes89_11, notes89_12, notes89_13, notes89_14, notes89_15, notes89_16,
                                             notes89_17, notes89_18, notes89_19, notes89_20};
