void tuning_mode(){

  
  static int durations_modifier[] = {0,0,0,0,63,63,63,63,125,125,125,125,250,250,250,250,500,500,500,500,999,999,999,999};
  static int notes_modifier[] = {-20,-20,-20,-19,-19,-19,-18,-18,-18,-17,-17,-17,-16,-16,-16,-15,-15,-15,-14,-14,-14,
                                 -13,-13,-13,-13,-12,-12,-12,-11,-11,-11,-10,-10,-10,-9,-9,-9,-8,-8,-8,-7,-7,-7,-6,-6,
                                 -6,-5,-5,-5,-4,-4,-4,-3,-3,-3,-2,-2,-2,-1,-1,-1,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,
                                 6,6,6,7,7,7,8,8,8,9,9,9,10,10,10,11,11,11,12,12,12,13,13,13,14,14,14,15,15,15,16,16,16,
                                 17,17,17,18,18,18,19,19,19,20,20,20};
 
  int notes_modifier_select= analogRead(A3);
  int previous_notes_modifier_select;
  notes_modifier_select= map(notes_modifier_select, 0, 1023, 0, 123);
  
  int durations_modifier_select = analogRead(A2);
  int previous_durations_modifier_select;
  durations_modifier_select = map (durations_modifier_select, 0, 1023, 0, 23);

  
  lcd.setCursor(0, 0);
  lcd.print("    (");
  lcd.print(record_notes[note_counter]);
  lcd.print(")");
  lcd.print("   (");
  lcd.print(record_durations[note_counter]);
  lcd.print(")");  
  lcd.setCursor(0, 1);
  lcd.print(note_counter);
  lcd.print("   N=");
  lcd.print(new_record_notes[note_counter]);
  lcd.print("  D= ");
  lcd.print(new_record_durations[note_counter]);



  if (redbutton.getState() == LOW) {                                    // WHile the red button is pressed
      
    if (notes_modifier_select != previous_notes_modifier_select){        // if the A3 pot value is changed
  
      new_record_notes[note_counter] = record_notes[note_counter] + notes_modifier[notes_modifier_select]; // update the value of new_record_notes
      previous_notes_modifier_select = notes_modifier_select; 
    }
  
    if (durations_modifier_select != previous_durations_modifier_select){
  
      new_record_durations[note_counter] = durations_modifier[durations_modifier_select];
      previous_durations_modifier_select = durations_modifier_select;
    }
  }

  if (red1button.isReleased()) {                     // if red1 button is pressed

    writeIntArrayIntoEEPROM(0, new_record_notes, 128);  // Write 2 bytes on position 0 and 1 of EEPROM [] with [] size 128
    writeIntArrayIntoEEPROM(256, new_record_durations, 128); // Start writing on position 256 of EEPROM record_durations[]
    EEPROM.write(2049, instrument);               // Write the record 1 instrument to EEPROM
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[8])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 1 Saved");
    delay(500);
  }

  if (red2button.isReleased()) {                  // if red2 button is pressed
    
    writeIntArrayIntoEEPROM(512, new_record_notes, 128);
    writeIntArrayIntoEEPROM(768, new_record_durations, 128);
    EEPROM.write(2050, instrument);
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[9])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 2 Saved");
    delay(500);
  }

  if (red3button.isReleased()) {                  // if red3 button is pressed
   
    writeIntArrayIntoEEPROM(1024, new_record_notes, 128);
    writeIntArrayIntoEEPROM(1280, new_record_durations, 128);
    EEPROM.write(2051, instrument);
    lcd.clear();
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[10])));  // Copy lcd word from program memory to buffer
    lcd.print(buffer);
//    lcd.print("Record 3 Saved");
    delay(500);
  }

  if (red4button.isReleased()) {                  // if red4 button is pressed
    
    writeIntArrayIntoEEPROM(1536, new_record_notes, 128);
    writeIntArrayIntoEEPROM(1792, new_record_durations, 128);
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

void tuning_player(int channel, float tempo, int n_record_notes, int record_notes[], int record_durations[] ) {

  tempo_control();                          // instantiate tempo control


  if (channel == 5) {

    static uint32_t previousMillis5 = 0;
    static byte r = 0;                        // sets initial value of l


    if (millis() - previousMillis5 >= record_durations[r] * 1) { // checks to see if the record duration for the
      // current note has passed, when multiplied by the tempo... in this case, tempo = 1

      noteOff(channel, record_notes[r - 1], 0); // Stops playing last record note on specified channel
      noteOn(channel, record_notes[r], 127);  // Starts playing current record note on specified channel, maximum volume      
      previousMillis5 = millis();              // saves current time
      r++;                                     // increases counter variable m to go to play next note

      if (record_notes[r] == 0) {                     // checks the limit of the recorded array (hitting an empty note)
        r = 0;                                        // restarts counter
      }
    }
  }
} 
