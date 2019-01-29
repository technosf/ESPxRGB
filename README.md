# ESPxRGB

ESPxRGB is an Arduino library of RGB, RGBW, HSV conversion functions and correction functions for Gamma and Chromiance written in Xtensa assembler for ESP SoCs.

The objective of the library is to be as fast and efficient as possible.

## Table of Contents  

- [Why an assembler RGB manipulation library](#why-an-assembler-rgb-manipulation-library)
- [Features](#features)
- [Options and Use](#options-and-use)
- [History](#history)
- [References](#references)
- [License](#license)

## Why an assembler RGB manipulation library

Looking to use small, low-powered _SoCs_ to drive long strings of LEDs with the optimum speed and power efficiency requires efficient algorythms and code. Assembler is as efficient as you can get. The ESP SoCs are great given their feature set, conectivity, power and price. Plus, they are easy to program.

## Features

ESPxRGB works in the 8-bit RGB/W space. It covers functions supporting:

* RGB to RGBW
* HSV to RGB and RGBW, with a choice of four HSV algorythms
* RGB gamma correction (for normalizing the perception of pulsing luminance)
* RGB chroma correction (for normalizing the perception of luminance across the spectrum)

Plus intersections of all the above.

Externalized _**C**_ headers provide regular Arduino and ESP-IDF code access to the functions.

## Options and Use

Drop the library into your *~Arduino/libraries* folder and include the *ESPxRGB.h* header in your project.
The library is compiled based on flags in the *src/options.h* file; The functions are grouped and can be included/excluded in the compiled code as dictated by pre-processor definitions.

The *examples* folder contains *sketches* than can test the functions and generate look-up tables used by the code. Look-up tables in the _*.S*_ files can be replaced as desired.

### Functions

#### Correction

* _xgamma8_  - Normalizes the value of a single 8-bit color value
* _xgammaarray8_  - Normalizes a range of 8-bit color values
* _xrgbgamma8_  - Normalizes a set of 8-bit RGB values
* _xrgbwgamma8_  - Normalizes a set of 8-bit RGBW values

#### Conversion

* _xrgb2rgbw8_  - RGB to RGBW
* _xhsv2rgb8s_  - HSV to RGB using the Spectrum algorythm
* _xhsv2rgb8e_  - HSV to RGB using a power efficient function
* _xhsv2rgbwt_  - HSV to RGB using a tweaked function aproximating FastLED Rainbow HSV
* _xhsv2rgb8w_  - HSV to RGB using a (sine) wave function
* _xhsv2rgb8_  - A default HSV to RGB that rferences one of the implemented function. Change as needed.

#### Combined

* _xhsv2rgbw8_      - HSV to RGBW using default HSV function
* _xhsv2rgbgamma8_   - HSV to RGB with gamma correction using default HSV function
* _xhsv2rgbwgamma8_  - HSV to RGB with gamma correction using default HSV function
* _xrgb2rgbwgamma8_  - RGB to RGBW with gamma correction

## History

* _v0.1.0_  - Initial check-in and config as a library.

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
