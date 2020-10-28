
#define switch1pin 13
#define switch2pin 12
#define switch3pin 11
#define switch4pin 10
#define mode_switchpin 5
#define tuning_switchpin 4

#define n_keys 26                     // Number of stylophone keys

int mode = 0;                         // mode 0 = stylophone mode ; mode 1 = sequencer mode

int lcd_mode0state;                   // mode 0 lcd state - Stylophone Mode
int lcd_mode1state;                   // mode 1 lcd state - Composer Mode
int lcd_mode2state;                   // mode 2 lcd state - Tuning Mode

int channel;                          // Channel selection variable

static uint8_t instrument = 0;            // instrument variable used in functions
static uint8_t previous_instrument = 0;   // previous instrument value variable

int octavepot;                        // Octave selection potentiometer
int octave;                           // Octave variable

float tempo = 1;                    // sets initial tempo to 1 as default
float tempo1 = 1;
float tempo2 = 1;
float tempo3 = 1;
float tempo4 = 1;
float tempo5 = 1;

int preset;                         // Variable for preset loops selection
int preset1;
int preset2;
int record3 = 1;                    // Variable for recorded loops selection
int record4 = 1;

uint8_t note_symbol[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};  // Code to create a music notation symbol on LCD

const int SHORT_PRESS_TIME = 1000; // 1000 milliseconds
const int LONG_PRESS_TIME  = 1000; // 1000 milliseconds

int redbutton_lastState;
unsigned long redpressedTime  = 0;
unsigned long redreleasedTime = 0;
bool redisPressing = false;
bool redisLongDetected = false;

unsigned long yellowpressedTime  = 0;
unsigned long yellowreleasedTime = 0;
bool yellowisPressing = false;
bool yellowisLongDetected = false;

unsigned long bluepressedTime  = 0;
unsigned long bluereleasedTime = 0;
bool blueisPressing = false;
bool blueisLongDetected = false;

int note_counter;

int previous_tuning_switchpin;

bool play_new_record = false;
bool play_record_buffer = false;
