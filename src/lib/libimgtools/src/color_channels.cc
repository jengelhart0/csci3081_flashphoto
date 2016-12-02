/*******************************************************************************
 * Name            : color_channels.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of ColorChannels class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "include/color_channels.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
ColorChannels::ColorChannels(PixelBuffer *canvas)
    : Filter(canvas) {}

ColorChannels::~ColorChannels(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void ColorChannels::ModifyPixel(int x, int y) {
    PixelBuffer* canvas = Filter::get_canvas();
    ColorData pixel = canvas->get_pixel(x, y);
    float colors[] = { pixel.red(), pixel.green(), pixel.blue() };
    float new_colors[] = { pixel.red()*red_,
                           pixel.green()*green_,
                           pixel.blue()*blue_ };
    canvas->set_pixel(x, y, (ColorData(new_colors[0], new_colors[1],
                                       new_colors[2], pixel.alpha())));
}

}    // namespace image_tools
