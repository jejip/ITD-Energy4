
//Read incoming values (in bytes), the first byte is the identifier (0-9) second byte is value (10-255).
void readIncoming() {
  
  while ((Serial.available() > 1)){ //only read serial when 2 bytes are available
    
    incoming = Serial.read(); //read the first incoming byte
    
    switch (incoming) {
      case 0:
        value = Serial.read();
        stepper1_enable = map(value, num_identifiers, num_identifiers+1, 0, 1); //10 is off and 11 is on
        stepper1_enable = constrain(stepper1_enable, 0, 1);
        Serial.println(stepper1_enable);
        //stepper1_enable = int(value);
        break;
      case 1:
        value = Serial.read();
//        stepper1_pos = map(value, num_identifiers, 255, 10, 5000);
        stepper1_pos = int(value);
        break;
      case 2:
        value = Serial.read();
        stepper1_speed = map(value, num_identifiers, 255, 0, 250);
        break;
      case 3:
        value = Serial.read();
        stepper2_enable = map(value, num_identifiers, num_identifiers+1, 0, 1); //10 is off and 11 is on
        stepper2_enable = constrain(stepper2_enable, 0, 1);
        break;
      case 4:
        value = Serial.read();
        stepper2_pos = map(value, num_identifiers, 255, 0, 400); //maximum position is 200 for opening / closing
        break;
      case 5:
        value = Serial.read();
        stepper2_speed = int(value);
        break;
      case 6:
        value = Serial.read();
//        led_pos = map(value, num_identifiers, 255, 0, 255); //if we remap this value the position isn't shown accurately`
        led_pos = int(value);
        led_pos = led_pos - 10;
        break;
      case 7:
        value = Serial.read();
        led_state = value - num_identifiers;
        break;
      case 8:
        value = Serial.read();
        display_value = value;
        //display_value = map(value, num_identifiers, 255, 0, 9999); //the display can only display 4 numbers
        break;
      case 9:
        value = Serial.read();
        led_hue = map(value, num_identifiers, 255, 0, 255);
        break;
    }  
  }
}


//Send some values back to max, in ascii instead of bytes (because that worked fine)
void sendvalues() {
  // Let's send max 25 times per second
  if (millis() > (lastTimeSent + 40))
  {
    // read the value from the sensors:
    sensorValue0 = analogRead(sensor0); //distance
    sensorValue1 = analogRead(sensor1); //pot (radiator)
    sensorValue2 = analogRead(sensor2); //power plug (light)
    sensorValue3 = digitalRead(sensor3); // light switch

    // print to the maxpatch
    Serial.print(sensorValue0);
    Serial.print(" ");
    Serial.print(sensorValue1);
    Serial.print(" ");
    Serial.print(stepper2_pos);
    Serial.print(" ");
    Serial.print(led_state);
    Serial.print("\n");
    lastTimeSent = millis();
  }
}
