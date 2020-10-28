void recording() {

  for (int i = 1; i < n_keys; i++) {                      // for all the keys

    if (key[i].isPressed()) {                           // if any key is pressed

      if (octave == 0) {
        record_notes[note_counter] = note01[i]; // saves note on current position of record_note array buffer
        new_record_notes[note_counter] = note01[i]; // saves note on current position of record_note array buffer used in Tuning Mode
      }

      if (octave == 1) {
        record_notes[note_counter] = note23[i];
        new_record_notes[note_counter] = note23[i];
      }
      if (octave == 2) {
        record_notes[note_counter] = note45[i];
        new_record_notes[note_counter] = note45[i];
      }
      if (octave == 3) {
        record_notes[note_counter] = note67[i];
        new_record_notes[note_counter] = note67[i];
      }
      if (octave == 4) {
        record_notes[note_counter] = note89[i];
        new_record_notes[note_counter] = note89[i];
      }

      lcd.setCursor(13, 0);
      lcd.print(note_counter);
      lcd.setCursor(note_counter, 1);                 // sets lcd cursor into position
      lcd.write(0);                                   // displays musical notation symbol on counter position
      if (note_counter >= 1){
        lcd.setCursor((note_counter - 1), 1);
        if (note_counter > 15) {
          lcd.setCursor((note_counter - 16), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
        }
        if (note_counter > 30) {
          lcd.setCursor((note_counter - 31), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
        }
        if (note_counter > 45) {
          lcd.setCursor((note_counter - 46), 1);
        }
        if (note_counter > 62) {
          lcd.setCursor((note_counter - 63), 1);
        }
        if (note_counter > 78) {
          lcd.setCursor((note_counter - 79), 1);
        }
        if (note_counter > 94) {
          lcd.setCursor((note_counter - 95), 1);
        }
        if (note_counter > 111) {
          lcd.setCursor((note_counter - 112), 1);
        }  
        lcd.print(" ");
        lcd.write(0);  
      }
      note_counter++;                                 // increases note_counter +1
      note_counter %= 128;                            // limits number of recorded notes to 128

      duration_buffer[note_counter] = millis();       // saves current time on current position of duration_buffer

      if (note_counter >= 2) {                        // when note position is 2
        record_durations[(note_counter) - 1] = duration_buffer[note_counter] - duration_buffer[(note_counter) - 1];
        new_record_durations[(note_counter) - 1] = duration_buffer[note_counter] - duration_buffer[(note_counter) - 1];
      }                                               // pick the times of duration_buffer to calculate
    }                                                 // the record_durations of current position
  }


  if (red1button.isReleased()) {                     // if red1 button is pressed

    writeIntArrayIntoEEPROM(0, record_notes, 128);  // Write 2 bytes on position 0 and 1 of EEPROM record_notes[] with [] size 128
    writeIntArrayIntoEEPROM(256, record_durations, 128); // Start writing on position 256 of EEPROM record_durations[]
    EEPROM.write(2049, instrument);               // Write the record 1 instrument to EEPROM
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[8])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 1 Saved");
    delay(500);
  }

  if (red2button.isReleased()) {                  // if red2 button is pressed
    
    writeIntArrayIntoEEPROM(512, record_notes, 128);
    writeIntArrayIntoEEPROM(768, record_durations, 128);
    EEPROM.write(2050, instrument);
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[9])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 2 Saved");
    delay(500);
  }

  if (red3button.isReleased()) {                  // if red3 button is pressed
   
    writeIntArrayIntoEEPROM(1024, record_notes, 128);
    writeIntArrayIntoEEPROM(1280, record_durations, 128);
    EEPROM.write(2051, instrument);
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[10])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 3 Saved");
    delay(500);
  }

  if (red4button.isReleased()) {                  // if red4 button is pressed
    
    writeIntArrayIntoEEPROM(1536, record_notes, 128);
    writeIntArrayIntoEEPROM(1792, record_durations, 128);
    EEPROM.write(2052, instrument);
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[11])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 4 Saved");
    delay(500);
  }
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void writeIntArrayIntoEEPROM(int address, int numbers[], int arraySize)
{
  int addressIndex = address;
  for (int i = 0; i < arraySize; i++) 
  {
    EEPROM.write(addressIndex, numbers[i] >> 8);
    EEPROM.write(addressIndex + 1, numbers[i] & 0xFF);
    addressIndex += 2;
  }
}
