/*
   ESPxRGB Library Options 

   Compile options for ESPxRGB

*/

#if !defined (ARDUINO_ARCH_ESP32) && !defined (ARDUINO_ARCH_ESP8266)
#error "ESP target required for compilation"
#endif

#ifndef _ASMLANGUAGE  /* conditionalize to avoid cpp warnings (3rd parties might use same macro) */
#define _ASMLANGUAGE
#endif


/*
    Features to compile in
*/
#define __GAMMA__       // Gamma correction functions
#define __HSV__         // HSV to RGB conversion functions
#define __RGBW__        // RGB to RGBW conversion functions


/*
 * Compile logic
 */
#if defined (__GAMMA__ ) && defined ( __RGBW__ )
#define __GAMMA_RGBW__
#endif

#if defined ( __HSV__ ) && defined ( __RGBW__ )
#define __HSV_RGBW__
#endif

#if defined (__GAMMA__ ) && defined ( __HSV__ )&& defined ( __RGBW__ )
#define __GAMMA_HSV_RGBW__
#endif


/*
   Function Configurations
*/

#ifdef __GAMMA__

#define GAMMA_CORRECTION 2.8    // Gamma correction used to generate table in sketch

//
//#define __GAMMA_CHECK_SKETCH__    // Sketch checks its generated gamma table against the compiled function
//

#endif // __GAMMA__


#ifdef __HSV__
/*
 * HSV configuration
 */
#define HSV_SEXTANTS    6
#define HSV_HUE_SEXTANT 256
#define HSV_HUE_STEPS   (HSV_SEXTANTS * HSV_HUE_SEXTANT)
#define HSV_HUE_MIN     0
#define HSV_HUE_MAX     (HSV_HUE_STEPS - 1)
#define HSV_SAT_MIN     0
#define HSV_SAT_MAX     255
#define HSV_VAL_MIN     0
#define HSV_VAL_MAX     255

#endif // __HSV__
