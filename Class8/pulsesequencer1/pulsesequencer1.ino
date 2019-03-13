//
// pulsesequencer1
// 
// 4-voice, 16-step pulse sequencer for 
// eurorack / serge modular triggering
// by arduino.
// 
// rld, I<3DM, 3.19
//
// sequencer uses 16 LEDs as a 5-view interface
// controlled by 4 momentary switches and a pot.
//
// assumes:
// 4 buttons and a pot (INPUT)
// 16 stage leds (via 2x74HC595) and 4 trigger leds (OUTPUT)
// outputs are split to banana jacks for wiring
//

const boolean db = false; // debug state

// timing for rtsked implementation:
unsigned long now;
unsigned long then;
// master clock - controlled by pot:
unsigned long interval = 1000; 

// pins:
const int latchPin = 12; // shift register latch
const int clockPin = 13; // shift register clock
const int dataPin = 11; // shift register data
const int aPin = 2; // button input 1
const int bPin = 3; // button input 2
const int cPin = 4; // button input 3
const int dPin = 5; // button input 4
const int kPin = A0; // analog pot input
const int s1Pin = 7; // output for sequence 1 pulses
const int s2Pin = 8; // output for sequence 2 pulses
const int s3Pin = 9; // output for sequence 3 pulses
const int s4Pin = 10; // output for sequence 4 pulses

// sequencer:
byte sptr = 0; // sequence ptr
byte led1 = 0; // first 8 lights
byte led2 = 0; // second 8 lights
// initial sequences:
boolean s1[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
boolean s2[] = {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0};
boolean s3[] = {1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
boolean s4[] = {0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1};

// pulse output pins
const int ptime = 20; // pulse high time
int s1p = 0; // pulse state for output 1
int s2p = 0; // pulse state for output 2
int s3p = 0; // pulse state for output 3
int s4p = 0; // pulse state for output 4

// view:
// 0 = sequence position
// 1-4 = bank 1-4
byte view = 0;
// old button states:
boolean a_o = 0;
boolean b_o = 0;
boolean c_o = 0;
boolean d_o = 0;

char crsr = 0; // current "cursor" for sequence editing
int cp = 0; // cursor blink state
const int crsrtime = 1000; // cursor blink time

// see tabs for routines...
