//functions for the leds, different effects and patterns for different uses


//move a coloured dots with a trail
void sinelon(int pos, int hue)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  leds[pos] += CHSV(hue, 255, 255);
}

void sine2(int pos)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 1);
  leds[pos] += CHSV(0, 255, 255);
}

//show quick flashes of a colour
//void confetti() 
//{
//  // random colored speckles that blink
//  fadeToBlackBy( leds, NUM_LEDS, 5);
//  int pos = random16(NUM_LEDS);
//  leds[pos] += CHSV( gHue + random8(64), 200, 255); //randomize the colour a bit
//}

//slow coloured sprinkles
//void bpm()
//{
//  uint8_t BeatsPerMinute = 12;
//  CRGBPalette16 palette = PartyColors_p;
//  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
//  for( int i = 0; i < NUM_LEDS; i++) { //9948
//    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
//  }
//}

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
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( 100, 255, 192);
}



//void noise16() {
//  fill_noise16(leds, NUM_LEDS, octaves, x, xscale, hue_octaves, hxy, hue_scale, hue_time);
//  if (thisdir == 0) {hxy+=hxyinc; x += x_speed; hue_time+= hue_speed;} else { hxy-=hxyinc; x -= x_speed; hue_time -= hue_speed;}
//} // nois16()
//
//
//void pop_fade() {
//  unsigned long thiscolour;
//  if (ranamount >NUM_LEDS) ranamount = NUM_LEDS;               // Make sure we're at least utilizing ALL the LED's.
//  int idex = random16(0, ranamount);
//
//  if (idex < NUM_LEDS) {                                      // Only the lowest probability twinkles will do.
//    boolcolours ? thiscolour = random(0, 0xffffff) : thiscolour =  colours[random16(0, numcolours)];     
//    int barlen = random16(1,maxbar);
//    for (int i = 0; i <barlen; i++) 
//      if (idex+i < NUM_LEDS) leds[idex+i] = thiscolour;       // Make sure we don't overshoot the array.
//  }
//  for (int i = 0; i <NUM_LEDS; i++) leds[i].nscale8(fadeval); // Go through the array and reduce each RGB value by a percentage.
//} // pop_fade()
