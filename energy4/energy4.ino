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
bool stepper1_enable = 0;
int stepper1_pos = 0;
int stepper1_speed = 0;

bool stepper2_enable = 0;
int stepper2_pos = 0;
int stepper2_speed = 0;

int led_pos = 0;
int led_speed = 0;
int led_hue = 0;
int led_bri = 0;

// LEDS

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

#define LED_DT 3                                             // Serial data pin
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B
#define LED_TYPE WS2812B                                       // What kind of strip are you using (APA102, WS2801 or WS@2812B
#define NUM_LEDS 30                                           // Number of LED's

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
#define BRIGHTNESS 150                                          // 

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

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP or INTERLEAVE!
// wrappers for the motor!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, DOUBLE);
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

  //setup stepper
  AFMS.begin(); // Start the bottom shield
   
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(500);
    
  stepper2.setMaxSpeed(100);
  stepper2.setAcceleration(300);
  
}



void loop() {
  // read the serial input from the max patch
  readIncoming();
  
  //show LED
  sinelon(led);
  FastLED.show();

  //move stepper
  if (stepper1.distanceToGo() == 0)
    {
      stepper1.moveTo(stepper);
    }
  stepper1.run();
  
  if (stepper2.distanceToGo() == 0)
    {
      stepper2.moveTo(stepper);
    }
  stepper2.run();
  
  //Send values from the analog inputs back
  //sendvalues();

}
