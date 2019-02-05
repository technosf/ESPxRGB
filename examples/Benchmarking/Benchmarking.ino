/*

*/

#include "ESPxRGB.h"      // Library definition header

const int STEPS = 1536;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // Not used
}

void benchHSV()
{
  unsigned long startts [STEPS];
  unsigned long endts [STEPS];
  unsigned int  r, g, b;

  for ( int h = 0; h < STEPS; h++ )
  {
    startts = micros();
    xhsv2rgb(h,32,32,r,g,b);
    xhsv2rgb(h,32,64,r,g,b);
    xhsv2rgb(h,32,96,r,g,b);
    xhsv2rgb(h,32,128,r,g,b);
    xhsv2rgb(h,32,160,r,g,b);
    xhsv2rgb(h,32,192,r,g,b);
    xhsv2rgb(h,32,224,r,g,b);
    xhsv2rgb(h,32,255,r,g,b);
    endts = micros();
  }
  
  
}
