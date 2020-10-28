
void Record_Player(){

    if (digitalRead(switch3pin) == LOW) {

      if (record3 == 0) {     
        //record_player(3, tempo3, n_record_notes, record_notes, record_durations);
      }
      if (record3 == 1) {
        readIntArrayFromEEPROM(0, record1_notes, 128);
        readIntArrayFromEEPROM(256, record1_durations, 128);
        record1_instrument = EEPROM.read(2049);  // Read the record 1 instrument to EEPROM
        talkMIDI(0xC0 | 3, record1_instrument, 0);             // Changes intrument of channel 3 to record1 instrument 
        record_player(3, tempo3, n_record_notes, record1_notes, record1_durations);
      }
      if (record3 == 2) {
        readIntArrayFromEEPROM(512, record2_notes, 128);
        readIntArrayFromEEPROM(768, record2_durations, 128);
        record2_instrument = EEPROM.read(2050); 
        talkMIDI(0xC0 | 3, record2_instrument, 0); // Changes intrument of channel 3 to record2 instrument        
        record_player(3, tempo3, n_record_notes, record2_notes, record2_durations);
      }
      if (record3 == 3) {
        readIntArrayFromEEPROM(1024, record3_notes, 128);
        readIntArrayFromEEPROM(1280, record3_durations, 128);
        record3_instrument = EEPROM.read(2051);
        talkMIDI(0xC0 | 3, record3_instrument, 0); // Changes intrument of channel 3 to record3 instrument          
        record_player(3, tempo3, n_record_notes, record3_notes, record3_durations);
      }
      if (record3 == 4) {
        readIntArrayFromEEPROM(1536, record4_notes, 128);
        readIntArrayFromEEPROM(1792, record4_durations, 128);
        record4_instrument = EEPROM.read(2052);
        talkMIDI(0xC0 | 3, record4_instrument, 0); // Changes intrument of channel 3 to record4 instrument          
        record_player(3, tempo3, n_record_notes, record4_notes, record4_durations);
      }

      if (red3button.getState() == LOW) {                                              // while red3button is pressed

        instrument_select(3);
        preset_select(3);
      }
    }else{talkMIDI(0xB0 | 3, 0x78, 0);} // Silences this channel


    if (digitalRead(switch4pin) == LOW) {

      if (record4 == 0) {     
        //record_player(5, tempo4, n_record_notes, record_notes, record_durations); // Play the record buffer on channel 5
      }
      if (record4 == 1) {
        readIntArrayFromEEPROM(0, record1_notes, 128);
        readIntArrayFromEEPROM(256, record1_durations, 128);
        record1_instrument = EEPROM.read(2049);
        talkMIDI(0xC0 | 4, record1_instrument, 0); // Changes intrument of channel 3 to record1 instrument  
        record_player(4, tempo4, n_record_notes, record1_notes, record1_durations);
      }
      if (record4 == 2) {
        readIntArrayFromEEPROM(512, record2_notes, 128);
        readIntArrayFromEEPROM(768, record2_durations, 128);
        record1_instrument = EEPROM.read(2050);
        talkMIDI(0xC0 | 4, record2_instrument, 0); // Changes intrument of channel 3 to record2 instrument          
        record_player(4, tempo4, n_record_notes, record2_notes, record2_durations);
      }
      if (record4 == 3) {
        readIntArrayFromEEPROM(1024, record3_notes, 128);
        readIntArrayFromEEPROM(1280, record3_durations, 128);
        record1_instrument = EEPROM.read(2051);
        talkMIDI(0xC0 | 4, record3_instrument, 0); // Changes intrument of channel 3 to record3 instrument          
        record_player(4, tempo4, n_record_notes, record3_notes, record3_durations);
      }
      if (record4 == 4) {
        readIntArrayFromEEPROM(1536, record4_notes, 128);
        readIntArrayFromEEPROM(1792, record4_durations, 128);
        record1_instrument = EEPROM.read(2052);
        talkMIDI(0xC0 | 4, record4_instrument, 0); // Changes intrument of channel 3 to record4 instrument          
        record_player(4, tempo4, n_record_notes, record4_notes, record4_durations);
      }

      if (red4button.getState() == LOW) {               // while red4button is pressed

        instrument_select(4);
        preset_select(4);
      }
    }else{talkMIDI(0xB0 | 4, 0x78, 0);}               // Silences this channel  
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void record_player(int channel, float tempo, int n_record_notes, int record_notes[], int record_durations[] ) {

  tempo_control();                          // instantiate tempo control


  if (channel == 5) {                         // This channel is used to play record buffer in Composer Mode

    static uint32_t previousMillis5 = 0;
    static byte r = 0;                        // sets initial value of l


    if (millis() - previousMillis5 >= record_durations[r] * tempo) { // checks to see if the record duration for the
      // current note has passed, when multiplied by the tempo

      noteOff(channel, record_notes[r - 1], 0); // Stops playing last record note on specified channel
      noteOn(channel, record_notes[r], 127);  // Starts playing current record note on specified channel, maximum volume
      lcd.setCursor(0, 0);
      lcd.print(record_notes[r]);
      strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[5])));  // Copy lcd word from program memory to buffer
      lcd.print(buffer);
//      lcd.print("     Record_Buff");
      lcd.setCursor(r, 1);
      if (r > 15) {
        lcd.setCursor((r - 16), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
      }
      if (r > 31) {
        lcd.setCursor((r - 32), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
      }
      if (r > 47) {
        lcd.setCursor((r - 48), 1);
      }
      if (r > 63) {
        lcd.setCursor((r - 64), 1);
      }
      if (r > 79) {
        lcd.setCursor((r - 80), 1);
      }
      if (r > 95) {
        lcd.setCursor((r - 96), 1);
      }
      if (r > 111) {
        lcd.setCursor((r - 112), 1);
      }      
      lcd.print(" ");
      lcd.write(0);                            // makes display a musical note symbol when note is played

      previousMillis5 = millis();              // saves current time

      r++;                                     // increases counter variable m to go to play next note

      if (record_notes[r] == 0) {                     // checks the limit of the recorded array (hitting an empty note)
        r = 0;                                        // restarts counter
      }
    }
  }


  if (channel == 3) {

    static uint32_t previousMillis3 = 0;
    static byte l = 0;                        // sets initial value of l


    if (millis() - previousMillis3 >= record_durations[l] * tempo) { // checks to see if the record duration for the
      // current note has passed, when multiplied by the tempo

      noteOff(channel, record_notes[l - 1], 0); // Stops playing last record note on specified channel
      noteOn(channel, record_notes[l], 127);  // Starts playing current record note on specified channel, maximum volume
      lcd.setCursor(0, 0);
      lcd.print(record_notes[l]);
      if (record3 >= 1){
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[6])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
//        lcd.print("      Record ");
        lcd.print(record3);
      }else{
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[7])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
//        lcd.print("   Buff Record ");
        }
      lcd.setCursor(l, 1);
      if (l > 15) {
        lcd.setCursor((l - 16), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
      }
      if (l > 31) {
        lcd.setCursor((l - 32), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
      }
      if (l > 47) {
        lcd.setCursor((l - 48), 1);
      }
      if (l > 63) {
        lcd.setCursor((l - 64), 1);
      }
      if (l > 79) {
        lcd.setCursor((l - 80), 1);
      }
      if (l > 95) {
        lcd.setCursor((l - 96), 1);
      }
      if (l > 111) {
        lcd.setCursor((l - 112), 1);
      }
      lcd.print(" ");
      lcd.write(0);                            // makes display a musical note symbol when note is played

      previousMillis3 = millis();              // saves current time

      l++;                                     // increases counter variable m to go to play next note

      if (record_notes[l] == 0) {                     // checks the limit of the recorded array (hitting an empty note)
        l = 0;                                        // restarts counter
      }
    }
  }


  if (channel == 4) {

    static uint32_t previousMillis4 = 0;
    static byte m = 0;                        // sets initial value of m


    if (millis() - previousMillis4 >= record_durations[m] * tempo) { // checks to see if the record duration for the
      // current note has passed, when multiplied by the tempo

      noteOff(channel, record_notes[m - 1], 0); // Stops playing last record note on specified channel
      noteOn(channel, record_notes[m], 127);  // Starts playing current record note on specified channel, maximum volume
      lcd.setCursor(0, 0);
      lcd.print(record_notes[m]);
      if (record4 >= 1){
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[6])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
//        lcd.print("      Record ");
        lcd.print(record4);
      }else{
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[7])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
//        lcd.print("   Buff Record ");
        }
      lcd.setCursor(m, 1);
      if (m > 15) {
        lcd.setCursor((m - 16), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
      }
      if (m > 31) {
        lcd.setCursor((m - 32), 1); // makes LCD cursor go back to stareting position when it hits the end os screen
      }
      if (m > 47) {
        lcd.setCursor((m - 48), 1);
      }
      if (m > 60) {
        lcd.setCursor((m - 61), 1);
      }
      if (m > 77) {
        lcd.setCursor((m - 78), 1);
      }
      if (m > 95) {
        lcd.setCursor((m - 96), 1);
      }
      if (m > 111) {
        lcd.setCursor((m - 112), 1);
      }      
      lcd.print(" ");
      lcd.write(0);                            // makes display a musical note symbol when note is played

      previousMillis4 = millis();              // saves current time

      m++;                                     // increases counter variable m to go to play next note

      if (record_notes[m] == 0) {                     // checks the limit of the recorded array (hitting an empty note)
        m = 0;                                        // restarts counter
      }
    }
  }
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

void readIntArrayFromEEPROM(int address, int numbers[], int arraySize)
{
  int addressIndex = address;
  for (int i = 0; i < arraySize; i++)
  {
    numbers[i] = (EEPROM.read(addressIndex) << 8) + EEPROM.read(addressIndex + 1);
    addressIndex += 2;
  }
}
