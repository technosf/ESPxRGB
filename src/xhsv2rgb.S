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

#define delta   a11
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
  .frame    a1,  32
  entry     a1,  32  

  movi  jumper, _hsv2rgb8s
  j     _range_check_and_delta 

  /*
   * 
  val = dim_curve[val];
  sat = 255 - dim_curve[255 - sat];
   */
   /*
  _sdimmer: 
  movi    jumper,  _dim_curve        // Gamma table goes in a3
  add.n   val,    val, jumper                // Calculate the gamma address
  l8ui    val,    val,  0                // Load into a2 the value at a2
  */

  
/*
 * Do the calculations 
 */
_hsv2rgb8s:

  bbci    sector, 0x0, _s_slope_calc    // Do not invert step/slope if even sector
  
  xor     step,  step, temp             // step = 256 - step 

    
_s_slope_calc:

  mul16u  slope,  delta,  step          // slope = delta * step
  srli    slope,  slope,  8             // slope = (delta * step) / 256
  add.n   slope,  slope,  base          // slope = ((delta * step)/256) + base

  movi    jumper, _vector6               // vector addr     
  j _sectorvector                       // jump to sector-specific code


  
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
  .frame    a1,  32
  entry     a1,  32  

  movi  jumper, _hsv2rgb8e
  j     _range_check_and_delta 

  /*
   * 
  val = dim_curve[val];
  sat = 255 - dim_curve[255 - sat];
   */
   /*
  _sdimmer: 
  movi    jumper,  _dim_curve        // Gamma table goes in a3
  add.n   val,    val, jumper                // Calculate the gamma address
  l8ui    val,    val,  0                // Load into a2 the value at a2
  */

  
/*
 * Do the calculations 
 */
_hsv2rgb8e:
  
  bbci    sector, 0x0, _e_slope_calc    // Do not invert step/slope if even sector
  
  xor     step,  step, temp             // step = 256 - step 

    
_e_slope_calc:

  mul16u  delta,  delta,  step          // delta * step
  add.n   slope,  base,   delta         // slope = (delta * step) + base
  srli    slope,  slope,  9             // slope = ((delta * step) + base ) / 512
  xor     val,    slope,  temp          // val = inverted slope

  movi    jumper, _vector6               // vector addr     
  j _sectorvector                       // jump to sector-specific code

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
  .frame    a1,  32
  entry     a1,  32  

  movi  jumper, _hsv2rgb8w
  j     _range_check_and_delta 
  
/*
 * Do the calculations 
 */
_hsv2rgb8w: 

  bbci    sector, 0x0, _w_slope_calc    // Do not invert step/slope if even sector
  
  xor     step,  step, temp             // step = 256 - step 

    
_w_slope_calc:

  mul16u  delta,  delta,  step          // delta * step
  add.n   slope,  base,   delta         // slope = (delta * step) + base
  srli    slope,  slope,  8             // slope = ((delta * step) + base ) / 256 
 
  movi    jumper,  _wave_quarter        // sine table goes in jumper
  add.n   jumper, jumper, slope         // Calculate the sine address
  l8ui    slope,  jumper, 0             // Load into a2 the value at a2

  xor     val,    slope,  temp          // val = inverted slope

  movi    jumper, _vector6               // vector addr     
  j _sectorvector                       // jump to sector-specific code


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
  .frame    a1,  32
  entry     a1,  32  

  beqz    val,    _monochromatic_exit       // if v = 0, jump set values to off, exit
  beqz    sat,    _monochromatic_exit       // if s = 0, jump set values to monochromatic, exit

  /// Base
  movi    temp,   0xFF                      // Load sector step lsb mask
  xor     base,   sat, temp                 // base = 255 - sat
  mul16u  base,   base, val                 // base = ((255 - sat) * val)
  srli    base,   base, 8                   // base = ((255 - sat) * val) >> 8;
  /// Delta
  sub     delta,  val,  base                // delta = val - base
  mov     slope,  delta
  movi    temp,   0x03                      // delta / 3 
  quou    delta,  delta,  temp              // delta / 3
  /// Steps
  movi    temp,   T_STEPS                   // 192
  remu    step,   hue,  temp                // Step = mod hue, 192
  quou    sector, hue,  temp                // Sector = hue / 192
  /// Slope
  mul16u  slope,  delta,  step              // slope = delta * step
  quou    slope,  slope,  temp              // slope = delta * step /192


  movi    jumper, _vector8                   // vector addr  
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
  sub     val,    val,    delta             // val = val - delta
  add     slope,  slope,  delta             // slope = delta + slope
  add     slope,  slope,  base              // slope = base + slope
  s8i     val,    p_R,    0
  s8i     slope,  p_G,    0
  s8i     base,   p_B,    0
  retw.n  

