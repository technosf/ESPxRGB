/*

  Generators for Lookup tables used in ESPxRGB

*/

byte _slice(double angle);

// =========== Lookup Table Generators =============

/*
 * Gamma correction generator
 */
void genGamma( float gammacorrection, unsigned int inMax, unsigned int outMax, unsigned int * garray )
{
  *garray++ = 0;
  unsigned int x;
  for ( float i = 1.0; i < inMax; i++ )
  {
    x =  ( pow( i / inMax, gammacorrection ) * outMax ) + 0.5 ;
    //x = pow( 2.0, ( i + 64 ) / 41 ) - 1;
    *garray++ = x;
  }
}

/*
 * Quarter Sine Wave generator
 */
void genWave()
{
  Serial.println("\nESPxRGB\nQuarter Wave Lookup ASM data\n");

  for (int i = 0; i < 256; i += 16)
  {
    Serial.printf("\n.word");
    boolean comma = false;
    for (int j = i; j < i + 16; j += 4 )
    {
      if ( comma ) Serial.printf(",");
      comma = true;
      Serial.printf(" 0x%02x%02x%02x%02x", _slice(j+3), _slice(j+2), _slice(j+1), _slice(j));
    }
  }
  Serial.println();
}

byte _slice(double angle)
{
  const double XPI  = 3.141592653589793238463;
  const double incr  = XPI / 512;    // (PI/2)/256
  const double offset  = 3 * XPI / 2;    
  
  
  return 128*(sin(offset + (angle*incr))+1);
}

// ============= Table Checkers =============

#ifdef __GAMMA_CHECK_SKETCH__

/*
  Check the Gamma function against the values from the sketch generated table
*/
void checkGamma( int entries, unsigned int gammaArray [] )
{
  int errors = 0;

  Serial.println("\n\nGamma Check ASM data");

  for ( unsigned int i = 0; i < entries; i++ )
  {
    if ( gammaArray[i] != xgamma8(i) )
    {
      errors++;
      Serial.printf( "Gamma error index:%u  Expected: %02x  Got: %02x\n", i, gammaArray[i], xgamma8(i) );
    }
  }

  if ( errors = 0 )
  {
    Serial.println("Gamma Lookup ASM data OK!");
  }
  else
  {
    Serial.printf("Gamma Lookup ASM data for %u errors out of %u entries.\n", errors, entries );
  }
} // checkGamma


/*
  Calculate the gamma tabe and copmare to the one deployed in the library
*/
void genGammaTable()
{
  Serial.println("\nESPxRGB\n\nGamma Lookup ASM data\n");

  unsigned int ledRange = 256;
  unsigned int horizwords = 16;
  unsigned int gammaArray [ledRange];
  calGamma( GAMMA_CORRECTION, ledRange, ledRange, gammaArray );

  for (int i = 0; i < ledRange; i += horizwords)
  {
    Serial.printf("\n.word");
    boolean comma = false;
    for (int j = i; j < i + horizwords; j += 4 )
    {
      if ( comma ) Serial.printf(",");
      comma = true;
      Serial.printf(" 0x%02x%02x%02x%02x", gammaArray[j + 3], gammaArray[j + 2], gammaArray[j + 1], gammaArray[j]);
    }
  }

  checkGamma( ledRange, gammaArray );

} // genGammaTable


#endif // __GAMMA_CHECK_SKETCH__
