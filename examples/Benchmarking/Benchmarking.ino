/*

*/

#include "ESPxRGB.h"      

const int STEPS = 1536;

  unsigned int  r, g, b;

  unsigned long startts;
  unsigned long endts;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // Not used
}

void benchHSV()
{
  unsigned long spec, eff, wave, tweak, fasth, kk;
  int iters, i;

  for ( int h = 0; h < STEPS; h++ )
  {
  for ( int s = 0; s < 256; s+=32 )
  {
    fsth += fasthsv(h,s);
    kk += kkhsv(h,s);
    spec += hsvs(h,s);
    eff += hsve(h,s);
    wave += hsvw(h,s);
    tweak += hsvt(h,s);
    
    iters += 10;
  }
  }
  i = 1000 * iters;
  Serial.begin(115200);
  Serial.println("Computations Per Second\nFastHSV Spectrum\tKKs Spectrum\tESPxRGB Spectrum\tEficient\tWave\Tweaked");
  Serial.printf("%u\t%u\t%u\t%u\t%u\t%u", fsth/i, kk/i, spec/i, eff/i, wave/i, tweak/i);
}

unsigned long hsvs(
  unsigned int  h,
  unsigned int  s)
{
    startts = micros();
    xhsv2rgbs(h,s,0,r,g,b);
    xhsv2rgbs(h,s,31,r,g,b);
    xhsv2rgbs(h,s,63,r,g,b);
    xhsv2rgbs(h,s,95,r,g,b);
    xhsv2rgbs(h,s,127,r,g,b);
    xhsv2rgbs(h,s,128,r,g,b);
    xhsv2rgbs(h,s,159,r,g,b);
    xhsv2rgbs(h,s,191,r,g,b);
    xhsv2rgbs(h,s,223,r,g,b);
    xhsv2rgbs(h,s,255,r,g,b);
    endts = micros();

    return endts - startts;
}
unsigned long hsve(
  unsigned int  h,
  unsigned int  s)
{
    startts = micros();
    xhsv2rgbe(h,s,0,r,g,b);
    xhsv2rgbe(h,s,31,r,g,b);
    xhsv2rgbe(h,s,63,r,g,b);
    xhsv2rgbe(h,s,95,r,g,b);
    xhsv2rgbe(h,s,127,r,g,b);
    xhsv2rgbe(h,s,128,r,g,b);
    xhsv2rgbe(h,s,159,r,g,b);
    xhsv2rgbe(h,s,191,r,g,b);
    xhsv2rgbe(h,s,223,r,g,b);
    xhsv2rgbe(h,s,255,r,g,b);
    endts = micros();
    return endts - startts;
}
unsigned long hsvw(
  unsigned int  h,
  unsigned int  s)
{
    startts = micros();
    xhsv2rgbw(h,s,0,r,g,b);
    xhsv2rgbw(h,s,31,r,g,b);
    xhsv2rgbw(h,s,63,r,g,b);
    xhsv2rgbw(h,s,95,r,g,b);
    xhsv2rgbw(h,s,127,r,g,b);
    xhsv2rgbw(h,s,128,r,g,b);
    xhsv2rgbw(h,s,159,r,g,b);
    xhsv2rgbw(h,s,191,r,g,b);
    xhsv2rgbw(h,s,223,r,g,b);
    xhsv2rgbw(h,s,255,r,g,b);
    endts = micros();
    return endts - startts;
}
unsigned long hsvt(
  unsigned int  h,
  unsigned int  s)
{
    startts = micros();
    xhsv2rgbt(h,s,0,r,g,b);
    xhsv2rgbt(h,s,31,r,g,b);
    xhsv2rgbt(h,s,63,r,g,b);
    xhsv2rgbt(h,s,95,r,g,b);
    xhsv2rgbt(h,s,127,r,g,b);
    xhsv2rgbt(h,s,128,r,g,b);
    xhsv2rgbt(h,s,159,r,g,b);
    xhsv2rgbt(h,s,191,r,g,b);
    xhsv2rgbt(h,s,223,r,g,b);
    xhsv2rgbt(h,s,255,r,g,b);
    endts = micros();
    return endts - startts;
}


