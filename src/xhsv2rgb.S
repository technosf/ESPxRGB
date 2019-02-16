/*
  ESPxRGB Library HSV Functions

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
 * Param: Reg in: Size:      
 *  h     a2      2 bytes      
 *  s     a3      1 byte       
 *  v     a4      1 byte       
 *  r*    a5      1 bytes      
 *  g*    a6      1 bytes     
 *  b*    a7      1 bytes     
 * 
 * ASM is optimized for fall-through minimal branching
 */
 
#include "options.h"

#ifndef __HSV__
#warning "HSV functions are not included."
#else
 
// Inputs
#define hue a2
#define sat a3
#define val a4
#define p_R a5
#define p_G a6
#define p_B a7

// Working storage
#define sector  a8
#define step    a9
#define base    a3  
#define slope   a10    

#define chroma  a11
#define jumper  a12
#define temp    a13

#define S_SECTORS 6     // Spectrum Sectors
#define S_STEPS   256   // SpectrumSector Steps 

#define T_SECTORS 8     // Tweaked Sectors
#define T_STEPS   192   // Tweaked Sector Steps

  .text

// --------------------- Externals ---------------------

    .global xhsv2rgb8s
    .global xhsv2rgb8e
    .global xhsv2rgb8w
    .global xhsv2rgb8t
  
// ====================== Spectrum ======================


/*         
 *  Spectrum   
 *  HSV -> RGB function             
 *  
 *  xhsv2rgb8
 *  Sectors 8, Step 192
 */
  .type   xhsv2rgb8s,@function
  .align 4
xhsv2rgb8s:
  .frame  a1,  32
  entry   a1,  32  

  movi    jumper, _hsv2rgb8s
  j _range_check_and_chroma 
  

_hsv2rgb8s:

  bbci    sector, 0x0, _s_slope_calc        // Do not invert step/slope if even sector
  
  xor     step,  step, temp                 // step = 256 - step 

    
_s_slope_calc:

  mul16u  slope,  chroma,  step             // slope = chroma * step
  srli    slope,  slope,  8                 // slope = (chroma * step) / 256
  add.n   slope,  slope,  base              // slope = ((chroma * step)/256) + base

  movi    jumper, _vector6                  // vector addr     
  j _sectorvector                           // jump to sector-specific code


  
// ====================== Efficient ======================


/*         
 *  Efficient   
 *  HSV -> RGB function             
 *  
 *  xhsv2rgb8e
 *  Sectors 8, Step 192
 */
  .type   xhsv2rgb8e,@function
  .align 4

xhsv2rgb8e:

  .frame  a1,  32
  entry   a1,  32  

  movi    jumper, _hsv2rgb8e
  j _range_check_and_chroma 


_hsv2rgb8e:

  bbci    sector, 0x0, _e_slope_calc        // Do not invert step/slope if even sector
  xor     step,   step,   temp              // step = 256 - step 
    

_e_slope_calc:

  mul16u  slope,  chroma,  step             // slope = chroma * step
  srli    slope,  slope,  9                 // slope = (chroma * step) / 512
  sub     val,    val,    slope             // val = val - slope
  add.n   slope,  slope,  base              // slope = slope + base

  movi    jumper, _vector6                  // vector addr     
  j _sectorvector                           // jump to sector-specific code

// ====================== Wave ======================


/*         
 *  Wave (Sine)   
 *  HSV -> RGB function             
 *  
 *  xhsv2rgb8w
 *  Sectors 8, Step 192
 */
  .type   xhsv2rgb8w,@function
  .align 4

xhsv2rgb8w:

  .frame  a1,  32
  entry   a1,  32  

  movi    jumper, _hsv2rgb8w
  j _range_check_and_chroma 
  
_hsv2rgb8w: 

  bbci    sector, 0x0, _w_slope_calc        // Do not invert step/slope if even sector
  xor     step,  step, temp                 // step = 256 - step 

    
