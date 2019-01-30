/*
  Checks for HSV Tests and HSV Luma-Reference functions
*/

#include "options.h"

uint8_t luma(byte R, byte G, byte B);


void checkHSV()
{

  // HSV Checks

#ifdef __HSV__

  /*
     HSV to RGB checks for S, E, W, T variants
  */
  h = 0x0280;
  s = 0x80;
  v = 0x80;

  Serial.printf( "\n\nHSV to RGB {Spectrum}\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgb8s( h,  s,  v, &r, &g , &b );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x", r, g, b );

  Serial.printf( "\n\nHSV to RGB {Efficient}\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgb8e( h,  s,  v, &r, &g , &b );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x", r, g, b );

  Serial.printf( "\n\nHSV to RGB {Wave}\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgb8w( h,  s,  v, &r, &g , &b );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x", r, g, b );

  Serial.printf( "\n\nHSV to RGB {Tweaked}\n\tfor: 0x%04x, 0x%02x, 0x%02x", h, s, v );
  xhsv2rgb8t( h,  s,  v, &r, &g , &b );
  Serial.printf( "\n\t is: 0x%02x, 0x%02x, 0x%02x", r, g, b );



  /*
     HSV Relative Lumanance correction table info

    Uncomment the lumanance function of your choice below

  */

  uint8_t sr, sg, sb, er, eg, eb, wr, wg, wb, tr, tg, tb;
  Serial.println("\n\nIndex\tHue  ==  Spectrum - Eficient - Sine Wave - Tweaked");
  Serial.println("Index\t     R\t\t\t     G\t\t\t     B\t\t\t     L");
  for ( uint16_t i = 0; i < 1535 ; i += 6 )
  {
    xhsv2rgb8s( i,  255,  255, &sr, &sg , &sb );
    xhsv2rgb8e( i,  255,  255, &er, &eg , &eb );
    xhsv2rgb8w( i,  255,  255, &wr, &wg , &wb );
    xhsv2rgb8t( i,  255,  255, &tr, &tg , &tb );
    Serial.printf("%03u\t%02x-%02x-%02x-%02x", i / 6, sr, er, wr, tr );
    Serial.printf("\t\t%02x-%02x-%02x-%02x", sg, eg, wg, tg );
    Serial.printf("\t\t%02x-%02x-%02x-%02x", sb, eb, wb, tb );
    Serial.printf("\t\t%02x-%02x-%02x-%02x\n", luma(sr, sg, sb), luma(er, eg, eb), luma(wr, wg, wb), luma(tr, tg, tb) );
  }

#endif // __HSV__

} // checkHSV()


// ============= Value Functions ==============

/*
  Luminance of given RGB
  Choice of three standards, uncomment your choice
*/
uint8_t luma(byte R, byte G, byte B)
{
  // return byte( ( 0.299 * R ) + ( 0.587 * G ) + ( 0.114 * B ) );    // ITU-R BT.601
  // return byte( ( 0.2126 * R ) + ( 0.7152 * G ) + ( 0.0722 * B ) ); //  ITU-R BT.709
  return byte( ( 0.212 * R ) + ( 0.701 * G ) + ( 0.087 * B ) );    //  SMPTE 240M
  return 0;
}
