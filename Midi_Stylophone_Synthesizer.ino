/*  This project is composed of a MIDI controller and a MIDI synthesizer all in one single equipment
    The stylophone is used as a MIDI controller, along with with the potentiometers connected to the analog inputs.
    The MIDI information is transmitted to a VS1053 MIDI synthesizer chip which will interpret the information and produce sounds accordingly

    The Stylophone input keys are all connected to digital ports
    Stylo is connected to GND from Arduino

    POTS:

    A0 - Pitch Bend Pot / Note Modifier in Tuning Mode
    A1 - Octave Selection / Duration Modifier in Tuning Mode   
    A2 - Tempo                
    A3 - Not Used     

    CONTROLS:

      STYLOPHONE MODE - mode0:

        Use the stylus on the keys to play the respective note of the current octave on channel 0
         Octave pot will select the octave range for the keys - Total of 4 octaves from C0 to G9
         Pitch Bend pot will bend the note of the note that is playing
         Yellow and Blue buttons - next and previous instrument on specified channel 0
         Red button - not used
        
        Switch 1 or 2 ON - Start looping presets on channels 1 or 2 -
        
          Pots - change various parameters such as tempo and pitch bend
          Red Button 1 or 2 - While pressed, allows control over respective channel and preset playing on it, such as:
          Red button - choose the preset to loop on the channel
          Blue buttons - next and previous instrument on specified channel

        Switch 3 or 4 ON - Start looping records (saved on EEPROM) on channels 3 and 4 - Records were composed on Composer Mode

          Pots - change various parameters such as tempo and pitch bend
          Red Button 1 or 2 - While pressed, allows control over respective channel and record playing on it, such as:
          Red button - choose the record to loop on the channel. Default record is the buffer record fromm composer mode
          Blue buttons - next and previous instrument on specified channel

      COMPOSER MODE - mode1:

        Same controls as no stylophone mode, except each note played and its duration is recorded an buffer arrays.
          Red button
            Long Press: will clear the notes played and durations buffer, to allow start a new recording
            Short Press: rewind to previous key note played, causing the note counter to decrease
          Red 1, 2, 3 and 4 button, when pressed, will copy the notes and durations from buffer arrays to record 1,2,3 or 4
    

   TO BE DONE:

    - Be able to only change tempo
    - Improve Tuning Mode

*/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include "definitions_variables.h"
#include "RT_MIDI_init.h"
#include "keys.h"
#include "notes.h"
#include "instruments.h"
#include "lcd.h"
#include "presets.h"
#include "records.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <ezButton.h>



LiquidCrystal_I2C lcd(0x27, 20, 4);             // set the LCD address to 0x27 for a 16 chars and 2 line display

ezButton bluebutton1(19);  // create ezButton object that attach to pin 19;
ezButton bluebutton2(17);   // create ezButton object that attach to pin 17;
ezButton redbutton(22);   // create ezButton object that attach to pin 22;
ezButton yellowbutton(18);   // create ezButton object that attach to pin 22;
ezButton red1button(3);  // create ezButton object that attach to pin 3;
ezButton red2button(14);  // create ezButton object that attach to pin 14;
ezButton red3button(15);  // create ezButton object that attach to pin 15;
ezButton red4button(16);  // create ezButton object that attach to pin 16;


