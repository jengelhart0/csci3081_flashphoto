/*******************************************************************************
 * Name            : quantize.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of Quantize class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/quantize.h"
#include <math.h>
#include <iostream>
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Quantize::Quantize(PixelBuffer *canvas)
    : Filter(canvas) {}

Quantize::~Quantize(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Quantize::ModifyPixel(int x, int y) {
    PixelBuffer* canvas = Filter::get_canvas();
    ColorData pixel = canvas->get_pixel(x, y);
    float factor = 1.0 / (static_cast<float>(bins_) - 1.0);
    float colors[] = { pixel.red(), pixel.green(), pixel.blue() };
    float new_colors[3];
    float temp_diff = 1.0;
    float smallest_diff = 1.0;
    float bin_number = 0;
    for (int i = 0; i < 3; i++) {
        smallest_diff = 1.0;
        for (float j = 0; j < bins_; j+=1.0) {
            temp_diff = fabs(colors[i] - (factor*j));
            if (temp_diff < smallest_diff) {
                bin_number = j;
                smallest_diff = temp_diff;
            }
        }
        new_colors[i] = (factor * bin_number);
    }
    canvas->set_pixel(x, y, ColorData(new_colors[0], new_colors[1],
                                      new_colors[2], pixel.alpha()));
}

}    // namespace image_tools
