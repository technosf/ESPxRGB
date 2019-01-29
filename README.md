# ESPxRGB

ESPxRGB is an Arduino library of RGB, RGBW, HSV conversion functions and Gamma Correction written in Xtensa assembler for ESP SoCs.

## Table of Contents  

- [Why an assembler RGB manipulation library](#why-an-assembler-rgb-manipulation-library)
- [Features](#features)
- [Options and Use](#options-and-use)
- [History](#history)
- [References](#references)
- [License](#license)

## Why an assembler RGB manipulation library

Looking to use small, low-powered SoCs to drive long strings of LEDs with the optimum speed and power efficiency requires efficient algorythms and code. Assembler is as efficient as you can get. The ESP SoCs are great given their feature set, conectivity, power and price. Plus, they are easy to program.

## Features

ESPxRGB works in the 8-bit RGB/W space. It covers functions supporting:
_ RGB to RGBW
_ _HSV to RGB and RGBW, with a choice of four HSV algorythms
_ RGB gamma correction (for normalizing the perception of pulsing luminance)
_ RGB chroma correction (for normalizing the perception of luminance across the spectrum)
plus intersections of all the above.

External **C** headers provide regular Arduino and ESP-IDF code access to the functions.

## Options and Use

Drop the library into your *~Arduino/libraries* folder and include the *ESPxRGB.h* header in your project.
The library is compiled based on flags in the *src/options.h* file:
The functions are grouped and can be included/excluded in the compiled code as dictated by pre-processor definitions.

The *examples* folder contains *sketches* than can test the functions and generate look-up tables used by the code.

### Functions

#### Conrection

_ *xgamma8* Normalizes the value of a single 8-bit color value
_ *xgammaarray8*    Normalizes a range of 8-bit color values
_ *xrgbgamma8* Normalizes a set of 8-bit RGB values
_ *xrgbwgamma8* Normalizes a set of 8-bit RGBW values

#### Conversion

_ *xrgb2rgbw8* RGB to RGBW
_ *xhsv2rgb8s* HSV to RGB using the Spectrum algorythm
_ *xhsv2rgb8e*  HSV to RGB using a power efficient function
_ *xhsv2rgbwt*   HSV to RGB using a tweaked function aproximating FastLED Rainbow HSV
_ *xhsv2rgb8w*   HSV to RGB using a (sine) wave function

#### Combined

_ *xhsv2rgbgamma8*  HSV to RGB with gamma correction
_ *xhsv2rgbwgamma8* HSV to RGB with gamma correction
_ *xrgb2rgbwgamma8* RGB to RGBW with gamma correction

## History

## References

## License

ESPxRGB - Copyright 2019 technosf [<https://github.com/technosf>]

Licensed under the GNU LESSER GENERAL PUBLIC LICENSE, Version 3.0 or greater (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.gnu.org/licenses/lgpl-3.0.en.html

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
