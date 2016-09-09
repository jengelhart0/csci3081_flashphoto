//
//  PixelBuffer.cpp
//  Copyright 2016 CSci-3081W TAs.
//
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PixelBuffer.h"
#include "ColorData.h"

#include <iostream>
#include <cstring>

using std::cerr;
using std::endl;
using std::fill;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
PixelBuffer::PixelBuffer(int w,
                         int h,
                         ColorData backgroundColor)
    : width_(w),
      height_(h),
      pixels_(new ColorData[w*h]),
      background_color_(new ColorData(backgroundColor)) {
    fillPixelBufferWithColor(backgroundColor);
}

PixelBuffer::~PixelBuffer() {
    delete [] pixels_;
    delete background_color_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData PixelBuffer::getPixel(int x, int y) const {
    ColorData pixelData;

    if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
        cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
    } else {
        int index = x + width_*(y);
        pixelData = pixels_[index];
    }
    return pixelData;
}

void PixelBuffer::setPixel(int x, int y, const ColorData& newPixel) {
    if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
        cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
    } else {
        int index = x + width_*(y);  // x + width*(height-(y+1));
        pixels_[index] = newPixel;
    }
}

ColorData const * PixelBuffer::getData() const { return pixels_; }
int PixelBuffer::getHeight() const { return height_; }
int PixelBuffer::getWidth() const { return width_; }
ColorData PixelBuffer::getBackgroundColor() { return *background_color_; }

void PixelBuffer::fillPixelBufferWithColor(ColorData color) {
    fill(pixels_, pixels_+width_*height_, color);
}

void PixelBuffer::copyPixelBuffer(
    PixelBuffer *sourceBuffer,
    PixelBuffer *destBuffer) {
    if (destBuffer->getWidth() != sourceBuffer->getWidth() ||
        destBuffer->getHeight() != sourceBuffer->getHeight()) {
        cerr << "copyPixelBuffer: " << "dimension mismatch" << endl;
    } else {
        memcpy(reinterpret_cast<void*>(destBuffer->pixels_),
               reinterpret_cast<void*>(sourceBuffer->pixels_),
               sizeof(ColorData)*static_cast<unsigned>(destBuffer->height_)*
               static_cast<unsigned>(destBuffer->width_));
    }
}
