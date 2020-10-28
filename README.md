# MIDI-Stylophone
Arduino controlled MIDI Stylophone using the VS1053 module

    This project is composed of a MIDI controller and a MIDI synthesizer all in one single equipment
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

    - Optimize code
    - Improve Tuning Mode
    - Add more slots to save records (on EEPROM)


