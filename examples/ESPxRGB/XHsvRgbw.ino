/*
  Checks for HSV RGBW functions
*/

void checkHSVRGBW()

{

#ifdef __HSV_RGBW__

  /*
     HSV to RGBW checks for default HSV variant
  */
  h = 0x0280;
  s = 0x80;
  v = 0x80;

  Serial.printf( "\n\nHSV to RGB {Spectrum}\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgb8( h,  s,  v, &r, &g , &b );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x", r, g, b );

#endif // __HSV_RGBW__

} // checkHSVRGBW()
