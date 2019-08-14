void AP_drive(){
  if(!autopilot){
    return;
  }

  driveForward();
}

void AP_turn(){
  if(!autopilot){
    return;
  }

  turnRight();
}
