/*

  ESPxRGB Library Header

   ------------------------------------------------------------------------------------------------

   Copyright 2019 technosf [https://github.com/technosf]

   Licensed under the GNU LESSER GENERAL PUBLIC LICENSE, Version 3.0 or greater (the "License"); 
   you may not use this file except in compliance with the License. 
   You may obtain a copy of the License at

   https://www.gnu.org/licenses/lgpl-3.0.en.html
   Unless required by applicable law or agreed to in writing, 
   software distributed under the License is distributed on an "AS IS" BASIS, 
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
   See the License for the specific language governing permissions and limitations under the License.
*/


#ifndef ESPXRGB_H
#define ESPXRGB_H

#include "options.h"
#include "Arduino.h"

extern "C"
{

#ifdef __GAMMA__

  /*
    Gamma correction on an 8-bit range
  */
  uint8_t xgamma8( uint8_t val );

  /*
     Gamma correction over an array of 8-bit values
  */
  void xgammaarray8( uint8_t *pntr, uint8_t count );


  /*
    Gamma correction on RGB in 8-bit range
  */
  void xrgbgamma8( uint8_t *r, uint8_t *g , uint8_t *b );

  /*

    /*
    Gamma correction on RGB in 8-bit range
  */
 // void xrgbgammashift8( uint8_t *r, uint8_t *g , uint8_t *b );

  /*

    Gamma correction on RGBW in 8-bit range
  */
  void xrgbwgamma8( uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w );

  /*
    Luma shift on RGB in 8-bit range
  */
 // void xrgbluma8( uint8_t *r, uint8_t *g , uint8_t *b, int8_t shift );

  /*
     Luma shift over an array of 8-bit values
  */
 // void xlumaarray8( uint8_t *pntr, uint8_t count, int8_t shift  );

#endif // __GAMMA__


#ifdef __HSV__

  /*
     HSV to RGB for 8-bit range
  */
  void xhsv2rgb8s( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b );
  void xhsv2rgb8e( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b );
  void xhsv2rgb8w( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b );
  void xhsv2rgb8t( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b );

#endif // __HSV__


#ifdef __RGBW__

  /*
     RGB to RGBW conversion on 8-bit range
  */
  void xrgb2rgbw8( uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w );   // Done

#endif // __RGBW__


  // ------------------- Convienence functions ------------------------------


#ifdef __GAMMA_RGBW__

  /*
     RGB to RGBW with Gamma Correction for 8-bit range
  */
  void xrgb2rgbwgamma8( uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w )
  {
    xrgb2rgbw8( r, g, b, w );
    xrgbwgamma8( r, g, b, w );
  }

#endif // __GAMMA__RGBW__ 


#ifdef __HSV_RGBW__

  /*
     HSV to RGBW for 8-bit range
  */
  void xhsv2rgbw8( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b , uint8_t *w )
  {
    //xhsv2rgb8( h, s, v, r, g, b );
    xrgb2rgbw8( r, g, b, w );
  }

#endif


#ifdef __GAMMA_HSV_RGBW__

  /*
     HSV to RGB conversion with Gamma correction for 8-bit range
  */
  void xhsv2rgbgamma8( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b )
  {
    xhsv2rgb8s( h, s, v, r, g, b );
    xrgbgamma8( r, g, b );
  }

  /*
     HSV to RGBW with Gamma Correction for 8-bit range
  */
  void xhsv2rgbwgamma8( uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b, uint8_t *w )
  {
    xhsv2rgb8s( h, s, v, r, g, b );
    xrgb2rgbw8( r, g, b, w );
    xrgbwgamma8( r, g, b, w );
  }

#endif // __GAMMA_HSV_RGBW__

}

#endif // ESPXRGB_H
