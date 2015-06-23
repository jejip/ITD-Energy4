
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
        stepper1_pos = map(value, num_identifiers, 255, 10, 255);
        //stepper1_pos = int(value);
        break;
      case 2:
        value = Serial.read();
        stepper1_speed = int(value);
        break;
      case 3:
        value = Serial.read();
        stepper2_enable = map(value, num_identifiers, num_identifiers+1, 0, 1); //10 is off and 11 is on
        stepper2_enable = constrain(stepper2_enable, 0, 1);
        break;
      case 4:
        value = Serial.read();
        stepper2_pos = map(value, num_identifiers, 255, 0, 200); //maximum position is 200 for opening / closing
        break;
      case 5:
        value = Serial.read();
        stepper2_speed = int(value);
        break;
      case 6:
        value = Serial.read();
        led_pos = map(value, num_identifiers, 255, 0, NUM_LEDS-1);
        break;
      case 7:
        value = Serial.read();
        led_speed = map(value, num_identifiers, 255, 0, 9999); //the display can only display 4 numbers
        //TO DO: how to make the transition between numbers smooth?
        break;
      case 8:
        value = Serial.read();
        led_hue = map(value, num_identifiers, 255, 0, 255);
        break;
      case 9:
        value = Serial.read();
        led_state = value - num_identifiers;
//        led_state = constrain(led_state, 0, 5); // constrain to 5 modes
        //led_state = int(value);
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
    sensorValue0 = analogRead(sensor0);
    sensorValue1 = analogRead(sensor1);

    // print to the maxpatch
    Serial.print(stepper1_pos);
    Serial.print(" ");
    Serial.print(stepper2_pos);
    Serial.print(" ");
    Serial.print(led_state);
    Serial.print(" ");
    Serial.print(stepper1_enable);
    Serial.print("\n");
    lastTimeSent = millis();
  }
}
