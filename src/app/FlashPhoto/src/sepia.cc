/*******************************************************************************
 * Name            : sepia.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of Sepia class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "sepia.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Sepia::Sepia(PixelBuffer *canvas)
    : Filter(canvas) {}

Sepia::~Sepia(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Sepia::ModifyPixel(int x, int y) {
    PixelBuffer* canvas = Filter::get_canvas();
    ColorData pixel = canvas->get_pixel(x, y);

    /* Citation for color calculations */
    /***************************************************************************
	*    Title:         How do I... Convert images to grayscale and sepia tone 
    *                   using C#?
	*    Author:        Smith, Zach
	*    Date:          Aug 21, 2007
	*    Availability:  http://http://www.techrepublic.com
	***************************************************************************/
    float red = (pixel.red() * .6) + (pixel.green() *.769) +
                (pixel.blue() * .189);
    float green = (pixel.red() * .349) + (pixel.green() *.686) +
                  (pixel.blue() * .168);
    float blue = (pixel.red() * .272) + (pixel.green() *.534) +
                 (pixel.blue() * .131);

    ColorData color(red, green, blue, pixel.alpha());
    canvas->set_pixel(x, y, color);
}

}    // namespace image_tools
