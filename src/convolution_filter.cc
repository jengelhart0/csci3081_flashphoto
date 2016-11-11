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
      type_(UNASSIGNED),
      kernel_() {} 

ConvolutionFilter::~ConvolutionFilter(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void ConvolutionFilter::ModifyPixel(int x, int y, PixelBuffer *canvas_copy) { ///CONFUSING SET-UP in PixelBuffer! 
									      ///Verify you have actually made a copy aren't pointing to same canvas!!
    // kernel coordinate parameters on canvas
    int kernel_dim = kernel_->get_dimension();		 
    int starting_x = x - (kernel_dim / 2);
    int starting_y = y - (kernel_dim / 2);
    int ending_x = starting_x + kernel_dim - 1;
    int ending_y = starting_y + kernel_dim - 1;

    PixelBuffer *canvas = get_canvas();
    ColorData target_pixel = canvas->get_pixel(x, y);

    int i, j;
    int k = 0;

    for(i = starting_y; i <= ending_y; i++) {
	for(j = starting_x; j <= ending_x; j++, k++) {
	    // use overloaded ColorData operators to calculate target_pixel values
	    target_pixel = target_pixel + (canvas->get_pixel(i, j) * kernel_->get_weight(k));    
	}
    }
    canvas_copy->set_pixel(x, y, target_pixel);
} 

void ConvolutionFilter::ApplyFilter(void) {
 //   CreateKernel(); <-- replace with call to kernelfactory
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
    set_canvas(&canvas_copy);
}

void ConvolutionFilter::set_type(Type type) {
    type_ = type;
}

ConvolutionFilter::Type ConvolutionFilter::get_type(void) { return type_; }

} // namespace image_tools