_w_slope_calc:

  movi    jumper,  _wave_quarter            // sine table goes in jumper
  add.n   jumper, jumper, step              // Calculate the sine address
  l8ui    slope,  jumper, 0                 // Load into a2 the value at a2
  mul16u  slope,  slope,  chroma            // chroma * step 
  srli    slope,  slope,  8                 // slope = ((chroma * step) + base ) / 256

  sub     val,    val,    slope             // val = val - slope
  add.n   slope,  slope,  base              // slope = slope + base

  movi    jumper, _vector6                  // vector addr     
  j _sectorvector                           // jump to sector-specific code


// ====================== Tweaked ======================


/*         
 *  Tweaked (Pyschologically)   
 *  HSV -> RGB function             
 *  
 *  xhsv2rgb8t
 *  
 *  Based on Wave function with 
 */
  .type   xhsv2rgb8t,@function
  .align 4

xhsv2rgb8t:

  .frame  a1,  32
  entry   a1,  32  

  beqz    val,    _monochromatic_exit       // if v = 0, jump set values to off, exit
  beqz    sat,    _monochromatic_exit       // if s = 0, jump set values to monochromatic, exit

  /// Base
  movi    temp,   0xFF                      // Load sector step lsb mask
  xor     base,   sat, temp                 // base = 255 - sat
  mul16u  base,   base, val                 // base = ((255 - sat) * val)
  srli    base,   base, 8                   // base = ((255 - sat) * val) >> 8;
  /// chroma
  sub     chroma, val,  base                // chroma = val - base
  mov     slope,  chroma
  movi    temp,   0x03                      // chroma / 3 
  quou    chroma, chroma, temp              // chroma / 3
  /// Steps
  movi    temp,   T_STEPS                   // 192
  remu    step,   hue,  temp                // Step = mod hue, 192
  quou    sector, hue,  temp                // Sector = hue / 192
  /// Slope
  mul16u  slope,  chroma,  step             // slope = chroma * step
  quou    slope,  slope,  temp              // slope = chroma * step /192


  movi    jumper, _vector8                  // vector addr  
  movi    temp,   T_SECTORS                 // 8 sectors max
  bgeu    sector, temp, _tweak_max          // Branch if sector is out of range
  j _sectorvector                           // jump to sector-specific code

/*
 * Set max sectors, steps for tweak model
 */    
 _tweak_max:   

  movi    sector, T_SECTORS - 1                   
  movi    step,   T_STEPS - 1                    
  j _sectorvector

/*
 * Tweaked 8-sector, 192 step code
 */   
_T0:    
  sub     val,    val,    slope             // val = val - slope
  add     slope,  slope,  base              // slope = base + slope
  s8i     val,    p_R,    0
  s8i     slope,  p_G,    0
  s8i     base,   p_B,    0
  retw.n  

_T1:   
  sub     val,    val,    chroma            // val = val - chroma
  add     slope,  slope,  chroma            // slope = chroma + slope
  add     slope,  slope,  base              // slope = base + slope
  s8i     val,    p_R,    0
  s8i     slope,  p_G,    0
  s8i     base,   p_B,    0
  retw.n  

_T2:   
  addx2   temp,   slope,  chroma            // s* slope + chroma
  sub     val,    val,    temp              // val - chroma - 2*slope
  add     slope,  slope,  base              // slope = 2 * inv slope + base
  addx2   slope,  chroma,  slope 
  s8i     val,    p_R,    0
  s8i     slope,  p_G,    0
  s8i     base,   p_B,    0
  retw.n  

_T3:   
  sub     val,    val,    slope             // val = val -slope
  add     slope,  slope,  base              // slope = slope + base
  s8i     base,   p_R,    0
  s8i     val,    p_G,    0
  s8i     slope,  p_B,    0
  retw.n  

_T4:   
  addx2   slope,  slope,  chroma
  sub     val,    val,    slope
  add     slope,  slope,  base
  s8i     base,   p_R,    0
  s8i     val,    p_G,    0
  s8i     slope,  p_B,    0
  retw.n  

