/*******************************************************************************
 * Name            : filter.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of Filter class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "include/filter.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

Filter::Filter(PixelBuffer *canvas) 
    : canvas_(canvas) {}

Filter::~Filter(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

PixelBuffer *Filter::get_canvas(void) { return canvas_; }
void Filter::set_canvas(PixelBuffer *new_canvasptr) { canvas_ = new_canvasptr; } 

void Filter::ApplyFilter() {
    int height = canvas_->height();
    int width = canvas_->width();
    int y, x;
    for(y = 0; y < height; y++) {
	for(x = 0; x < width; x++) {
	    ModifyPixel(x, y);
	}
    }
}
}    // namespace image_tools
