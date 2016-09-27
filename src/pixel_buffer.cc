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

void PixelBuffer::copyPixelBuffer(const PixelBuffer * sourceBuffer,
                                  PixelBuffer * destinationBuffer)
{
  if (destinationBuffer->width() != sourceBuffer->width()
      || destinationBuffer->height() != sourceBuffer->height())
  {
    cerr << "copyPixelBuffer: " << "dimension mismatch" << endl;

  }
  else
  {
    memcpy ( (void*)destinationBuffer->pixels_, (void*) sourceBuffer->pixels_,
             sizeof(ColorData)*destinationBuffer->height()*destinationBuffer->width() );

  }

}


PixelBuffer* PixelBuffer::duplicatePixelBuffer(const PixelBuffer* sourceBuffer)
{
  PixelBuffer* d = new PixelBuffer(sourceBuffer->width(),
                                   sourceBuffer->height(), sourceBuffer->background_color());
  PixelBuffer::copyPixelBuffer(sourceBuffer, d);
  return d;
}

}  // namespace image_tools