_T5:   
  sub     val,    val,    slope             // val = val - slope
  add     slope,  slope,  base              // slope = base + slope
  s8i     slope,  p_R,    0
  s8i     base,   p_G,    0
  s8i     val,    p_B,    0
  retw.n  

_T6:   
  add     temp,   chroma, slope             // val = val - slope
  sub     val,    val,   temp               // val = val - chroma
  add     slope,  temp,  base               // slope = base + slope
  s8i     slope,  p_R,    0
  s8i     base,   p_G,    0
  s8i     val,    p_B,    0
  retw.n  

_T7:         
  sub     slope,  chroma, slope             // Invert slope
  sub     val,    val,    slope             // val = val - inv slope
  add     slope,  slope,  base              // slope = base + inv slope
  s8i     val,    p_R,    0
  s8i     base,   p_G,    0
  s8i     slope,  p_B,    0
  retw.n  

// ============ Common ============

_range_check_and_chroma:

  beqz    val,    _monochromatic_exit       // if v = 0, jump set values to off, exit
  beqz    sat,    _monochromatic_exit       // if s = 0, jump set values to monochromatic, exit

  /// chroma
  movi    temp,   0xFF                      // Load sector step lsb mask
  xor     base,   sat,  temp                // base = 255 - sat
  mul16u  base,   base, val                 // base = ((255 - sat) * val)
  srli    base,   base, 8                   // base = ((255 - sat) * val) >> 8;
  sub     chroma, val,  base                // chroma = val - base; 

  /// Steps
  and     step,   hue, temp                 // Get sector step
  srli    sector, hue, 8                    // Shift hue right 8 places (MSB) to get sector
  bgeui   sector, S_SECTORS,  _sector_max   // If >= max sectors, max sector and steps
  jx jumper

  /*
 * Set HSV to spectrum max range - HSV_HUE_STEP
 * Set sector to max 
 */    
 _sector_max:   

  movi    sector,   S_SECTORS - 1
  movi    step,     S_STEPS - 1  
  jx jumper

// ------------------------------

_sectorvector:

  movi    temp,   0x4                     // One word 
  mul16u  temp,   temp,   sector          // sector X words   
  add.n   jumper, jumper, temp            // Vector plus words
  l32i.n  jumper, jumper, 0               // load jumper address from vector
  jx jumper                               // jump   

/*
 *  Sector-specific code
 *  
 *  Regular six-sector RGB-CMY
 */
_S0:
  s8i     val,    p_R,    0
  s8i     slope,  p_G,    0
  s8i     base,   p_B,    0
  retw.n  
_S1:   
  s8i     slope,  p_R,    0
  s8i     val,    p_G,    0
  s8i     base,   p_B,    0
  retw.n  
_S2:   
  s8i     base,   p_R,    0
  s8i     val,    p_G,    0
  s8i     slope,  p_B,    0
  retw.n  
_S3:   
  s8i     base,   p_R,    0
  s8i     slope,  p_G,    0
  s8i     val,    p_B,    0
  retw.n  
_S4:   
  s8i     slope,  p_R,    0
  s8i     base,   p_G,    0
  s8i     val,    p_B,    0
  retw.n  
_S5:   
  s8i     val,    p_R,    0
  s8i     base,   p_G,    0
  s8i     slope,  p_B,    0
  retw.n  
   
   
/*
 * Set RGB to "v" 
 */
_monochromatic_exit: 
  
  s8i  val, p_R, 0   
  s8i  val, p_G, 0  
  s8i  val, p_B, 0   
  retw.n
  
// ============ Data ============

  .data

_vector6:
  .word _S0
  .word _S1
  .word _S2
  .word _S3
  .word _S4
  .word _S5

_vector8:
  .word _T0
  .word _T1
  .word _T2
  .word _T3
  .word _T4
  .word _T5
  .word _T6
  .word _T7

#endif // __HSV__  
