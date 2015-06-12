
//Read incoming values (in bytes), the first byte is the identifier (0-9) second byte is value (10-255).
void readIncoming() {
  
  byte incoming = 0;
  byte value = 0;
  
  while ((Serial.available() > 1)){ //only read serial when 2 bytes are available
    
    incoming = Serial.read(); //read the first incoming byte
    
    switch (incoming) {
      case 0:
        value = Serial.read();
        stepper1_enable = map(value, 10, 11, 0, 1); //10 is off and 11 is on
        Serial.println(stepper1_enable);
        //stepper1_enable = int(value);
      case 1:
        value = Serial.read();
        stepper1_pos = map(value, 10, 255, 0, 500);
        //stepper1_pos = int(value);
        break;
      case 2:
        value = Serial.read();
        stepper1_speed = int(value);
      case 3:
        value = Serial.read();
        stepper2_enable = int(value);
      case 4:
        value = Serial.read();
        stepper2_pos = int(value);
      case 5:
        value = Serial.read();
        stepper2_speed = int(value);
      case 6:
        value = Serial.read();
        led_pos = map(value, 10, 255, 0, 30);
      case 7:
        value = Serial.read();
        led_speed = int(value);
      case 8:
        value = Serial.read();
        led_hue = map(value, 10, 255, 0, 255);
      case 9:
        value = Serial.read();
        led_state = int(value);
    }  
  }
}


//Send some values back to max, in ascii instead of bytes (because that worked fine)
void sendvalues() {
  // Let's send max 25 times per second
  if (millis() > (lastTimeSent + 40))
  {
    // read the value from the sensors:
    sensorValue0 = analogRead(sensor0);
    sensorValue1 = analogRead(sensor1);

    // print to the maxpatch
    Serial.print(sensorValue0);
    Serial.print(" ");
    Serial.print(sensorValue1);
    Serial.print("\n");
    lastTimeSent = millis();
  }
}
