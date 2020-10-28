
void Preset_Player(){

      /*******************************************************************************************************/
    /////////// ************* Play Presets while on Stylophone mode *************** /////////////////////////
    /*******************************************************************************************************/

    if (digitalRead(switch1pin) == LOW) {

      if (preset1 == 0) {
        melody_player(1, tempo1, n_preset0_notes, preset0_notes, preset0_durations);
      }
      if (preset1 == 1) {
        melody_player(1, tempo1, n_preset1_notes, preset1_notes, preset1_durations);
      }
      if (preset1 == 2) {
        melody_player(1, tempo1, n_preset2_notes, preset2_notes, preset2_durations);
      }
      if (preset1 == 3) {
        melody_player(1, tempo1, n_preset3_notes, preset3_notes, preset3_durations);
      }
      if (preset1 == 4) {
        melody_player(1, tempo1, n_preset4_notes, preset4_notes, preset4_durations);
      }
      if (preset1 == 5) {
        melody_player(1, tempo1, n_preset5_notes, preset5_notes, preset5_durations);
      }




      if (red1button.getState() == LOW) {               // while red1button is pressed
        
        preset_select(1);
        instrument_select(1);                // change instrument on channel 1 using yellow button and blue button
      }
    }else{talkMIDI(0xB0 | 1, 0x78, 0);} // Silences this channel



    if (digitalRead(switch2pin) == LOW) {

      if (preset2 == 0) {
        melody_player(2, tempo2, n_preset0_notes, preset0_notes, preset0_durations);
      }
      if (preset2 == 1) {
        melody_player(2, tempo2, n_preset1_notes, preset1_notes, preset1_durations);
      }
      if (preset2 == 2) {
        melody_player(2, tempo2, n_preset2_notes, preset2_notes, preset2_durations);
      }
      if (preset2 == 3) {
        melody_player(2, tempo2, n_preset3_notes, preset3_notes, preset3_durations);
      }
      if (preset2 == 4) {
        melody_player(2, tempo2, n_preset4_notes, preset4_notes, preset4_durations);
      }
      if (preset2 == 5) {
        melody_player(2, tempo2, n_preset5_notes, preset5_notes, preset5_durations);
      }


      if (red2button.getState() == LOW) {           // while red2button is pressed

        instrument_select(2);
        preset_select(2);
      }
    }else{talkMIDI(0xB0 | 2, 0x78, 0);} // Silences this channel
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void melody_player(int channel, float tempo, int n_preset_notes, const uint8_t preset_notes[], const uint16_t preset_durations[] ) {

  tempo_control();                          // instantiate tempo control



  if (channel == 1) {
 
    static uint32_t previousMillis1 = 0;
    static byte state1 = 0;                    // sets starting switch case to 0
    static byte j = 0;                        // sets initial value of i

    if (millis() - previousMillis1 >= preset_durations[j] * tempo) { // checks to see if the preset duration for the
      // current note has passed, when multiplied by the tempo
      state1++;            // its time to move to next state
      state1 %= 2;         // setting state limit value 2 (state = 0 until state = 1)

      switch (state1)      // act according to the state
      {
        case 0:                                   // This state the note starts
          noteOn(channel, preset_notes[j], 127);  // Starts playing current preset note on specified channel, maximum volume
          lcd.setCursor(0, 0);
          lcd.print(preset_notes[j]);
          strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[4])));  // Copy lcd word from program memory to buffer
          lcd.print(buffer);
//          lcd.print("      Preset ");
          lcd.print(preset1);
          lcd.setCursor(j, 1);
          if (j > 15) {
            lcd.setCursor((j - 16), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
          }
          if (j > 31) {
            lcd.setCursor((j - 32), 1);
          }
          if (j > 47) {
            lcd.setCursor((j - 48), 1);
          }
          if (j > 63) {
            lcd.setCursor((j - 64), 1);
          }
          if (j > 79) {
            lcd.setCursor((j - 80), 1);
          }
          if (j > 95) {
            lcd.setCursor((j - 96), 1);
          }
          if (j > 111) {
            lcd.setCursor((j - 112), 1);
          }
          lcd.print(" ");
          lcd.write(0);                           // makes display a musical note symbol when note is played

          break;

        case 1:                                   // This state the note finishes
          noteOff(channel, preset_notes[j], 0);   // Stops playing current preset note on specified channel
          j++;                                    // after note finishes, goes to next note
          j %= n_preset_notes;                 // sets limit of notes to go next
          break;
      }
      previousMillis1 = millis();
    }
  }


  if (channel == 2) {

    static uint32_t previousMillis2 = 0;
    static byte state2 = 0;                    // sets starting switch case to 0
    static byte k = 0;                        // sets initial value of i

    if (millis() - previousMillis2 >= preset_durations[k] * tempo) { // checks to see if the preset duration for the
      // current note has passed, when multiplied by the tempo
      state2++;            // its time to move to next state
      state2 %= 2;  // setting state limit value 2 (state = 0 until state = 1)

      switch (state2)      // act according to the state
      {
        case 0:                                   // This state the note starts
          noteOn(channel, preset_notes[k], 127);  // Starts playing current preset note on specified channel, maximum volume
          lcd.setCursor(0, 0);
          lcd.print(preset_notes[k]);
          strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[4])));  // Copy lcd word from program memory to buffer
          lcd.print(buffer);
//          lcd.print("      Preset ");
          lcd.print(preset2);
          lcd.setCursor(k, 1);
          if (k > 15) {
            lcd.setCursor((k - 16), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
          }
          if (k > 31) {
            lcd.setCursor((k - 32), 1);
          }
          if (k > 47) {
            lcd.setCursor((k - 48), 1);
          }
          if (k > 63) {
            lcd.setCursor((k - 64), 1);
          }
          if (k > 79) {
            lcd.setCursor((k - 80), 1);
          }
          if (k > 95) {
            lcd.setCursor((k - 96), 1);
          }
          if (k > 111) {
            lcd.setCursor((k - 112), 1);
          }
          lcd.print(" ");
          lcd.write(0);                           // makes display a musical note symbol when note is played

          break;

        case 1:                                   // This state the note finishes
          noteOff(channel, preset_notes[k], 0);   // Stops playing current preset note on specified channel
          k++;                                    // after note finishes, goes to next note
          k %= n_preset_notes;                 // sets limit of notes to go next
          break;
      }
      previousMillis2 = millis();
    }
  }
}
