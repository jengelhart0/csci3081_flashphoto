/*******************************************************************************
 * Name            : pixel_buffer.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PixelBuffer.h"
#include "ColorData.h"

#include <iostream>
#include <cstring>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
using std::cerr;
using std::endl;
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
PixelBuffer::PixelBuffer(int w,
                         int h,
                         ColorData background_color)
    : width_(w),
      height_(h),
      pixels_(new ColorData[w*h]),
      background_color_(new ColorData(background_color)) {
    FillPixelBufferWithColor(background_color);
}

PixelBuffer::~PixelBuffer(void) {
    delete [] pixels_;
    delete background_color_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData PixelBuffer::get_pixel(int x, int y) const {
    ColorData pixel_data;

    if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
        cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
    } else {
        int index = x + width_*(y);
        pixel_data = pixels_[index];
    }
    return pixel_data;
}

void PixelBuffer::set_pixel(int x, int y, const ColorData& new_pixel) {
    if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
        cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
    } else {
        int index = x + width_*(y);  // x + width*(height-(y+1));
        pixels_[index] = new_pixel;
    }
}

void PixelBuffer::FillPixelBufferWithColor(ColorData color) {
    std::fill(pixels_, pixels_+width_*height_, color);
}

/*******************************************************************************
 * Operator Definitions
 ******************************************************************************/
PixelBuffer& PixelBuffer::operator=(
    const PixelBuffer &rhs) {
    /* Check for self-assignment! */
    if (this == &rhs) {
        return *this;
    }
    if (this->width() != rhs.width() ||
        this->height() != rhs.height()) {
        cerr << "CopyPixelBuffer: dimension mismatch" << endl;
    } else {
        std::copy(this->pixels_,
                  this->pixels_+(sizeof(ColorData)*width_*height_),
                  rhs.pixels_);
    }
    return *this;
} /* operator=() */

}  // namespace image_tools
