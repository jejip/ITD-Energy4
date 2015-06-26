

void show_display(){
  //put the rotary value onto the display
  Wh_value = rotary*20;
  Wh_value = constrain(Wh_value,0,8000);
  
    //Only turn on display and LEDS when the value to display is > 0
    if (Wh_value > 0 && display_value == 11){
      //put values on the display
      matrix.setBrightness(15); // set max brightness
      matrix.println(Wh_value);
      matrix.writeDisplay();
      
      //put LEDS for the unit on
      digitalWrite(Wh_led, HIGH);
    }
    else{
      matrix.setBrightness(0); //set brightness to 0 to turn brightness off
      matrix.println(0);
      matrix.writeDisplay();
      digitalWrite(Wh_led, LOW);
    } 
  
}
