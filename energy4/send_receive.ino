
//Read incoming values (in bytes), the first byte is the identifier (0-9) second byte is value (10-255).
void readIncoming() {
  
  byte incoming = 0;
  byte value = 0;
  
  while ((Serial.available() > 1)){ //only read serial when 2 bytes are available
    
    incoming = Serial.read(); //read the first incoming byte
    
    switch (incoming) {
      case 0:
        value = Serial.read();
        led = int(value);
        break;
      case 1:
        value = Serial.read();
        stepper = int(value);
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
