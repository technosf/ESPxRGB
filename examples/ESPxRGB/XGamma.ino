/*
  Checks for Gamma functions
*/

void checkGAMMA()
{

#ifdef __GAMMA__

  /*
    Gamma correction on an 8-bit range

    uint8_t xgamma8( uint8_t val );
  */

  Serial.printf( "\n\nGamma\n\tfor: %02x\n\t is: %02x", 0x99, xgamma8(0x99) );

  /*
      Gamma correction over an array of 8-bit values

      void xgammaarray8( uint8_t *pntr, uint8_t count );
  */

  uint8_t ga []  = { 0x99, 0x05, 0xf0, 0x25, 0x10, 0xff };
  Serial.printf( "\n\nGamma Array\n\tfor: 0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x", *ga, *(ga + 1), *(ga + 2), *(ga + 3), *(ga + 4), *(ga + 5) );
  xgammaarray8( ga, 0x5 );
  Serial.printf( "\n\t is: 0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x", *ga, *(ga + 1), *(ga + 2), *(ga + 3), *(ga + 4), *(ga + 5) );


  /*
    Gamma correct on RGB/W in 8-bit range

    void xrgbgamma8( uint8_t *r, uint8_t *g , uint8_t *b );
    void xrgbwgamma8( uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w );
  */

  r = 0x99;
  g = 0x05;
  b = 0xf0;

  Serial.printf( "\n\nGamma RGB\n\tfor: %02x, %02x, %02x", r, g, b );
  xrgbgamma8( &r, &g , &b );
  Serial.printf( "\n\t is: %02x, %02x, %02x", r, g, b);

  r = 0x99;
  g = 0x05;
  b = 0xf0;
  w = 0xAA;

  Serial.printf( "\n\nGamma RGBW\n\tfor: 0x%02x, 0x%02x, 0x%02x", r, g, b );
  xrgbwgamma8( &r, &g , &b, &w );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x, 0x%02x", r, g, b, w );


#endif // __GAMMA__

} //checkGAMMA()
