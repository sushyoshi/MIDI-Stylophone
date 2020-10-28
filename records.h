
int n_record_notes = 128;

int duration_buffer[128] = {};  // buffer array used to store millis() information to calculate record_durations[]


int new_record_notes[128] = {0};              // Recorded notes from Tuning mode before being tuned
int new_record_durations[128] = {}; // Recorded durations from Tuning mode before being tuned

int record_notes[128] = {0};              // Recorded notes from Composer mode will be stored here
int record_durations[128] = {}; // Recorded durations from Composer mode will be stored here

int record1_notes[128] = {};             // Preset saved from record_notes on Composer Mode
int record1_durations[128] = {};// Preset saved from record_durations on Composer Mode
int record1_instrument;

int record2_notes[128] = {};             // Preset saved from record_notes on Composer Mode
int record2_durations[128] = {};// Preset saved from record_durations on Composer Mode
int record2_instrument;

int record3_notes[128] = {};             // Preset saved from record_notes on Composer Mode
int record3_durations[128] = {};// Preset saved from record_durations on Composer Mode
int record3_instrument;

int record4_notes[128] = {};             // Preset saved from record_notes on Composer Mode
int record4_durations[128] = {};// Preset saved from record_durations on Composer Mode
int record4_instrument;
