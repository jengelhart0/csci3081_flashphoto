/*******************************************************************************
 * Name            : kernel.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Kernel class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/10/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef INCLUDE_KERNEL_H_
#define INCLUDE_KERNEL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class implements a Kernel for ConvolutionFilters.        
 */

class Kernel {
  public:

      int get_dimension(void);
      float get_weight(int index);
      void init_kernel(int dimension);
      void set_kernel_value(int position, float value);

  private:
      int dimension_;
      float *data_;
};
} // namespace image_tools

#endif // INCLUDE_KERNEL_H