_T2:   
  addx2   temp,   slope,  delta           // s* slope + delta
  sub     val,    val,    temp            // val - delta - 2*slope
  add     slope,  slope,  base            // slope = 2 * inv slope + base
  addx2   slope,  delta,  slope 
  s8i     val,    p_R,    0
  s8i     slope,  p_G,    0
  s8i     base,   p_B,    0
  retw.n  

_T3:   
  sub     val,    val,    slope           // val = val -slope
  add     slope,  slope,  base            // slope = slope + base
  s8i     base,   p_R,    0
  s8i     val,    p_G,    0
  s8i     slope,  p_B,    0
  retw.n  

_T4:   
  addx2   slope,  slope,  delta
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
  add     temp,   delta, slope             // val = val - slope
  sub     val,    val,   temp             // val = val - delta
  add     slope,  temp,  base              // slope = base + slope
  s8i     slope,  p_R,    0
  s8i     base,   p_G,    0
  s8i     val,    p_B,    0
  retw.n  

_T7:         
  sub     slope,  delta,  slope              // Invert slope
  sub     val,    val,    slope             // val = val - inv slope
  add     slope,  slope,  base              // slope = base + inv slope
  s8i     val,    p_R,    0
  s8i     base,   p_G,    0
  s8i     slope,  p_B,    0
  retw.n  

// ============ Common ============

_range_check_and_delta:
  beqz    val,    _monochromatic_exit       // if v = 0, jump set values to off, exit
  beqz    sat,    _monochromatic_exit       // if s = 0, jump set values to monochromatic, exit

  /// Delta
  movi    temp,   0xFF                      // Load sector step lsb mask
  xor     base,   sat, temp                 // base = 255 - sat
  mul16u  base,   base, val                 // base = ((255 - sat) * val)
  srli    base,   base, 8                   // base = ((255 - sat) * val) >> 8;
  sub     delta,  val,  base                // delta = val - base; 

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
  jx      jumper                          // jump   

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

_dim_curve:
.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
.word 0x00000000, 0x00000000, 0x00000000, 0x01010101
.word 0x01010101, 0x01010101, 0x02020201, 0x02020202
.word 0x03030202, 0x03030303, 0x04040404, 0x05050504
.word 0x06060605, 0x07070706, 0x08080807, 0x0a090909
.word 0x0b0b0a0a, 0x0c0c0c0b, 0x0e0e0d0d, 0x100f0f0f
.word 0x12111110, 0x14131312, 0x16161515, 0x19181717
.word 0x1b1b1a19, 0x1e1d1d1c, 0x21201f1f, 0x24232222
.word 0x27262625, 0x2b2a2928, 0x2e2d2c2c, 0x3231302f
.word 0x36353433, 0x3a393837, 0x3f3e3d3b, 0x43424140
.word 0x48474645, 0x4d4c4b4a, 0x5351504f, 0x58575554
.word 0x5e5d5b5a, 0x6462615f, 0x6a696766, 0x716f6d6c
.word 0x77767472, 0x7e7d7b79, 0x86848280, 0x8d8b8988
.word 0x9593918f, 0x9d9b9997, 0xa5a3a19f, 0xaeacaaa7
.word 0xb7b5b2b0, 0xc0bebbb9, 0xc9c7c5c2, 0xd3d1cecc
.word 0xdddbd8d6, 0xe8e5e2e0, 0xf2f0edea, 0xfdfaf8f5

_wave_quarter:
/*
 *  Quarter wave, 256 steps, 0x7F max
 */
.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
.word 0x00000000, 0x01010100, 0x01010101, 0x02020201
.word 0x02020202, 0x03030303, 0x04040403, 0x05050404
.word 0x06050505, 0x07060606, 0x08080707, 0x09090808
.word 0x0a0a0a09, 0x0b0b0b0a, 0x0d0c0c0c, 0x0e0e0e0d
.word 0x100f0f0f, 0x11111110, 0x13131212, 0x15141413
.word 0x16161615, 0x18181717, 0x1a1a1919, 0x1c1c1b1b
.word 0x1e1e1d1d, 0x20201f1f, 0x22222121, 0x24242323
.word 0x27262625, 0x29282827, 0x2b2b2a2a, 0x2e2d2c2c
.word 0x30302f2e, 0x33323131, 0x35353433, 0x38373636
.word 0x3a3a3938, 0x3d3c3c3b, 0x403f3e3e, 0x42424140
.word 0x45454443, 0x48474746, 0x4b4a4949, 0x4e4d4c4c
.word 0x51504f4f, 0x54535251, 0x57565554, 0x5a595857
.word 0x5d5c5b5a, 0x605f5e5d, 0x63626160, 0x66656463
.word 0x69686767, 0x6c6b6a6a, 0x6f6e6d6d, 0x72717170
.word 0x75757473, 0x78787776, 0x7c7b7a79, 0x7f7e7d7c




#endif // __HSV__  
