/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225
{
    class HSLAPixel
    {
    public:
        /**
              * Constructs a default HSLAPixel.
              * 
              * A default pixel is completely opaque (non-transparent) and white. 
              * Opaque implies that the alpha component of the pixel is 1.0. 
              * Lower alpha values are (semi-)transparent. 
              */
        HSLAPixel();

        /**
              * Constructs an opaque HSLAPixel with the given hue, saturation, and luminance values. 
              * 
              * @param hue Hue value for the new pixel, in degrees [0, 360).  
              * @param saturation Saturation value for the new pixel, [0, 1]. 
              * @param luminance Luminance value for the new pixel, [0, 1]. 
              */
        HSLAPixel(double hue,
                  double saturation,
                  double luminance);

        /**
              * Constructs an HSLAPixel with the given hue, saturation, luminance, and alpha values.  
              * 
              * @param hue Hue value for the new pixel, in degrees [0, 360).  
              * @param saturation Saturation value for the new pixel, [0, 1]. 
              * @param luminance Luminance value for the new pixel, [0, 1]. 
              * @param alpha Alpha value for the new pixel, [0, 1]. 
              */
        HSLAPixel(double hue,
                  double saturation,
                  double luminance,
                  double alpha);

        // Alpha of the pixel, [0, 1].
        double a;

        // Hue of the pixel, in degrees [0, 360).
        double h;

        // Luminance of the pixel, [0, 1].
        double l;

        // Saturation of the pixel, [0, 1].
        double s;
    };
}
