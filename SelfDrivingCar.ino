/*
 * TODO:
 * #Comment InputControl
 * #Comment Code in MotorControl
 * #Comment Code in AutopilotControl
 */

#include <IRremote.h>

//change for debug output
#define DEBUG_OUT false
#define DEBUG_OUT_INPUT (false && DEBUG_OUT)
#define DEBUG_OUT_SENSOR (false && DEBUG_OUT)
#define DEBUG_OUT_TWEAK (false && DEBUG_OUT)

//numeric constant values
#define stopDistance 30

//define information for a LED to display the status of the autopilot
#define ENABLE_AUTOPILOT_INFO true
#define autopilotInfoLEDPin 13

//define pin for infrared sensor
#define recieverPin 4

//define codes for infrared sensor remote
#define forwardCode 0xFF18E7
#define forwardCode2 0x3D9AE3F7
#define backwardCode 0xFF4AB5
#define backwardCode2 0x1BC0157B
#define leftCode 0xFF10EF
#define leftCode2 0x8C22657B
#define rightCode 0xFF5AA5
#define rightCode2 0x449E79F
#define stopCode 0xFF38C7
#define stopCode2 0x488F3CBB
#define autopilotCode 0xFFA25D
#define autopilotCode2 0xE318261B
#define sameCode 0xFFFFFFFF

//define pins for ultrasonic sensor
#define triggerPin 12
#define echoPin 11

//defien motor pins from 5 - 10
#define motorLeft 5
#define motorRight 10
#define LForward 6
#define LBackward 7
#define RForward 8
#define RBackward 9

#define lightresistor1 2 //LEFT
#define lightresistor2 3 //RIGHT

boolean autopilot = false;
IRrecv IRreciever(recieverPin);
decode_results results;

boolean driveBackwards = false;
int motorSpeedLeft = 252;  //144
int motorSpeedRight = 248 ; //126

boolean dontCount = false;

volatile int count1 = 0;
volatile int count2 = 0;

void setup() {
  #if DEBUG_OUT
    Serial.begin(38400);
  #endif
  
  for(int i = 5; i <= 10; i++){
    pinMode(i, OUTPUT);
  }

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(lightresistor1), ISR_Lichtschranke1, RISING);
  attachInterrupt(digitalPinToInterrupt(lightresistor2), ISR_Lichtschranke2, RISING);
  
  IRreciever.enableIRIn();

  #if ENABLE_AUTOPILOT_INFO
    pinMode(autopilotInfoLEDPin, OUTPUT);
  #endif
}

void loop(){
  evaluateSensor();

  //tweakValues();
  
  evaluateInput();
}

//========================================================================================

void outputTweakingValues(){
  if(millis() % 1000 < 50){
    Serial.print("Left: ");
    Serial.print(count1);
    Serial.print("rot ");
    Serial.print(motorSpeedLeft);
    Serial.print(" speed units | Right: ");
    Serial.print(count2);
    Serial.print("rot ");
    Serial.print(motorSpeedRight);
    Serial.println(" speed units");
  }
}

void evaluateSensor(){
  if(driveBackwards){
    return;
  }
  
  if(frontBlocked()){
    stopDriving();

    AP_turn();
  } else {
    AP_drive();
  }
}

void tweakValues(){
  #if DEBUG_OUT_TWEAK
    outputTweakingValues();
  #endif
  if(count1 + 5 > count2 && count1 - 5 < count2){
    if(count1 > 100){
      count1 = 0;
      count2 = 0;
    }
    return;
  } else {
    //Tweak Values
    if(count1 == count2){
      return;
    }
    //if left wheel turns faster than right wheel
    if(count1 > count2){
      if(motorSpeedRight != 255){
        motorSpeedRight++;
      } else {
        motorSpeedLeft--;
      }

    //if right wheel turns faster than left wheel
    } else {
      if(motorSpeedLeft != 255){
        motorSpeedLeft++;
      } else {
        motorSpeedRight--;
      }
    }

    count1 = 0;
    count2 = 0;
  }
}

void evaluateInput() {
  if(IRreciever.decode(&results)){
    #if DEBUG_OUT
      Serial.println(results.value, HEX);
    #endif
    decodeAction(results.value);
    IRreciever.resume();
  }
}
