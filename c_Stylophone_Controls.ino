/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void instrument_select(int channel) {       // Changes instrument number on the designated channel



  if (bluebutton2.isReleased()) {           // if yellow button is pressed
    instrument++;                           // increase instrument number
    instrument %= 128;                      // limit instrument variable (0 - 127)
  }

  if (bluebutton1.isReleased()) {             // if blue button is pressed
    instrument--;                           // decrease instrument number
    instrument %= 128;                      // limit instrument variable (0 - 127)
  }


  if (instrument != previous_instrument) {

    talkMIDI(0xC0 | channel, instrument, 0);    //Set instrument number. 0xC0 is a 1 data byte command

    lcd.clear();                                // LCD code to show the instrument selected
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[3])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
    lcd.print("      ");
    lcd.setCursor(11, 0);
    lcd.print(instrument);
    lcd.setCursor(0, 1);
    strcpy_P(buffer, (char *)pgm_read_word(&(instrument_table[instrument])));  // Necessary casts and dereferencing, just copy.
    lcd.print(buffer);
    lcd.setCursor(0, 0);

    previous_instrument = instrument;

    delay(100);
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void pitch_bending () {

  int pitchpot = (analogRead(A0));

  int pitch_bend = map(pitchpot, 0, 1023, 0, 16383); // pitch bend range is 0 - 16383, and
  // the middle of the range, 8192, is zero pitch bend

  int previous_pitch_bend;
  
  // convert 8-bit bytes to 7-bit bytes:
  pitch_bend = pitch_bend << 1;          // shift low byte's msb to high byte
  byte msb = highByte(pitch_bend);      // get the high bits
  byte lsb = lowByte(pitch_bend) >> 1;  // get the low 8 bits

  int pitch_bend_display = map(pitch_bend, 0, 16383, -2, 2);// maps the values of pitch bend to number of semitones for lcd display
  
  if (pitch_bend != previous_pitch_bend){        // if the pitch bend value is changed

    talkMIDI(0xE0 | 0, lsb, msb);           // send command to pitch bend on channel 0
    lcd.setCursor(11, 1);
    lcd.print("PB:");
    lcd.print(pitch_bend_display);
    lcd.print("  ");
    previous_pitch_bend = pitch_bend; 
  }  
  

  if (red1button.getState() == LOW) {
    talkMIDI(0xE0 | 1, lsb, msb);
  }
  if (red2button.getState() == LOW) {
    talkMIDI(0xE0 | 2, lsb, msb);
  }
  if (red3button.getState() == LOW) {
    talkMIDI(0xE0 | 3, lsb, msb);
  }
  if (red4button.getState() == LOW) {
    talkMIDI(0xE0 | 4, lsb, msb);
  }

}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void octaveselection() {

  octavepot = analogRead(A1);    //Potentiometer A1 will select the octaves from the stylophone keys from C0 to C9

  octavepot = map(octavepot, 0, 1023, 0, 4);

  if (octavepot == 0) {
    octave = 0; //Corresponding to octave 0 and 1
  }
  if (octavepot == 1) {
    octave = 1; //Corresponding to octave 2 and 3
  }
  if (octavepot == 2) {
    octave = 2; //Corresponding to octave 4 and 5
  }
  if (octavepot == 3) {
    octave = 3; //Corresponding to octave 6 and 7
  }
  if (octavepot == 4) {
    octave = 4; //Corresponding to octave 8 and 9
  }
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void tempo_control() {

  int tempopot = (analogRead(A2));
  tempopot = map(tempopot, 0, 1023, 3, 30); // makes the tempo potentiometer range from 3 to 30
  tempo = tempopot * 0.1;                   // setting tempo to be from 0.3 to 3
  
  if (red1button.getState() == LOW) {
    tempo1 = tempo; // sets tempo for channel 1 melody
  }
  if (red2button.getState() == LOW) {
    tempo2 = tempo; // sets tempo for channel 2 melody
  }
  if (red3button.getState() == LOW) {
    tempo3 = tempo; // sets tempo for channel 3 melody
  }
  if (red4button.getState() == LOW) {
    tempo4 = tempo; // sets tempo for channel 4 melody
  }
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void preset_select(int channel) {

  if (channel == 1) {
    if (redbutton.getState() != redbutton_lastState) { // if red button changes the state
      if (redbutton.isPressed()) {                  // if red button is pressed
        preset1++;
        preset1 %= 6;
      }
      if (redbutton.isReleased()) {                  // if red button is released
        talkMIDI(0xB0 | 1, 0x7b, 0);                // releases all notes on this channel
      }
    }
    redbutton_lastState = redbutton.getState();        // save last red button state
  }

  if (channel == 2) {
    if (redbutton.getState() != redbutton_lastState) { // if red button changes the state
      if (redbutton.isPressed()) {                  // if red button is pressed
        preset2++;
        preset2 %= 6;
      }
      if (redbutton.isReleased()) {                  // if red button is released
        talkMIDI(0xB0 | 2, 0x7b, 0);                // releases all notes on this channel
      }
    }
    redbutton_lastState = redbutton.getState();        // save last red button state
  }

  if (channel == 3) {
    if (redbutton.getState() != redbutton_lastState) { // if red button changes the state
      if (redbutton.isPressed()) {                  // if red button is pressed
        record3++;
        record3 %= 5;
      }
      if (redbutton.isReleased()) {                  // if red button is released
        talkMIDI(0xB0 | 3, 0x7b, 0);                // releases all notes on this channel
      }
    }
    redbutton_lastState = redbutton.getState();        // save last red button state
  }

  if (channel == 4) {
    if (redbutton.getState() != redbutton_lastState) { // if red button changes the state
      if (redbutton.isPressed()) {                  // if red button is pressed
        record4++;
        record4 %= 5;
      }
      if (redbutton.isReleased()) {                  // if red button is released
        talkMIDI(0xB0 | 4, 0x7b, 0);                // releases all notes on this channel
      }
    }
    redbutton_lastState = redbutton.getState();        // save last red button state
  }
}
