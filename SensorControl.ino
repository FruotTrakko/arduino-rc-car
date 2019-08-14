/* Checks if the distance between front ultrasonic sensor and the next obstacle
 * Returns true if the messured distance is lower than the predefind value 'stopDistance'
*/ 
boolean frontBlocked(){
  digitalWrite(triggerPin, LOW);
  delay(5);
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);
  long responseTime = pulseIn(echoPin, HIGH);
  long distance = (responseTime/2) * 0.03432;
  #if DEBUG_OUT_SENSOR
    Serial.print("Front distance: ");
    Serial.print(distance);
    Serial.print(" cm ; Distance to stop: ");
    Serial.print(stopDistance);
    Serial.println(" cm");
  #endif
  return distance < stopDistance;
}

void ISR_Lichtschranke1(){
  if(dontCount){
    return;
  }
  count1++;
}

void ISR_Lichtschranke2(){
  if(dontCount){
    return;
  }
  count2++;
}
