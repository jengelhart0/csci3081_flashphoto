/*******************************************************************************
 * Name            : threshold.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of Threshold class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "include/threshold.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Threshold::Threshold(PixelBuffer *canvas)
    : Filter(canvas) {}

Threshold::~Threshold(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Threshold::ModifyPixel(int x, int y) {
    PixelBuffer* canvas = Filter::get_canvas();
    ColorData pixel = canvas->get_pixel(x, y);
    float colors[] = { pixel.red(), pixel.green(), pixel.blue() };
    float new_colors[3];
    for (int i = 0; i < 3; i++) {
        if (colors[i] < threshold_)
            new_colors[i] = 0.0;
        else
            new_colors[i] = 1.0;
    }
    canvas->set_pixel(x, y, (ColorData(new_colors[0], new_colors[1],
                                       new_colors[2], pixel.alpha())));
}

}    // namespace image_tools
