/*
  ESPxRGB Library Gamma Functions

  v0.1.0

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

/*
 * ESPxRGB Library Gamma functions
 * 
 *  For driving RGB LEDs with RGB data. Reduces RGB values down to a range perceivable by
 */

#include "options.h"


#ifndef __GAMMA__
#warning "Gamma functions are not included."
#else  

// Inputsfor rgb
#define p_R a2
#define p_G a3
#define p_B a4
#define p_W a5
#define mtpl a6


// Inputsfor rgb
#define pntr a2
#define count a3

// Working storage
#define gammatbl a7
#define val a8
#define temp a9


// -------------- Macros --------------


/*
 * Update the pointer with the gamma lookup from the table
 */
.macro  m_gamma8  pntr:req, gamma:req
  l8ui    temp, \pntr,  0                   // load the raw color value
  add.n   temp, temp,   \gamma              // Calculate the corrected gamma value adress                
  l8ui    temp, temp,   0                   // Load the gamma value into temp from address in temp
  s8i     temp, \pntr,  0                   // Store the corrected color value
.endm  

/*
 * Multiply the pointer value, then 
 * Update the pointer with the gamma lookup from the table
 */
.macro  m_m_gamma8  pntr:req, gamma:req
  l8ui    temp, \pntr,  0                   // load the raw color value
  movi    val,  0x3f80                      // MSBs Float 1.0
  quou    val,  mtpl,   val                 // fp 1 = 0x100
  mul16u  temp, temp,   val                 // temp = temp * val
  srli    temp, temp,   8                   // rs temp 8
  add.n   temp, temp,   \gamma              // Calculate the corrected gamma value adress                
  l8ui    temp, temp,   0                   // Load the gamma value into temp from address in temp
  s8i     temp, \pntr,  0                   // Store the corrected color value
.endm  


  .text

// --------------- Externals ---------------

    .global xgamma8      
    .global xgammaarray8
    .global xrgbgamma8    
    .global xrgbwgamma8   
    .global xrgbmgamma8    
    .global xrgbwmgamma8   
  
// --------------- Code ---------------

/*            
 *  Gamma Correction       
 *  
 *  xgamma8
 *  
 */
  .type   xgamma8,@function
  .align 4

xgamma8:

  .frame  a1,  32
  entry   a1,  32     


_gamma8:  

  movi    a3, _gamma8_table                 // Gamma table goes in a3
  add.n   a2, a2,   a3                      // Calculate the gamma address
  l8ui    a2, a2,   0                       // Load into a2 the value at a2
  retw.n                                    // Return from the windowed call


/*            
 *  RGB Gamma Correction 
 *  
 *  xrgbmgamma8
 *  
 */
  .type   xrgbmgamma8,@function
  .align 4

xrgbmgamma8:

  .frame  a1,  32
  entry   a1,  32   

_rgbmgamma8:

  movi    gammatbl, _gamma8_table           // Lookup table address
  mov     mtpl,     a5                      // Move mltiplier from a5 to a6
  
_calc_rgb_mgamma8:  

  m_m_gamma8  p_R,  gammatbl                // Red
  m_m_gamma8  p_G,  gammatbl                // Green
  m_m_gamma8  p_B,  gammatbl                // Blue
  retw.n  


/*            
 *  RGB Gamma Correction 
 *  
 *  xrgbwmgamma8
 *  
 */
  .type   xrgbwmgamma8,@function
  .align 4

xrgbwmgamma8:

  .frame  a1,  32
  entry   a1,  32     

_rgbwmgamma8:  

  movi    gammatbl, _gamma8_table
  
_calc_w_mgamma8:  

  m_m_gamma8  p_W,  gammatbl                // White
  j _calc_rgb_mgamma8                       // Calculate the RGB
  

/*            
 *  RGB Gamma Correction 
 *  
 *  xrgbgamma8
 *  
 */
  .type   xrgbgamma8,@function
  .align 4

xrgbgamma8:

  .frame  a1,  32
  entry   a1,  32     


_rgbgamma8:

  movi    gammatbl, _gamma8_table           // Lookup table address

  
_calc_rgb_gamma8:  

  m_gamma8  p_R,  gammatbl                  // Red
  m_gamma8  p_G,  gammatbl                  // Green
  m_gamma8  p_B,  gammatbl                  // Blue
  retw.n   

  
/*            
 *  RGBW Gamma Correction (White, then RGB)        
 *  
 *  xrgbwgamma8
 *  
 */
  .type   xrgbwgamma8,@function
  .align 4

xrgbwgamma8:

  .frame  a1,  32
  entry   a1,  32     


_rgbwgamma8:
  
  movi    gammatbl, _gamma8_table
  
_calc_w_gamma8:  

  m_gamma8  p_W,    gammatbl                // White
  j _calc_rgb_gamma8                        // Calculate the RGB
     


/*            
 *  RGB Gamma Correction 
 *  
 *  xgammaarray8
 *  
 *  Gamma correct values in an 8bit value array
 */
  .type   xgammaarray8,@function
  .align 4

xgammaarray8:

  .frame  a1,  32
  entry   a1,  32     

_gammaarray8:  

  beqz      count,    _loopexit
  movi      gammatbl, _gamma8_table

_calc_array_gamma8:

  loop      count,    _loopexit    
  m_gamma8  pntr,     gammatbl              // Update pntr addr with gamma tble lookup   
  addi.n    pntr,     pntr,     0x01        // Increment pntr   
  
_loopexit:

  retw.n  

/*            
 *  RGB Luma Correction 
 *  
 *  xrgbluma8
 *  
 *  Gamma correct values in an 8bit value array
 */
  .type   xrgbluma8,@function
  .align 4

xrgbluma8:

  .frame  a1,  32
  entry   a1,  32     

_rgbluma8:  

  l8ui    val,  p_R,  0                     // Halve Red intensity
  srli    val,  val,  1
  s8i     val,  p_R,  0 

  l8ui    val,  p_G,  0                     // Quarter Green intensity
  srli    val,  val,  2
  s8i     val,  p_G,  0 

  l8ui    val,  p_B,  0                 // Boost Blue intensity by an eigth
  movi    temp, 0xEE
  bge     val,  temp, _lumaexit
  srli    temp, val,  5
  add.n   val,  val,  temp
  s8i     val,  p_B,  0 
  
_lumaexit:

  retw.n  

#endif      
