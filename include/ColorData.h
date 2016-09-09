/*******************************************************************************
 * Name            : ColorData.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Class definition for storing colors in floating point format
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_COLORDATA_H_
#define INCLUDE_COLORDATA_H_

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/** This color data class stores color in floating point format.
    The Red, Green, Blue, and Alpha channels range from 0.0 to 1.0. */
class ColorData {
 public:
    ColorData();
    ColorData(float r, float g, float b);
    ColorData(float r, float g, float b, float a);

    void setRed(float r);
    void setBlue(float b);
    void setGreen(float g);
    void setAlpha(float a);

    float getRed() const;
    float getBlue() const;
    float getGreen() const;
    float getAlpha() const;

    // Returns the "brightness" of the color according to a perceptual metric
    // that weights the red, green, and blue components of the color
    // non-uniformly.
    float getLuminance() const;

    // Return a clamped version of this ColorData
    ColorData clampedColor() const;

    // Arithmatic operators (friends so that non-member functions can access
    // private variables)
    friend ColorData operator* (const ColorData& a, float f);
    friend ColorData operator+ (const ColorData& a, const ColorData& b);
    friend ColorData operator- (const ColorData& a, const ColorData& b);

 private:
    // General helper function for clamping values between 0 and 1
    static inline float clampValue(float input, float a, float b)
        { return input < a ? a : (input > b ? b : input);}

    float red_;
    float green_;
    float blue_;
    float alpha_;
};

#endif  // INCLUDE_COLORDATA_H_
