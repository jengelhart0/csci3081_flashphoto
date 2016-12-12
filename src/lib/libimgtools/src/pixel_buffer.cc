/*******************************************************************************
 * Name            : pixel_buffer.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/pixel_buffer.h"
#include <iostream>
#include <cstring>
#include "include/color_data.h"

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
      pixels_(w*h, background_color),
      background_color_(background_color) {}

PixelBuffer::PixelBuffer(
    const PixelBuffer&rhs) : PixelBuffer(rhs.width_,
                                         rhs.height_,
                                         rhs.background_color_) {
  std::copy(rhs.pixels_.begin(), rhs.pixels_.end(), pixels_.begin());
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
    int index = x + width_*(y);
    pixels_[index] = new_pixel.clamped_color();
  }
}
/*******************************************************************************
 * Operators
 ******************************************************************************/
PixelBuffer& PixelBuffer::operator=(
    const PixelBuffer &rhs) {
  /* Check for self-assignment! */
  if (this == &rhs) {
    return *this;
  }
  this->pixels_ = rhs.pixels_;
  this->background_color_ = rhs.background_color_;

  return *this;
} /* operator=() */

bool PixelBuffer::operator==(
        const PixelBuffer& image) {
    ColorData temp1;
    ColorData temp2;
    const ColorData* pixels2 = image.data();
    for (int i = 0; i < pixels_.size(); i++) {
        temp1 = pixels_[i];
        temp2 = pixels2[i];
        if (temp1.red() != temp2.red() ||
            temp1.green() != temp2.green() ||
            temp1.blue() != temp2.blue())
            return false;
    }
    return true;
}
}  /* namespace image_tools */
