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
 * @brief This abstract class is a base for the different types of kernels for ConvolutionFilters.        
 */

class Kernel {
 public:
     Kernel(float filter_amount, int dimension);
     explicit Kernel(int dimension);
     virtual ~Kernel(void);

     float weight(int x, int y);
     int dimension(void);
     float filter_amount(void);

 protected:
     virtual void InitKernel(void) = 0;
     void weight(int x, int y, float value);
     float filter_amount_;
     int dimension_;

 private:
     void init_data(void);

     float *data_;
};
}  // namespace image_tools

#endif  // INCLUDE_KERNEL_H_
