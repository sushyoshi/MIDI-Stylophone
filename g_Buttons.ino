//////////////////////////////////////////////// YELLOW BUTTON PRESSES /////////////////////////////////////////////////////////

void yellowbutton_pressed() { 
  
  if(yellowbutton.isPressed()){
    yellowpressedTime = millis();
    yellowisPressing = true;
    yellowisLongDetected = false;
  }

// ======================== SHORT PRESS ============================ //

  if(yellowbutton.isReleased()) {
    yellowisPressing = false;
    yellowreleasedTime = millis();    
    long pressDuration = yellowreleasedTime - yellowpressedTime;

    if( pressDuration < SHORT_PRESS_TIME ){
      
      if ((mode == 1) && (digitalRead(tuning_switchpin) == HIGH)){ // If we are in COMPOSER MODE    
        play_record_buffer = !play_record_buffer;     
      }

      if ((mode == 1) && (digitalRead(tuning_switchpin) == LOW)){ // If we are in TUNING MODE   
        play_new_record = !play_new_record;  
      }
    } 
  }

  if (play_new_record) {    // keeps looping the melody of the new values from Tuning mode
    tuning_player(5, tempo5, n_record_notes, new_record_notes, new_record_durations);
  }

  if (play_record_buffer) {    // keeps looping the melody of the record buffer from Composer Mode
    tuning_player(5, tempo5, n_record_notes, record_notes, record_durations);
  }

// ======================== LONG PRESS ============================ //


  if(yellowisPressing == true && yellowisLongDetected == false) {
    long pressDuration = millis() - yellowpressedTime;

    if( pressDuration > LONG_PRESS_TIME ) {

      if ((mode == 1) && (digitalRead(tuning_switchpin) == HIGH)){ // If we are in COMPOSER MODE
         
      }

      if ((mode == 1) && (digitalRead(tuning_switchpin) == LOW)){  // If we are in TUNING MODE

      }    
      yellowisLongDetected = true;
    }
  }
}

//////////////////////////////////////////////// RED BUTTON PRESSES /////////////////////////////////////////////////////////

void redbutton_pressed(){                

  if(redbutton.isPressed()){
    redpressedTime = millis();
    redisPressing = true;
    redisLongDetected = false;
  }

// ======================== SHORT PRESS ============================ //

  if(redbutton.isReleased()) {
    redisPressing = false;
    redreleasedTime = millis();

    long pressDuration = redreleasedTime - redpressedTime;

    if( pressDuration < SHORT_PRESS_TIME ){           // When it is detected a short press
      
      if ((mode == 1) && (digitalRead(tuning_switchpin) == HIGH)){ // If we are in COMPOSER MODE

        note_counter--;                               // decreases note_counter     
        if (note_counter <=0){
          note_counter = 0;
        }
        
        lcd.setCursor(13, 0);                         //
        lcd.print("   ");                             // Clears screen area that displays the note_counter
        lcd.setCursor(13, 0);
        lcd.print(note_counter);                      // Displays the previous note_counter
        lcd.setCursor(note_counter, 1);               
        lcd.print("   ");                             // Clears screen area with the musical notation symbol
        lcd.setCursor(note_counter, 1);
        lcd.write(0);                                 // displays musical notation symbol on counter position
        noteOn(5, record_notes[note_counter], 127);   // Plays the note of the current note_counter for 1/4 second
        delay(250);
        noteOff(5, record_notes[note_counter], 0);
      }       
    
    }
  }


// ======================== LONG PRESS ============================ //


  if(redisPressing == true && redisLongDetected == false) {
    long pressDuration = millis() - redpressedTime;

    if( pressDuration > LONG_PRESS_TIME ) {

      if ((mode == 1) && (digitalRead(tuning_switchpin) == HIGH)){ // If we are in COMPOSER MODE

        for (int i = 0; i <= 128; i++) {                    
          record_notes[i] = 0;              // it will set to 0 all notes recorded on the record_notes array
          new_record_notes[i] = 0;         // it will set to 0 all notes recorded on the record_notes array from Tuning Mode
        }
        note_counter = 0;                          // it will reset the note counter
        lcd.setCursor(0, 0);
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[12])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
//        lcd.print("Record Buffer   ");
        lcd.setCursor(0, 1);
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[13])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
//        lcd.print("Cleared !       ");
        delay(1000);
      }

      if ((mode == 1) && (digitalRead(tuning_switchpin) == LOW)){      // If we are in TUNING MODE
  
      }    
      redisLongDetected = true;
    }
  }
}

//////////////////////////////////////////////// BLUE 2 BUTTON PRESSES /////////////////////////////////////////////////////////

void bluebutton2_pressed(){                

  if(bluebutton2.isPressed()){
    yellowpressedTime = millis();
    yellowisPressing = true;
    yellowisLongDetected = false;
  }


// ======================== SHORT PRESS ============================ //


  if(bluebutton2.isReleased()) {
    yellowisPressing = false;
    yellowreleasedTime = millis();

    long pressDuration = yellowreleasedTime - yellowpressedTime;

    if( pressDuration < SHORT_PRESS_TIME ){           // When it is detected a short press
      
      if ((mode == 1) && (digitalRead(tuning_switchpin) == LOW)){ // If we are in TUNING MODE
        note_counter++;                             // increase current_note number
        note_counter %= 128;                        // limit current_note variable (0 - 127)
        lcd.clear();
      }       
    }
  }
}

//////////////////////////////////////////////// BLUE 1 BUTTON PRESSES /////////////////////////////////////////////////////////

void bluebutton1_pressed(){                 

  if(bluebutton1.isPressed()){
    bluepressedTime = millis();
    blueisPressing = true;
    blueisLongDetected = false;
  }


// ======================== SHORT PRESS ============================ //


  if(bluebutton1.isReleased()) {
    blueisPressing = false;
    bluereleasedTime = millis();

    long pressDuration = bluereleasedTime - bluepressedTime;

    if( pressDuration < SHORT_PRESS_TIME ){           // When it is detected a short press
      
      if ((mode == 1) && (digitalRead(tuning_switchpin) == LOW)){ // If we are in TUNING MODE
        note_counter--;                              // decrease current_note number
        note_counter %= 128;                         // limit current_note variable (0 - 127) 
        note_counter = abs(note_counter);            // makes sure that the value will never go negative
        lcd.clear();
      }       
    }
  }

// ======================== LONG PRESS ============================ //


  if(blueisPressing == true && blueisLongDetected == false) {
    long pressDuration = millis() - bluepressedTime;

    if( pressDuration > LONG_PRESS_TIME ) {

      if ((mode == 1) && (digitalRead(tuning_switchpin) == LOW)){ // If we are in TUNING MODE

        note_counter = 0;                           // Reset the note counter

      }
  
      blueisLongDetected = true;
    }
  }
}
