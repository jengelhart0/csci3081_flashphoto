/*******************************************************************************
 * Name            : convolution_filter.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of ConvolutionFilter class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/convolution_filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
ConvolutionFilter::ConvolutionFilter(PixelBuffer *canvas)
    : Filter(canvas),
      type_(UNASSIGNED) {} 

ConvolutionFilter::~ConvolutionFilter(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void ConvolutionFilter::ModifyPixel(int x, int y, PixelBuffer *canvas_copy) { ///CONFUSING SET-UP in PixelBuffer! 
									      ///Verify you have actually made a copy aren't pointing to same canvas!!
    // kernel coordinate parameters on canvas
    int kernel_dim = kernel_->dimension();		 
    int starting_x = x - (kernel_dim / 2);
    int starting_y = y - (kernel_dim / 2);
    int ending_x = starting_x + kernel_dim - 1;
    int ending_y = starting_y + kernel_dim - 1;

    PixelBuffer *canvas = get_canvas();
    ColorData old_pixel = canvas->get_pixel(x, y);
    ColorData modified_pixel = canvas->get_pixel(x, y);

    int i, j;
    int current_x, current_y;

    for(i = starting_y, current_y = 0; i <= ending_y; i++, current_y++) {
	for(j = starting_x, current_x = 0; j <= ending_x; j++, current_x++) {
	    // use overloaded ColorData operators to calculate modified_pixel values
	    modified_pixel = modified_pixel + (canvas->get_pixel(i, j) * kernel_->weight(current_x, current_y));    
	}
    }

    ColorData new_pixel = (modified_pixel - old_pixel) * kernel_->filter_amount() + old_pixel; 

    canvas_copy->set_pixel(x, y, new_pixel);
} 

void ConvolutionFilter::ApplyFilter(void) {

    PixelBuffer *canvas = get_canvas();
    PixelBuffer canvas_copy = *canvas;

    int height = canvas->height();
    int width = canvas->width();
    int y, x;
    for(y = 0; y < height; y++) {
	for(x = 0; x < width; x++) {
	    ModifyPixel(x, y, &canvas_copy);
	}
    }
    Filter::set_canvas(&canvas_copy);
}

void ConvolutionFilter::kernel(Kernel *new_kernel) { kernel_ = new_kernel; }

void ConvolutionFilter::type(Type type) {
    type_ = type;
}

ConvolutionFilter::Type ConvolutionFilter::type(void) { return type_; }

} // namespace image_tools

