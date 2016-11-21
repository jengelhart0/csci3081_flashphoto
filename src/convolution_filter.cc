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
//    std::cout << canvas->width() << " " << canvas_width_ << " " << canvas->height() << " " << canvas_height_ << std::endl;

    ColorData old_pixel = canvas_copy_.get_pixel(x, y);
    ColorData modified_pixel = ColorData(0, 0, 0, 0);
//    ColorData modified_pixel = canvas_copy_.get_pixel(x, y);
//    std::cout << "old_pixel: r: " << old_pixel.red() << " g: " << old_pixel.green() << " b: " << old_pixel.blue() << " a: " << old_pixel.alpha() << std::endl;

    int i, j;
    int edge_checked_i, edge_checked_j;
    int kernel_x, kernel_y;

    for (i = starting_y, kernel_y = 0; i <= ending_y; i++, kernel_y++) {
        if (i >= 0 && i < canvas_height_) {
            edge_checked_i = i;
        } else { 
            edge_checked_i = (canvas_height_ - (i % (canvas_height_ - 1))) % canvas_height_;
        }
//        std::cout << "i: " << i << " " << edge_checked_i << std::endl;

        for (j = starting_x, kernel_x = 0; j <= ending_x; j++, kernel_x++) {                
                    // addition/modulus handles negative/out-of-bounds values
            if (j >= 0 && j < canvas_width_) {
                edge_checked_j = j;    
            } else {
                edge_checked_j = (canvas_width_ - (j % (canvas_width_ - 1))) % canvas_width_;
            }  
//            std::cout << "j: " << j << " " << edge_checked_j << std::endl;

            modified_pixel = modified_pixel
                   + (canvas_copy_.get_pixel((edge_checked_j + canvas_width_) % canvas_width_,
                                             (edge_checked_i + canvas_height_) % canvas_height_)
                   * kernel_->weight(kernel_x, kernel_y));
//                     std::cout << "modified_pixel: r: " << modified_pixel.red() << " g: " << modified_pixel.green() << " b: " << modified_pixel.blue() << " a: " << modified_pixel.alpha() << std::endl;
        }
    }
    ColorData new_pixel = (modified_pixel - old_pixel)
                        * kernel_->filter_amount() + old_pixel;
    new_pixel.alpha(old_pixel.alpha());

//    std::cout << "new_pixel: r: " << new_pixel.red() << " g: " << new_pixel.green() << " b: " << new_pixel.blue() << " a: " << new_pixel.alpha() << std::endl;
    canvas->set_pixel(x, y, new_pixel);
//    canvas->set_pixel(x, y, modified_pixel);
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

