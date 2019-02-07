/*  
  Modified from code from that

    created 05-01-2010 by kasperkamperman.com
*/

void getKKRGB(uint16_t hue, uint8_t sat, uint8_t val, uint8_t *R, uint8_t *G , uint8_t *B) 
{ 

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    *R=val;
    *G=val;
    *B=val;  
  } else  { 

    base = ((255 - sat) * val)>>8;

    switch(hue/60) {
    case 0:
        r = val;
        g = (((val-base)*hue)/60)+base;
        b = base;
    break;

    case 1:
        r = (((val-base)*(60-(hue%60)))/60)+base;
        g = val;
        b = base;
    break;

    case 2:
        r = base;
        g = val;
        b = (((val-base)*(hue%60))/60)+base;
    break;

    case 3:
        r = base;
        g = (((val-base)*(60-(hue%60)))/60)+base;
        b = val;
    break;

    case 4:
        r = (((val-base)*(hue%60))/60)+base;
        g = base;
        b = val;
    break;

    case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(hue%60)))/60)+base;
    break;
    }

    *R=r;
    *G=g;
    *B=b; 
  }   
}
