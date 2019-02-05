# ESPxRGB 

ESPxRGB is an Arduino library of RGB, RGBW, HSV conversion functions and Gamma Correction written in Xtensa assembler for ESP SoCs.

## Table of Contents 

- [Why an assembler RGB manipulation library](#why-an-assembler-rgb-manipulation-library)
- [Features](#features)
- [Options and Use](#options-and-use)
- [Versions](#versions)
- [History and References](#history_and_references)
- [License](#license)

## Why an assembler RGB manipulation library 

Looking to use small, low-powered SoCs to drive long strings of LEDs with the optimum speed and power efficiency places a premium on efficient algorythms and code, and Assembler is as efficient as you can get. The ESP SoCs are great given their feature set, conectivity, power and price. Plus, they are easy to program with a nice instruction set. 

The assembler itself is contained in GNU-format assembler **.S** files, and is not _inline assembler_. The **.S** files are compiled along with the **ESPxRGB.h** header when pulled into a project.

## Features 

ESPxRGB currently works in the 8-bit RGB/W space only. It covers functions supporting:
* RGB to RGBW
* HSV to RGB and RGBW, with a choice of four HSV algorythms
* RGB gamma correction (for normalizing the perception of pulsing luminance)
* RGB chroma correction (for normalizing the perception of luminance across the spectrum)

plus intersections of some of the above.

External **C** headers provide regular Arduino and ESP-IDF code access to the functions.

## Options and Use

Drop the library into your *~Arduino/libraries* folder and include the *ESPxRGB.h* header in your project.
The library is compiled based on flags in the *src/options.h* file:
The functions are grouped and can be included/excluded in the compiled code as dictated by pre-processor definitions.

The *examples* folder contains *sketches* than can test the functions and generate look-up tables used by the code.

### Functions

#### Conversion

* *xgamma8* - Normalizes the value of a single 8-bit color value 
* *xgammaarray8*  -  Normalizes a range of 8-bit color values 
* *xrgbgamma8* -  Normalizes a set of 8-bit RGB values 
* *xrgbwgamma8*  - Normalizes a set of 8-bit RGBW values 

#### Conversion

* *xrgb2rgbw8* - RGB to RGBW
* *xhsv2rgb8s* - HSV to RGB using the Spectrum algorythm
* *xhsv2rgb8e* -  HSV to RGB using a power efficient function
* *xhsv2rgbwt* - HSV to RGB using a tweaked function aproximating FastLED Rainbow HSV 
* *xhsv2rgb8w* -  HSV to RGB using a (sine) wave function
* *xhsv2rgb8* -  HSV to RGB default function that points to an above function of your choice.

#### Combined 

* *xhsv2rgbgamma8* -  HSV to RGB with gamma correction
* *xhsv2rgbwgamma8* - HSV to RGB with gamma correction
* *xrgb2rgbwgamma8* -  RGB to RGBW with gamma correction

 
##  Versions

* _0.1.0_	Initial commit and pre-release


## History and References

I came to write this library after looking into options to do HSV-to-RGB conversion. Initially I looked at [FastLED](https://github.com/FastLED/FastLED) but determined it too broad a library for my use, and it dictated that FastLED be at the center of whatever you were doing which was not what I wanted.

Next I came to use [fast_hsv2rgb from Vagrearg](http://www.vagrearg.org/content/hsvrgb): Lots of interesting math and theory on _spectrum_ HSV, with **C** implementations, and also **AVR**, which got me thinking of why not an **Xtensa** version. I tried copying the logic of the _AVR_ in _fast_hsv2rgb_, and then the _C_ logic, both of which use opaque iterative pointer-swapping, but I decided to use a _jump table_, and then to move to simplify the whole thing.

And the simplest HSV to RGB code out there, I found, is [Kasper Kamperman's](https://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/), with a simple flow through and _case_ at the end. Looking at it, I found I could simplify it a little more by pulling common calculation up out of the _case_; I then implemented that in _Xtensa_. Kasper also addressed _dimming_ for luminance normalization.

Reading up on HSV again on [Instructables](https://www.instructables.com/id/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/), [Ontaelio](https://www.instructables.com/member/Ontaelio/) also spoke to power efficiency through using wave forms and in to how they effected percieved color. I added both power-efficient (saw-tooth) and smoother looking (sine) wave implementation leveraging the _spectrum_ HSV code.

Yet the discussion of more natural looking HSV color-wheels led me to look back at [FastLED HSV to RGB](https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors) and at their _Rainbow_ HSV. Not being able to quickly grok the code, [looking at the rainbow waveform image](https://raw.github.com/FastLED/FastLED/gh-pages/images/HSV-rainbow-with-desc.jpg) led me to implement an approximation of that as simply as I could.


## License 

ESPxRGB - Copyright 2019  technosf  [https://github.com/technosf]

Licensed under the GNU LESSER GENERAL PUBLIC LICENSE, Version 3.0 or greater (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	https://www.gnu.org/licenses/lgpl-3.0.en.html

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
