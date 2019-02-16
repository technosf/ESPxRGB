/*

*/

#include "ESPxRGB.h"

const unsigned long MAX_LONG = 4294967295;
const int STEPS = 1536;
const unsigned long ITERS = 6291456;
const float I = ITERS * 1000000;

uint8_t r, g, b;

unsigned long startts;
unsigned long endts;

void setup() {

  Serial.begin(115200);

  Serial.println("Benching HSV Conversions for 6291456 iterations");
  Serial.println("Impl\t\t\tTime ms\t\tCalls per Second");


  unsigned long elapsed;

  elapsed = benchHSV(1);
  Serial.printf("%-15s\t\t%8.2f\t%8.2f\n", "FastHSV", elapsed / 1000.0, I / elapsed);

  elapsed = benchHSV(2);
  Serial.printf("%-15s\t\t%8.2f\t%8.2f\n", "KKs Spectrum", elapsed / 1000.0, I / elapsed);

  elapsed = benchHSV(3);
  Serial.printf("%-15s\t%8.2f\t%8.2f\n", "ESPxRGB Spectrum", elapsed / 1000.0, I / elapsed);

  elapsed = benchHSV(4);
  Serial.printf("%-15s\t%8.2f\t%8.2f\n", "ESPxRGB Efficient", elapsed / 1000.0, I / elapsed);

  elapsed = benchHSV(5);
  Serial.printf("%-15s\t\t%8.2f\t%8.2f\n", "ESPxRGB Wave", elapsed / 1000.0, I / elapsed);

  elapsed = benchHSV(6);
  Serial.printf("%-15s\t\t%8.2f\t%8.2f\n", "ESPxRGB Tweak", elapsed / 1000.0, I / elapsed);

  Serial.println("\nDone");

}

void loop() {
  // Not used
}

unsigned long benchHSV(int clc)
{
  unsigned long acc = 0;

  for ( uint16_t h = 0; h < STEPS; h++ )
  {
    for ( int s = 0; s < 256; s++ )
    {
      switch (clc)
      {
        case 1:
          acc += fasthsv(h, s);
          break;
        case 2:
          acc += kkhsv(h, s);
          break;
        case 3:
          acc += hsvs(h, s);
          break;
        case 4:
          acc += hsve(h, s);
          break;
        case 5:
          acc += hsvw(h, s);
          break;
        case 6:
          acc += hsvt(h, s);
      }
    }
  }
  return acc;
}

unsigned long hsvs( uint16_t h, uint8_t s)
{
  startts = micros();
  xhsv2rgb8s(h, s, 0, &r, &g, &b);
  xhsv2rgb8s(h, s, 31, &r, &g, &b);
  xhsv2rgb8s(h, s, 32, &r, &g, &b);
  xhsv2rgb8s(h, s, 63, &r, &g, &b);
  xhsv2rgb8s(h, s, 64, &r, &g, &b);
  xhsv2rgb8s(h, s, 95, &r, &g, &b);
  xhsv2rgb8s(h, s, 96, &r, &g, &b);
  xhsv2rgb8s(h, s, 127, &r, &g, &b);
  xhsv2rgb8s(h, s, 128, &r, &g, &b);
  xhsv2rgb8s(h, s, 159, &r, &g, &b);
  xhsv2rgb8s(h, s, 160, &r, &g, &b);
  xhsv2rgb8s(h, s, 191, &r, &g, &b);
  xhsv2rgb8s(h, s, 192, &r, &g, &b);
  xhsv2rgb8s(h, s, 223, &r, &g, &b);
  xhsv2rgb8s(h, s, 224, &r, &g, &b);
  xhsv2rgb8s(h, s, 255, &r, &g, &b);
  endts = micros();
  if ( endts < startts ) return endts + ( MAX_LONG - startts );
  return endts - startts;
}

unsigned long hsve( uint16_t h, uint8_t s)
{
  startts = micros();
  xhsv2rgb8e(h, s, 0, &r, &g, &b);
  xhsv2rgb8e(h, s, 31, &r, &g, &b);
  xhsv2rgb8e(h, s, 32, &r, &g, &b);
  xhsv2rgb8e(h, s, 63, &r, &g, &b);
  xhsv2rgb8e(h, s, 64, &r, &g, &b);
  xhsv2rgb8e(h, s, 95, &r, &g, &b);
  xhsv2rgb8e(h, s, 96, &r, &g, &b);
  xhsv2rgb8e(h, s, 127, &r, &g, &b);
  xhsv2rgb8e(h, s, 128, &r, &g, &b);
  xhsv2rgb8e(h, s, 159, &r, &g, &b);
  xhsv2rgb8e(h, s, 160, &r, &g, &b);
  xhsv2rgb8e(h, s, 191, &r, &g, &b);
  xhsv2rgb8e(h, s, 192, &r, &g, &b);
  xhsv2rgb8e(h, s, 223, &r, &g, &b);
  xhsv2rgb8e(h, s, 224, &r, &g, &b);
  xhsv2rgb8e(h, s, 255, &r, &g, &b);
  endts = micros();
  if ( endts < startts ) return endts + ( MAX_LONG - startts );
  return endts - startts;
}

