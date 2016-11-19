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
      canvas_copy_(*canvas),
      canvas_width_(canvas->width()),
      canvas_height_(canvas->height()) {}

ConvolutionFilter::~ConvolutionFilter(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void ConvolutionFilter::set_canvas_copy(const PixelBuffer &canvas) {
    canvas_copy_ = canvas;
}

void ConvolutionFilter::ModifyPixel(int x, int y) {
    int kernel_dim = kernel_->dimension();

    int starting_x = x - (kernel_dim / 2);
    int starting_y = y - (kernel_dim / 2);

    int ending_x = starting_x + kernel_dim - 1;
    int ending_y = starting_y + kernel_dim - 1;

    PixelBuffer *canvas = get_canvas();

    ColorData old_pixel = canvas_copy_.get_pixel(x, y);
    ColorData modified_pixel = ColorData(0, 0, 0, 0);

    int i, j;
    int kernel_x, kernel_y;

    for (i = starting_y, kernel_y = 0; i <= ending_y; i++, kernel_y++) {
        for (j = starting_x, kernel_x = 0; j <= ending_x; j++, kernel_x++) {
            // addition/modulus handles negative/out-of-bounds values
            modified_pixel = modified_pixel
               + (canvas_copy_.get_pixel((j + canvas_width_) % canvas_width_,
                                         (i + canvas_height_) % canvas_height_)
               * kernel_->weight(kernel_x, kernel_y));
        }
    }

    ColorData new_pixel = (modified_pixel - old_pixel)
                        * kernel_->filter_amount() + old_pixel;
    canvas->set_pixel(x, y, new_pixel);
}

void ConvolutionFilter::ApplyFilter(void) {
    PixelBuffer *canvas = get_canvas();
    ConvolutionFilter::set_canvas_copy(*canvas);
    int y, x;
    for (y = 0; y < canvas_height_; y++) {
        for (x = 0; x < canvas_width_; x++) {
            ModifyPixel(x, y);
        }
    }
}

void ConvolutionFilter::kernel(Kernel *new_kernel) { kernel_ = new_kernel; }

}  // namespace image_tools

