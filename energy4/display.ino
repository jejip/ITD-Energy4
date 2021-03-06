

void show_display(){
  //put the rotary value onto the display
  Wh_value = rotary*20;
//  Wh_value = rotary;
  Wh_value = constrain(Wh_value,0,8000);
  
    //Only turn on display and LEDS when the value to display is > 0
    if (Wh_value >= 0 && display_value == 11){
      //put values on the display
//      matrix.setBrightness(15); // set max brightness
      matrix.println(Wh_value);
      matrix.writeDisplay();
      
      //put LEDS for the unit on
      matrix2.drawBitmap(0, 0, W, 8, 8, LED_ON);
      matrix2.writeDisplay();
    }
    else{
      matrix.clear();
      matrix2.clear();
      matrix.writeDisplay();
      matrix2.writeDisplay();
    } 

    if (save_rotary == 12){ //when save rotary is called
      display_value_last = Wh_value;
    }
  
}
