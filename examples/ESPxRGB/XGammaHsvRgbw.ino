/*
  Checks for Gamma HSV RGBW functions
*/

void checkGAMMAHSVRGBW()
{

#ifdef __GAMMA_HSV_RGBW__

  /*
     HSV to RGB/RGBW conversion with Gamma correction for 8-bit range
  */

  h = 0x0280;
  s = 0x80;
  v = 0x80;

  Serial.printf( "\n\nHSV to RGB\nwith Gamma Correction\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgbgamma8( h,  s,  v, &r, &g, &b );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x", r, g, b );

  h = 0x0280;
  s = 0x80;
  v = 0x80;

  Serial.printf( "\n\nHSV to RGBW\nwith Gamma Correction\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgbwgamma8( h,  s,  v, &r, &g, &b, &w );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x, 0x%02x", r, g, b, w );

#endif // __GAMMA_HSV_RGBW__

} // checkGAMMAHSVRGBW()
