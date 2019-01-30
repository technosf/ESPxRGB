/*
 * Main Example Routine
 * 
   Perform function checks 
*/
void setup()
{
  Serial.begin(115200);

  checkGAMMA();
  checkHSV();
  checkRGBW();
  checkGAMMARGBW();
  checkHSVRGBW();
  checkGAMMAHSVRGBW();
  //genWave();
}


/*
  Not used
*/
void loop()
{
}