void setup() {

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<< Setup Code to intitialize the VS1053 module in Real-Time MIDI mode on SPI>>>>>>>>>>>>>
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  pinMode(VS_DREQ, INPUT);
  pinMode(VS_XCS, OUTPUT);
  pinMode(VS_XDCS, OUTPUT);
  digitalWrite(VS_XCS, HIGH); //Deselect Control
  digitalWrite(VS_XDCS, HIGH); //Deselect Data
  pinMode(VS_RESET, OUTPUT);

  //Initialize VS1053 chip
  digitalWrite(VS_RESET, LOW); //Put VS1053 into hardware reset

  // Setup SPI for VS1053
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  //From page 12 of datasheet, max SCI reads are CLKI/7. Input clock is 12.288MHz.
  //Internal clock multiplier is 1.0x after power up.
  //Therefore, max SPI speed is 1.75MHz. We will use 1MHz to be safe.
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.transfer(0xFF); //Throw a dummy byte at the bus

  delayMicroseconds(20);  // just allow for some time to pass
  digitalWrite(VS_RESET, HIGH); //Bring up VS1053

  // Load the realtime MIDI plugin
  VSLoadUserCode();
  delay(50);

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  Serial.begin(9600); //Use serial for debugging

  lcd.begin();                      // Initialize LCD
  lcd.backlight();
  lcd.createChar(0, note_symbol);

  pinMode(switch1pin, INPUT_PULLUP);
  pinMode(switch2pin, INPUT_PULLUP);
  pinMode(switch3pin, INPUT_PULLUP);
  pinMode(switch4pin, INPUT_PULLUP);
  pinMode(mode_switchpin, INPUT_PULLUP);
  pinMode(tuning_switchpin, INPUT_PULLUP);
  
  bluebutton2.setDebounceTime(20); // set debounce time to 50 milliseconds
  bluebutton1.setDebounceTime(20); // set debounce time to 50 milliseconds
  redbutton.setDebounceTime(50); // set debounce time to 50 milliseconds
  yellowbutton.setDebounceTime(50); // set debounce time to 50 milliseconds
  
  red1button.setDebounceTime(50); // set debounce time to 50 milliseconds
  red2button.setDebounceTime(50); // set debounce time to 50 milliseconds
  red3button.setDebounceTime(50); // set debounce time to 50 milliseconds
  red4button.setDebounceTime(50); // set debounce time to 50 milliseconds

  for (byte i = 0; i < n_keys; i++){
    key[i].setDebounceTime(20); // set debounce time to 20 milliseconds
  }
  
  
  //  talkMIDI(0xB0, 0x07, 127);               //0xB0 is channel message, set channel volume to near max (127)

}


void loop() {

  bluebutton2.loop(); // MUST call the loop() function first
  bluebutton1.loop(); // MUST call the loop() function first
  redbutton.loop(); // MUST call the loop() function first
  yellowbutton.loop(); // MUST call the loop() function first

  red1button.loop(); // MUST call the loop() function first
  red2button.loop(); // MUST call the loop() function first
  red3button.loop(); // MUST call the loop() function first
  red4button.loop(); // MUST call the loop() function first

  for (byte i = 0; i < n_keys; i++){
    key[i].loop(); // set debounce time to 50 milliseconds
  } 


  if (digitalRead(mode_switchpin) == HIGH) {
    mode = 0; // Stylophone Mode
  }
  if (digitalRead(mode_switchpin) == LOW) {
    mode = 1; // Composer Mode
  }


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Stylophone Mode >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  if (mode == 0) {

    if (lcd_mode0state == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[0])));  // Copy lcd word from program memory to buffer
      lcd.print(buffer);
      //lcd.print ("Stylophone Mode");
      lcd_mode0state = 1;
      lcd_mode1state = 0;
      lcd_mode2state = 0;
    }


    stylophone_player(0);      // calls function of stylophone player using keys and octave pot on channel 0

    pitch_bending();

    instrument_select(0);

    Preset_Player();

    Record_Player();
  }



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Composer Mode >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  if (mode == 1) {            // From here can choose either composer mode or tuning mode depending on switch4pin


    
    if (digitalRead(tuning_switchpin) == HIGH) {   // ENTER COMPOSER MODE

      if (lcd_mode1state == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[1])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
        lcd_mode0state = 0;
        lcd_mode1state = 1;
        lcd_mode2state = 0;
        previous_tuning_switchpin = HIGH;
      }

    stylophone_player(5);      // calls function of stylophone player using keys and octave pot on channel 5

    instrument_select(5);      // calls function for instrument selection on channel 5 - stylophone player

    recording();               // calls function to record each note and duration whenever a key is pressed
    
    redbutton_pressed();

    yellowbutton_pressed();
    
    }    




    if (digitalRead(tuning_switchpin) == LOW) {   // ENTER TUNING MODE

      if (lcd_mode2state == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        strcpy_P(buffer, (char *)pgm_read_word(&(lcd_table[2])));  // Copy lcd word from program memory to buffer
        lcd.print(buffer);
        //lcd.print ("Tuning Mode");
        lcd_mode0state = 0;
        lcd_mode1state = 0;
        lcd_mode2state = 1;
      }
   
      tuning_mode();                        // calls function to fine tune record buffer notes and durations

      redbutton_pressed();
      
      yellowbutton_pressed();

      bluebutton2_pressed();
      
      bluebutton1_pressed();
    }
  }
}
                            
