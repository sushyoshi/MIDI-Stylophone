#include <avr/pgmspace.h>

// LCD messages names are going to be saved on PROGMEM to save space on SRAM (variables)
const char lcd_0[] PROGMEM = "Stylophone Mode";
const char lcd_1[] PROGMEM = "Composer Mode";
const char lcd_2[] PROGMEM = "Tuning Mode";
const char lcd_3[] PROGMEM = "Instrument ";
const char lcd_4[] PROGMEM = "      Preset ";
const char lcd_5[] PROGMEM = "     Record_Buff";
const char lcd_6[] PROGMEM = "      Record ";
const char lcd_7[] PROGMEM = "   Buff Record ";
const char lcd_8[] PROGMEM = "Record 1 Saved";
const char lcd_9[] PROGMEM = "Record 2 Saved";
const char lcd_10[] PROGMEM = "Record 3 Saved";
const char lcd_11[] PROGMEM = "Record 4 Saved";
const char lcd_12[] PROGMEM = "Record Buffer   ";
const char lcd_13[] PROGMEM = "Cleared !       ";



const char *const lcd_table[] PROGMEM = {lcd_0, lcd_1, lcd_2, lcd_3, lcd_4, lcd_5, lcd_6, lcd_7,
                                         lcd_8, lcd_9, lcd_10, lcd_11, lcd_12, lcd_13};
