//
//  ColorData.cpp
//  //  Copyright 2016 CSci-3081W TAs.
//

#include "ColorData.h"

ColorData::ColorData() : red_(1), green_(1), blue_(1), alpha_(1) {}

ColorData::ColorData(float r, float g, float b) :
    red_(r), green_(g), blue_(b), alpha_(1) {}

ColorData::ColorData(float r, float g, float b, float a) :
    red_(r), green_(g), blue_(b), alpha_(a)  {}

void ColorData::setRed(float r) { red_ = r; }
void ColorData::setGreen(float g) { green_ = g; }
void ColorData::setBlue(float b) { blue_ = b; }
void ColorData::setAlpha(float a) { alpha_ = a; }
float ColorData::getRed() const { return red_; }
float ColorData::getGreen() const { return green_; }
float ColorData::getBlue() const { return blue_; }
float ColorData::getAlpha() const { return alpha_;}

float ColorData::getLuminance() const {
    return static_cast<float>(0.2126)*red_ +
        static_cast<float>(0.7152)*green_ +
        static_cast<float>(0.0722)*blue_;
}

ColorData ColorData::clampedColor() const {
        float clampedRed = ColorData::clampValue(this->getRed(), 0.f, 1.f);
        float clampedGreen = ColorData::clampValue(this->getGreen(), 0.f, 1.f);
        float clampedBlue = ColorData::clampValue(this->getBlue(), 0.f, 1.f);
        float clampedAlpha = ColorData::clampValue(this->getAlpha(), 0.f, 1.f);

        return ColorData(clampedRed, clampedGreen, clampedBlue, clampedAlpha);
}


// Apply component-wise arithmatic operations
ColorData operator* (const ColorData& a, float f) {
        return ColorData(a.red_*f, a.green_*f, a.blue_*f, a.alpha_*f);
}

ColorData operator+ (const ColorData& a, const ColorData& b) {
        return ColorData(a.red_ + b.red_, a.green_ + b.green_,
                         a.blue_ + b.blue_, a.alpha_ + b.alpha_);
}

ColorData operator- (const ColorData& a, const ColorData& b) {
        return ColorData(a.red_ - b.red_, a.green_ - b.green_,
                         a.blue_ - b.blue_, a.alpha_ - b.alpha_);
}
