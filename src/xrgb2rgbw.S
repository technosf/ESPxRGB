/*
  ESPxRGB Library RGB/W Functions

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
   ESPxRGB Library RGB to RGBW conversion functions

   Param: Reg in: Size:
    r*    a2      1 bytes
    g*    a3      1 bytes
    b*    a4      1 bytes
    w*    a5      1 bytes

  M = max(Ri,Gi,Bi)
  m = min(Ri,Gi,Bi)

  Wo = if (m/M < 0.5) use ( (m*M) / (M-m) ) else M
  Q = 255
  K = (Wo + M) / m
  Ro = floor( [ ( K * Ri ) - Wo ] / Q )
  Go = floor( [ ( K * Gi ) - Wo ] / Q )
  Bo = floor( [ ( K * Bi ) - Wo ] / Q )
*/

#include "options.h"


#ifndef __RGBW__
#warning "RGBW functions are not included."
#else

// Inputs
#define p_R a2
#define p_G a3
#define p_B a4
#define p_W a5

// Working storage
#define R a6
#define G a7
#define B a8
#define m a9
#define M a10
#define W a11
#define K a12
#define Q a13
#define temp a14


// -------------- Macros --------------

/*
   floor( [ ( K * Color ) - White ] / Q )
   Store result
*/
.macro    m_calcoffset color: req, pntr: req
  mul16u  \color,  \color,  K
  sub     \color,  \color,  W
  quou    \color,  \color,  Q
  s8i     \color,  \pntr,   0
.endm


  .text

// --------------- Externals ---------------

    .global xrgb2rgbw8

// --------------- Code ---------------

/*
    RGB to RGBW 8 bit conversion

*/
  .type   xrgb2rgbw8, @function
  .align 4
xrgb2rgbw8:
  .frame  a1,   32
  entry   a1,   32


_rgb2rgbw8:
// Get the color values from the pointers
  l8ui    R,    p_R,  0
  l8ui    G,    p_G,  0
  l8ui    B,    p_B,  0
  movi    W,    0

// Max - M = max(Ri,Gi,Bi)
  maxu    M,    R,    G
  maxu    M,    M,    B
  beqz    M,    _exit               // Max is zero, w = zero
  
// Min - m = min(Ri,Gi,Bi)
  minu    m,    R,    G
  minu    m,    m,    B
  beqz    m,    _exit               // Min is zero, w = Max
  
  mov     W,    M                   // W = M, default
  slli    temp, m,    1             // temp = 2m
  bge     M,    temp, _k            // M > 2 * m, bypass calc, use W = M
  
  mul16u  W,    m,    M             // W = M*m
  sub     temp, M,    m             // temp = M -m
  quou    W,    W,    temp          // W = (M * m) / (M - m)


_k:
  add     K,    W,    M             // K = (Wo + M)
  quou    K,    K,    m             // K = (Wo + M) / m
  
  movi    Q,    0xFF
  m_calcoffset  R,    p_R
  m_calcoffset  G,    p_G
  m_calcoffset  B,    p_B

_exit:

s8i       W,    p_W,  0
retw.n

#endif  // __RGBW__
