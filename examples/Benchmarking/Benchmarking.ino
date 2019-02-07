/*

*/

#include "ESPxRGB.h"

const int STEPS = 1536;

uint8_t r, g, b;

unsigned long startts;
unsigned long endts;

void setup() {

  Serial.begin(115200);

  Serial.println("Benching HSV Conversions");

  benchHSV();

}

void loop() {
  // Not used
}

void benchHSV()
{

  unsigned long spec, eff, wave, tweak, fasth, kk;
  float iters, i;
  uint8_t s;

  for ( uint16_t h = 0; h < STEPS; h++ )
  {
    Serial.printf("\nh:%u", h);
    for ( int s = 0; s < 256; s++ )
    {
      fasth += fasthsv(h, s);
      kk += kkhsv(h, s);
      spec += hsvs(h, s);
      eff += hsve(h, s);
      wave += hsvw(h, s);
      tweak += hsvt(h, s);

      iters += 16;
    }
  }
  i = 1000 * iters;

  Serial.printf( "\n\nComputations over %u Iterations\n\t\tFastHSV Spectrum\tKKs Spectrum\tESPxRGB Spectrum\tEficient\tWave\tTweaked\tAverage\n\n", iters );
  Serial.printf( "Total Time\t\t%lu\t\t%lu\t\t%lu\t\t%lu\t%lu\t%lu\t%lu\n", fasth , kk, spec, eff , wave, tweak, (fasth+kk+spec+eff+wave+tweak)/6 );
  Serial.printf( "Comps per Sec\t%f\t\t%f\t\t%f\t\t%f\t%f\t%f\n", fasth , kk, spec, eff , wave, tweak );
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
  return endts - startts;
}
