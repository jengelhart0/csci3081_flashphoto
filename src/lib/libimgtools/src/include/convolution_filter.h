/*******************************************************************************
 * Name            : convolution_filter.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for ConvolutionFilter class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef INCLUDE_CONVOLUTION_FILTER_H_
#define INCLUDE_CONVOLUTION_FILTER_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "kernel.h"
#include "filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This extension of Filter overrides the base ApplyFilter() to allow to 
 * CreateKernel(). It also implements ModifyPixel() for all ConvolutionFilters.
 */

class ConvolutionFilter : public Filter {
 public:
     explicit ConvolutionFilter(PixelBuffer *canvas);
     virtual ~ConvolutionFilter(void);
     /**
      * @brief Modifies each pixel in canvas by reading from canvas copy
      * for all pixels in kernel and applying modified pixel to canvas
      */ 
     virtual void ModifyPixel(int x, int y);

     void kernel(Kernel *new_kernel);

 private:
      Kernel *kernel_; /**< kernel that provides unique characteristics for a filter */
      PixelBuffer canvas_copy_; /**< needed so we are reading from an uncorrupted canvas */
      int canvas_width_;
      int canvas_height_;
};
}  // namespace image_tools

#endif  // INCLUDE_CONVOLUTION_FILTER_H_
