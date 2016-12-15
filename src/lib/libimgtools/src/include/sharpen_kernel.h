/*******************************************************************************
 * Name            : sharpen_kernel.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for SharpenKernel class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_KERNEL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_KERNEL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "./kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class implements an sharpen kernel for use with a ConvolutionFilter.        
 * init_kernel() constructs the sharpen kernel for this class.
 * The middle kernel coord will be set to the square of the
 * kernel's dim. This is one greater than the sum of all other coord values. 
 * All other coords set to -1. See example: 
 *
 * -2 -2 -2
 * -2 17 -2
 * -2 -2 -2
 */

class SharpenKernel : public Kernel {
 public:
     explicit SharpenKernel(float sharpen_amount);
     virtual ~SharpenKernel(void);

     virtual void InitKernel(void);
 private:
     float middle_val_; /**< Represents pixel being modified. */
     float other_val_; /**< Sum of middle and other pixels will be 1. */
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SHARPEN_KERNEL_H_
