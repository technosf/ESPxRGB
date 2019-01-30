/*
   Checks for RGBW functions
*/

void checkRGBW()
{

#ifdef __RGBW__

  /*
     RGB to RGBW conversion on 8-bit range

    xrgb2rgbw8( uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w );   // Done
  */

  r = 0x99;
  g = 0x05;
  b = 0xf0;
  w = 0xAA;

  Serial.printf( "\n\nRGB to RGBW\n\tfor: 0x%02x, 0x%02x, 0x%02x, 0x%02x", r, g, b, w );
  xrgb2rgbw8( &r, &g , &b, &w );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x, 0x%02x", r, g, b, w );

#endif // __RGBW__

} // checkRGBW()
