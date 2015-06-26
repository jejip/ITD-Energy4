/*
 * Made by Imara Speek, Paul Groenendaal and Aadjan van der Helm
 *
 * February 26 2015
 *
 */

// Defining the generic analog sensors
int sensor0 = A0;    // generic sensor 0
int sensor1 = A1;    // generic sensor 1


// values for the sensors
int sensorValue0 = 0;
int sensorValue1 = 0;

unsigned long lastTimeSent = 0;

//incoming values
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

int display_value = 0;

int num_identifiers = 10; //value for the number of identifiers

bool stepper1_enable_last = 1; //store last value to poll status of steppers, starts as on
bool stepper2_enable_last = 1;

// LEDS

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

#define LED_DT 5                                             // Serial data pin
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B
#define LED_TYPE WS2812B                                       // What kind of strip are you using (APA102, WS2801 or WS@2812B
#define NUM_LEDS 30                                           // Number of LED's

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
#define BRIGHTNESS 255                                          // 


// 7 Segment display

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();            // attaches I2C

#define Wh_led 4                                            // attaches leds to pin 4

int rotary = 0;
int Wh_value = 0;

// rotary encoder

#include <Encoder.h>                                        //attaches to pin 2 and 3
#include <TimerOne.h>

// STEPPER MOTORS

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


void setup() {
  // Initiate serial communication
  Serial.begin(115200);
  
  //set analog inputs as inputs
  pinMode(sensor0, INPUT);
  pinMode(sensor1, INPUT);
  
  //attach leds
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2801 or APA102
  FastLED.setBrightness(BRIGHTNESS);

  //attach segment display
  matrix.begin(0x71); // added a jumper to change the default address
  pinMode(Wh_led, OUTPUT); //leds which show unit as output

  //rotary encoder
  encoder.Timer_init();

  //setup stepper
  AFMS.begin(); // Start the bottom shield
   
  stepper1.setMaxSpeed(1000); //maximum is 1420
  stepper1.setAcceleration(800); //not really a maximum
    
  stepper2.setMaxSpeed(50);
  stepper2.setAcceleration(30);
  
}


void loop() {
  // read the serial input from the max patch
  readIncoming();
  
  //show LED

    switch (led_state) {
      case 0:
        fill();
        break;
      case 1:
        sampleled2();
        break;
      case 2:
        sinelon(led_pos, led_hue);
        break;
      case 3:
        juggle();
        break;
      case 4:
        sampleled();
        break;
      case 5:
        confetti();
        break;
    }
//  sinelon(led_pos, led_hue);
  FastLED.show();
  
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
