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
#include "include/kernel.h"
#include "include/filter.h"

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

      enum Type {UNASSIGNED, BLUR, MOTION_BLUR, SHARPEN, EDGE_DETECT};

      ConvolutionFilter(PixelBuffer *canvas);
      virtual ~ConvolutionFilter(void);

      virtual void ApplyFilter(void);
      virtual void ModifyPixel(int x, int y);

      void type(Type type);
      Type type(void);

      void kernel(Kernel *new_kernel); 

  private:

      void set_canvas_copy(PixelBuffer &canvas);

      Type type_;
      Kernel *kernel_;
      PixelBuffer canvas_copy_;
};
} // namespace image_tools

#endif // INCLUDE_CONVOLUTION_FILTER_H