unsigned long hsvw( uint16_t h, uint8_t s)
{
  startts = micros();
  xhsv2rgb8w(h, s, 0, &r, &g, &b);
  xhsv2rgb8w(h, s, 31, &r, &g, &b);
  xhsv2rgb8w(h, s, 32, &r, &g, &b);
  xhsv2rgb8w(h, s, 63, &r, &g, &b);
  xhsv2rgb8w(h, s, 64, &r, &g, &b);
  xhsv2rgb8w(h, s, 95, &r, &g, &b);
  xhsv2rgb8w(h, s, 96, &r, &g, &b);
  xhsv2rgb8w(h, s, 127, &r, &g, &b);
  xhsv2rgb8w(h, s, 128, &r, &g, &b);
  xhsv2rgb8w(h, s, 159, &r, &g, &b);
  xhsv2rgb8w(h, s, 160, &r, &g, &b);
  xhsv2rgb8w(h, s, 191, &r, &g, &b);
  xhsv2rgb8w(h, s, 192, &r, &g, &b);
  xhsv2rgb8w(h, s, 223, &r, &g, &b);
  xhsv2rgb8w(h, s, 224, &r, &g, &b);
  xhsv2rgb8w(h, s, 255, &r, &g, &b);
  endts = micros();
  if ( endts < startts ) return endts + ( MAX_LONG - startts );
  return endts - startts;
}

unsigned long hsvt( uint16_t h,  unsigned int  s)
{
  startts = micros();
  xhsv2rgb8t(h, s, 0, &r, &g, &b);
  xhsv2rgb8t(h, s, 31, &r, &g, &b);
  xhsv2rgb8t(h, s, 32, &r, &g, &b);
  xhsv2rgb8t(h, s, 63, &r, &g, &b);
  xhsv2rgb8t(h, s, 64, &r, &g, &b);
  xhsv2rgb8t(h, s, 95, &r, &g, &b);
  xhsv2rgb8t(h, s, 96, &r, &g, &b);
  xhsv2rgb8t(h, s, 127, &r, &g, &b);
  xhsv2rgb8t(h, s, 128, &r, &g, &b);
  xhsv2rgb8t(h, s, 159, &r, &g, &b);
  xhsv2rgb8t(h, s, 160, &r, &g, &b);
  xhsv2rgb8t(h, s, 191, &r, &g, &b);
  xhsv2rgb8t(h, s, 192, &r, &g, &b);
  xhsv2rgb8t(h, s, 223, &r, &g, &b);
  xhsv2rgb8t(h, s, 224, &r, &g, &b);
  xhsv2rgb8t(h, s, 255, &r, &g, &b);
  endts = micros();
  if ( endts < startts ) return endts + ( MAX_LONG - startts );
  return endts - startts;
}

unsigned long fasthsv( uint16_t h, uint8_t s)
{
  startts = micros();
  fast_hsv2rgb(h, s, 0, &r, &g, &b);
  fast_hsv2rgb(h, s, 31, &r, &g, &b);
  fast_hsv2rgb(h, s, 32, &r, &g, &b);
  fast_hsv2rgb(h, s, 63, &r, &g, &b);
  fast_hsv2rgb(h, s, 64, &r, &g, &b);
  fast_hsv2rgb(h, s, 95, &r, &g, &b);
  fast_hsv2rgb(h, s, 96, &r, &g, &b);
  fast_hsv2rgb(h, s, 127, &r, &g, &b);
  fast_hsv2rgb(h, s, 128, &r, &g, &b);
  fast_hsv2rgb(h, s, 159, &r, &g, &b);
  fast_hsv2rgb(h, s, 160, &r, &g, &b);
  fast_hsv2rgb(h, s, 191, &r, &g, &b);
  fast_hsv2rgb(h, s, 192, &r, &g, &b);
  fast_hsv2rgb(h, s, 223, &r, &g, &b);
  fast_hsv2rgb(h, s, 224, &r, &g, &b);
  fast_hsv2rgb(h, s, 255, &r, &g, &b);
  endts = micros();
  if ( endts < startts ) return endts + ( MAX_LONG - startts );
  return endts - startts;
}

unsigned long kkhsv( uint16_t h, uint8_t s)
{
  startts = micros();
  getKKRGB(h, s, 0, &r, &g, &b);
  getKKRGB(h, s, 31, &r, &g, &b);
  getKKRGB(h, s, 32, &r, &g, &b);
  getKKRGB(h, s, 63, &r, &g, &b);
  getKKRGB(h, s, 64, &r, &g, &b);
  getKKRGB(h, s, 95, &r, &g, &b);
  getKKRGB(h, s, 96, &r, &g, &b);
  getKKRGB(h, s, 127, &r, &g, &b);
  getKKRGB(h, s, 128, &r, &g, &b);
  getKKRGB(h, s, 159, &r, &g, &b);
  getKKRGB(h, s, 160, &r, &g, &b);
  getKKRGB(h, s, 191, &r, &g, &b);
  getKKRGB(h, s, 192, &r, &g, &b);
  getKKRGB(h, s, 223, &r, &g, &b);
  getKKRGB(h, s, 224, &r, &g, &b);
  getKKRGB(h, s, 255, &r, &g, &b);
  endts = micros();
  if ( endts < startts ) return endts + ( MAX_LONG - startts );
  return endts - startts;
}
