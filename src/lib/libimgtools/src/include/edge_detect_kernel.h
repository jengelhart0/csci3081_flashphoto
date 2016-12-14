/*******************************************************************************
 * Name            : edge_detect_kernel.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for EdgeDetectKernel class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_KERNEL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_KERNEL_H_
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
 * @brief This class implements an edge detection kernel for use with a ConvolutionFilter.     
 * The middle kernel coord will be set to one less than the square of the
 * kernel's dim. All other coords set to -1. See example for a 
 * dim 3 kernel: 
 *
 * -1-1-1
 * -1 8-1
 * -1-1-1   
 */

class EdgeDetectKernel : public Kernel {
 public:
     EdgeDetectKernel(void);
     virtual ~EdgeDetectKernel(void);
     /** 
      * @brief Constructs the Edge detect kernel for this class.
      */
     virtual void InitKernel(void);
 private:
     float middle_val_;  /**< Represents pixel to be modified. */
     float other_val_;  //!< Sum of middle and other pixels in kernel
                        //!< equal to 0. */
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_EDGE_DETECT_KERNEL_H_

