/*
  Checks for Gamma RGBW functions
*/

void checkGAMMARGBW()

{

#ifdef __GAMMA_RGBW__

  /*
     RGB to RGBW with Gamma correction for 8-bit range

     oid xrgb2rgbwgamma8( uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w )
  */

  r = 0x99;
  g = 0x05;
  b = 0xf0;
  w = 0xAA;

  Serial.printf( "\n\nRGB to RGBW\nwith Gamma Correction\n\tfor: 0x%02x, 0x%02x, 0x%02x", r, g, b, w  );
  xrgb2rgbwgamma8( &r, &g , &b, &w );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x, 0x%02x", r, g, b, w );

#endif // __GAMMA_RGBW__

} // checkGAMMARGBW()
