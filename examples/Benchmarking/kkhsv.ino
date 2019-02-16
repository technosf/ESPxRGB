/*
  Modified from code from that

    created 05-01-2010 by kasperkamperman.com
*/

void getKKRGB(uint16_t hue, uint8_t sat, uint8_t val, uint8_t *R, uint8_t *G , uint8_t *B)
{

  uint8_t r, g, b, base, sextant, step;

  if (sat == 0 || val == 0) { // Acromatic color (gray). Hue doesn't mind.
    *R = val;
    *G = val;
    *B = val;
  } else  {

    sextant = hue >> 8;
    step = hue % 256;
    if ( sextant >= 6 )
    {
      sextant = 5;
      step = 255;
    }
    base = ((255 - sat) * val) >> 8;


    switch (sextant) {
      case 0:
        r = val;
        g = (((val - base) * step) / 255) + base;
        b = base;
        break;

      case 1:
        r = (((val - base) * (255 - step)) / 255) + base;
        g = val;
        b = base;
        break;

      case 2:
        r = base;
        g = val;
        b = (((val - base) * step) / 255) + base;
        break;

      case 3:
        r = base;
        g = (((val - base) * (255 - step)) / 255) + base;
        b = val;
        break;

      case 4:
        r = (((val - base) * step) / 255) + base;
        g = base;
        b = val;
        break;

      case 5:
        r = val;
        g = base;
        b = (((val - base) * (255 - step)) / 255) + base;
        break;
    }

    *R = r;
    *G = g;
    *B = b;
  }
}
