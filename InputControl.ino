//used to store the last recieved code
unsigned long lastCode;

/*
 * MISSING
 */
void decodeAction(unsigned long value){
  //check for same code (default: 0xFFFFFFFF)
  if(value == sameCode){
    #if DEBUG_OUT_INPUT
      Serial.println("Recieved same code");
    #endif
    decodeAction(lastCode);
    return;
  //check for autopilot enable/disable code
  }else if(value == autopilotCode || value == autopilotCode2){
    autopilot = !autopilot;
    if(!autopilot){
      stopDriving();
    }
    #if ENABLE_AUTOPILOT_INFO
      if(autopilot){
        digitalWrite(autopilotInfoLEDPin, HIGH);
      }else{
        digitalWrite(autopilotInfoLEDPin, LOW);
      }
    #endif
    #if DEBUG_OUT_INPUT
      Serial.print("Set autopilot to: ");
      Serial.println(autopilot);
    #endif
  //check for forward code
  }else if(value == forwardCode || value == forwardCode2){
    #if DEBUG_OUT_INPUT
      Serial.println("Forward");
    #endif
    driveBackwards = false;
    driveForward();
  //check for stop code
  }else if(value == stopCode || value == stopCode2){
    #if DEBUG_OUT_INPUT
      Serial.println("Stop");
    #endif
    driveBackwards = false;
    stopDriving();
  //check for left code
  }else if(value == leftCode || value == leftCode2){
    #if DEBUG_OUT_INPUT
      Serial.println("Left");
    #endif
    driveBackwards = false;
    turnLeft();
  //check for right code
  }else if(value == rightCode || value == rightCode2){
    #if DEBUG_OUT_INPUT
      Serial.println("Right");
    #endif
    driveBackwards = false;
    turnRight();
  //check for backward code
  }else if(value == backwardCode || value == backwardCode2){
    #if DEBUG_OUT_INPUT
      Serial.println("Backward");
    #endif
    driveBackwards = true;
    driveBackward();
  }
  //set last code to current code value
  lastCode = value;
  #if DEBUG_OUT_INPUT
    Serial.print("Set last code: ");
    Serial.println(lastCode, HEX);
  #endif
}
