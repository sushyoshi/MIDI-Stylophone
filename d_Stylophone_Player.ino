/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void stylophone_player(int channel) {

  octaveselection();             // call function for octave selection potentiometer

  for (int i = 1; i < n_keys; i++) {
    if (key[i].isPressed()){

      lcd.clear();
      lcd.setCursor(0, 0);

      if (octave == 0) {
        noteOn(channel, (note01[i]), 127);
        strcpy_P(buffer, (char *)pgm_read_word(&(notes01_table[i])));  // Necessary casts and dereferencing, just copy.
        lcd.print(buffer);
        lcd.setCursor(4, 0);
        lcd.print(note01[i]);
      }

      if (octave == 1) {
        noteOn(channel, (note23[i]), 127);
        strcpy_P(buffer, (char *)pgm_read_word(&(notes23_table[i])));  // Necessary casts and dereferencing, just copy.
        lcd.print(buffer);
        lcd.setCursor(4, 0);
        lcd.print(note23[i]);
      }

      if (octave == 2) {
        noteOn(channel, (note45[i]), 127);
        //Serial.println (millis());
        strcpy_P(buffer, (char *)pgm_read_word(&(notes45_table[i])));  // Necessary casts and dereferencing, just copy.
        lcd.print(buffer);
        lcd.setCursor(4, 0);
        lcd.print(note45[i]);
      }

      if (octave == 3) {
        noteOn(channel, (note67[i]), 127);
        strcpy_P(buffer, (char *)pgm_read_word(&(notes67_table[i])));  // Necessary casts and dereferencing, just copy.
        lcd.print(buffer);
        lcd.setCursor(4, 0);
        lcd.print(note67[i]);
      }

      if (octave == 4) {
        noteOn(channel, (note89[i]), 127);
        strcpy_P(buffer, (char *)pgm_read_word(&(notes89_table[i])));  // Necessary casts and dereferencing, just copy.
        lcd.print(buffer);
        lcd.setCursor(4, 0);
        lcd.print(note89[i]);
      }
    }

    if (key[i].isReleased()){

      if (octave == 0) {
        noteOff(channel, (note01[i]), 0);
      }
      if (octave == 1) {
        noteOff(channel, (note23[i]), 0);
      }
      if (octave == 2) {
        noteOff(channel, (note45[i]), 0);
      }
      if (octave == 3) {
        noteOff(channel, (note67[i]), 0);
      }
      if (octave == 4) {
        noteOff(channel, (note89[i]), 0);
      }
    }
  }
}
