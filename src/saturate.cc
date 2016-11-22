/*******************************************************************************
 * Name            : saturate.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of Saturate class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "include/saturate.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Saturate::Saturate(PixelBuffer *canvas)
    : Filter(canvas) {}

Saturate::~Saturate(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Saturate::ModifyPixel(int x, int y) {
    PixelBuffer* canvas = Filter::get_canvas();
    ColorData pixel = canvas->get_pixel(x, y);
    /* Make a grayscale copy of canvas */
    float gray = pixel.luminance();
    ColorData gray_image(gray, gray, gray, pixel.alpha());
    /* Interpolate between old pixel and gray pixel */
    ColorData new_image = (pixel*saturation_) + (gray_image*(1 - saturation_));
    canvas->set_pixel(x, y, new_image);
}

}    // namespace image_tools
