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
    canvas_height_ = canvas.height();
    canvas_width_ = canvas.width();
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
    int edge_checked_i, edge_checked_j;
    int kernel_x, kernel_y;

    for (i = starting_y, kernel_y = 0; i <= ending_y; i++, kernel_y++) {
        // 'reflects' over/underflow values (e.g., i = -2 -> edge_checked_i = 2; 
        // i = canvas_width_ -> edge_checked_i = canvas_width-1)
        if (i >= 0 && i < canvas_height_) {
            edge_checked_i = i;
        } else { 
            edge_checked_i = (canvas_height_ - (i % (canvas_height_ - 1))) % canvas_height_;
        }
        for (j = starting_x, kernel_x = 0; j <= ending_x; j++, kernel_x++) {                
            // see edge_checked_i note above
            if (j >= 0 && j < canvas_width_) {
                edge_checked_j = j;    
            } else {
                edge_checked_j = (canvas_width_ - (j % (canvas_width_ - 1))) % canvas_width_;
            } 
            // aggregates new pixel values as we iterate through canvas/kernel
            modified_pixel = modified_pixel
                   + (canvas_copy_.get_pixel(edge_checked_j, edge_checked_i)
                   * kernel_->weight(kernel_x, kernel_y));
        }
    }

    ColorData new_pixel = (modified_pixel - old_pixel)
                        * kernel_->filter_amount() + old_pixel;
    // don't need any alterations the * overload makes to alpha
    new_pixel.alpha(old_pixel.alpha());
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

