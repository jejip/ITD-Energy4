/* TU Delft
 * Interactive Technology Design 2015
 *
 * Group Energy 4
 * 
 * June 2015
 */


/*
 *  Definitions for outgoing values
 *
 */

// Defining the generic analog sensors
int sensor0 = A0;    // generic sensor 0
int sensor1 = A1;    // generic sensor 1
int sensor2 = A2;    // generic sensor 2
int sensor3 = 4;    // digital sensor 3

// values for the sensors
int sensorValue0 = 0; //distance sensor
int sensorValue1 = 0; //radiator pot meter
int sensorValue2 = 0; //power plug (light)
bool sensorValue3 = 0; //Light switch

unsigned long lastTimeSent = 0;

/*
 *  Definitions for incoming values
 *
 */
 
byte incoming = 0;
byte value = 0;
  
bool stepper1_enable = 0;
int stepper1_pos = 0;
int stepper1_speed = 700;

bool stepper2_enable = 0;
int stepper2_pos = 0;
int stepper2_speed = 700;

int led_pos = 0;
int led_speed = 0;
int led_hue = 0;
int led_state = 0;

int display_value = 1; //show display on startup

int num_identifiers = 10; //value for the number of identifiers

bool stepper1_enable_last = 1; //store last value to poll status of steppers, starts as on
bool stepper2_enable_last = 1;

/*
 *  LEDs
 *  30 Neopixels with the FASTled library
 */

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

#define LED_DT 5                                             // Serial data pin
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B
#define LED_TYPE WS2812B                                       // What kind of strip are you using (APA102, WS2801 or WS@2812B
#define NUM_LEDS 30                                           // Number of LED's

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
#define BRIGHTNESS 255                                          // 


/*
 *  Display
 *  7 segment display and small led matrix by Adafruit on I2C
 */

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();            // attaches I2C

#define Wh_led 4                                            // attaches leds to pin 4

int Wh_value = 0;

Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();

//the led data to display the W
static const uint8_t PROGMEM
W[] =
  { B10000001,
    B10000001,
    B10000001,
    B10011001,
    B10011001,
    B11011011,
    B01100110,
    B00100100 };


/*
 *  Rotary encoder
 *  Grove rotary encoder
 */

#include <Encoder.h>                                        //attaches to pin 2 and 3
#include <TimerOne.h>

int rotary = 0;

/*
 *  Stepper motors
 *  2 stepper motors with the adafruit motor shield
 */

#include <AccelStepper.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //init the shield

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield, on address 1 (M1&M2) and 2 (M3&M4)
Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMS.getStepper(200, 2);

// you can change these to DOUBLE or SINGLE or MICROSTEP or INTERLEAVE!
// wrappers for the motor!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, INTERLEAVE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, INTERLEAVE);
}

// Now we'll wrap the 2 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


/*
 *  SETUP
 *
 */

void setup() {
  delay(3000); //some delay to enable re-uploading a sketch  
  
  // Initiate serial communication
  Serial.begin(115200);
  
  //set analog inputs as inputs
  pinMode(sensor0, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT_PULLUP); //because it's a switch we need to activate the internal pullup resistor
  
  //attach leds
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2801 or APA102
  FastLED.setBrightness(BRIGHTNESS);

  //attach segment display
  matrix.begin(0x71); // add the 7 segment display. added a jumper to change the default address
  matrix2.begin(0x72);  // add the 8x8 led matrix
  
  matrix2.setBrightness(3); //led matrix is wayy brighter than the values

  //rotary encoder
  encoder.Timer_init();

  //setup stepper
  AFMS.begin(); // Start the bottom shield
   
  stepper1.setMaxSpeed(1420); //maximum is 1420
  stepper1.setAcceleration(800); //not really a maximum
    
  stepper2.setMaxSpeed(50);
  stepper2.setAcceleration(30);
  
}


/*
 *  LOOP
 *
 */

void loop() {
  // read the serial input from the max patch
  readIncoming();
  
  //show LEDs
  showleds();
  
  //move stepper
  movesteppers();
  
  //receive rotary encoder values
  // one full neo turn is 400 steps (+ -)
  if (encoder.rotate_flag ==1)
  {
    if (encoder.direct==0)
    { rotary--;}
     else
     {rotary++;}
    encoder.rotate_flag =0;
  }
  
  //show segmented display
  show_display();
  
  //Send values from the analog inputs back
  sendvalues();

}
