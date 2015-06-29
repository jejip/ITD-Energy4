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
        fill_color(led_pos);
        break;
      case 2:
        sinelon(led_pos);
        break;
      case 3:
        ledset(rotary);
        break;
      case 4:
        juggle(); //it needs to show this in order to show other animations?
        break;
      case 5:
        confetti(led_pos);
        break;
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

void fill_color(int hue) //fill all the leds with black
{
  fill_solid(leds, NUM_LEDS, CHSV(hue,255,100));
}

void circular()
{
  fadeToBlackBy( leds, NUM_LEDS, 1);
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] += CHSV(120,255,255);
    if (i == NUM_LEDS) i = 0;
  }
}


void sinelon(int pos) //move a coloured dots with a trail, with max input value
{
  pos = constrain(pos, 0, NUM_LEDS-1); //led_pos goes until 255, so constrain the value first
  fadeToBlackBy( leds, NUM_LEDS, 1);
  leds[pos] += CHSV(120, 255, 255);
}


void ledset(int rotary) { //show a fixed point with a trail
  //rotary = constrain(rotary, 0, NUM_LEDS-1); //led_pos goes until 255, so constrain the value first

  int hue = 100; //which colour? 0-255
  int pos; //which position is the handle? 0-23
  
  //FastLED.clear();
//  leds[pos] = CHSV(hue,255,255);
//  leds[pos+1] = CHSV(hue,255,200);
//  leds[pos+2] = CHSV(hue,255,150);
//  leds[pos+3] = CHSV(hue,255,105);
//  leds[pos+4] = CHSV(hue,255,55);
//  leds[pos+5] = CHSV(hue,255,30);
//  leds[pos+6] = CHSV(hue,255,10);
   fadeToBlackBy( leds, NUM_LEDS, 1);
   pos = (rotary/10)-(rotary/40);
   leds[pos] += CHSV(hue,255,255);

}


void confetti(int pos) 
{
  // random colored speckles that blink
  fadeToBlackBy( leds, NUM_LEDS, 5);
  int pos2 = random16(NUM_LEDS);
  leds[pos2] += CHSV( 0 + random8(pos), 200, 255); //randomize the colour a bit
}


//Back and forth filling up led strip
void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 80);
  byte dothue = 0;
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[beatsin8(i,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}


void sampleled()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  int pos = beatsin16(13,0,NUM_LEDS); //back and forth sine wave
  leds[pos] += CHSV( 100, 255, 192);
}

void sampleled2()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  int pos = beat8(120); //back and forth sine wave
  leds[2] += CHSV( 100, 255, pos);
}



//void bpm() //slow coloured sprinkles
//{
//  uint8_t BeatsPerMinute = 12;
//  CRGBPalette16 palette = PartyColors_p;
//  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
//  for( int i = 0; i < NUM_LEDS; i++) { //9948
//    leds[i] = ColorFromPalette(palette, 255, 255);
//  }
//}
