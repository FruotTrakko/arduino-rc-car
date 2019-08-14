void stopDriving(){
  dontCount = true;
  digitalWrite(LForward, LOW);
  digitalWrite(LBackward, LOW);
  digitalWrite(RForward, LOW);
  digitalWrite(RBackward, LOW);

  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}

void driveForward(){
  dontCount = false;
  digitalWrite(LForward, HIGH);
  digitalWrite(LBackward, LOW);
  digitalWrite(RForward, HIGH);
  digitalWrite(RBackward, LOW);

  analogWrite(motorLeft, motorSpeedLeft);
  analogWrite(motorRight, motorSpeedRight);
}

void turnRight(){
  dontCount = true;
  digitalWrite(LForward, HIGH);
  digitalWrite(LBackward, LOW);
  digitalWrite(RForward, LOW);
  digitalWrite(RBackward, LOW);

  analogWrite(motorLeft, motorSpeedLeft);
  analogWrite(motorRight, 0);
}

void turnLeft(){
  dontCount = true;
  digitalWrite(LForward, LOW);
  digitalWrite(LBackward, LOW);
  digitalWrite(RForward, HIGH);
  digitalWrite(RBackward, LOW);

  analogWrite(motorLeft, 0);
  analogWrite(motorRight, motorSpeedRight);
}

void driveBackward(){
  dontCount = false;
  digitalWrite(LForward, LOW);
  digitalWrite(LBackward, HIGH);
  digitalWrite(RForward, LOW);
  digitalWrite(RBackward, HIGH);

  analogWrite(motorLeft, motorSpeedLeft);
  analogWrite(motorRight, motorSpeedRight);
}
