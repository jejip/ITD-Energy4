//functions for the leds, different effects and patterns for different uses

/*
 *  main function
 *
 */

void showleds()
{
  //choose which led animation to show
  switch (led_state) {
      case 0:
        black();
        break;
      case 1:
        confetti(led_pos);
        break;
      case 2:
        trail(led_pos);
        break;
      case 3:
        ledset(rotary);
        break;
      case 4:
        juggle(); 
        break;
      case 5:
        fill_color(led_pos);
        break;
    }

  //if led state is changed, clear the leds for new animation
  if (led_state != led_state_last) { //poll for changes 
      FastLED.clear();
      led_state_last = led_state; //set the last state to the current state
  }

  //call FASTled to show animation
  FastLED.show();
}

/*
 *  LED patterns
 *
 */

void black() //fill all the leds with black
{
  fill_solid(leds, NUM_LEDS, CHSV(0,0,0));
}

void fill_color(int hue) //fill all the leds with a received colour
{
  fill_solid(leds, NUM_LEDS, CHSV(hue,255,100));
}

//random colored speckles that blink, with adjustable amount of colours
//TODO: make less speckles? slow down effect
void confetti(int pos) 
{
  fadeToBlackBy( leds, NUM_LEDS, 5);
  int pos2 = random16(NUM_LEDS);
  leds[pos2] += CHSV( 0 + random8(pos), 150, 200); //randomize the colour a bit
}


//move a coloured dots with a trail, with max input value
void trail(int pos) 
{
  pos = constrain(pos, 0, NUM_LEDS-1); //led_pos goes until 255, so constrain the value first
  fadeToBlackBy( leds, NUM_LEDS, 1);
  leds[pos] += CHSV(122, 255, 255); //same colour as the paint
}

//fill up the led strip from the top
void ledset(int rotary) { //show a fixed point with a trail
  int hue = 64; //which colour? 0-255
  int pos;
  
   pos = (rotary/10)-(rotary/40); //this keeps the last led at the top
   pos = constrain(pos, 0, NUM_LEDS-1); //keep it from overflowing
   
   fadeToBlackBy( leds, NUM_LEDS, 1);
   FastLED.clear();
   
   //a loop to show all the leds <= pos
   for (int i = 0; i <= pos; i++) {
    leds[i] += CHSV(hue,255,255); //add the last led to show 
   } 
}


//Back and forth filling up led strip with coloured dots
void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 80);
  byte dothue = 0;
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[beatsin8(i,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
