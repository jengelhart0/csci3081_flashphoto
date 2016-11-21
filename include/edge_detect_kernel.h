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

#ifndef INCLUDE_EDGE_DETECT_KERNEL_H_
#define INCLUDE_EDGE_DETECT_KERNEL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "include/kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class implements an edge detection kernel for use with a ConvolutionFilter.        
 */

class EdgeDetectKernel : public Kernel {
 public:
     EdgeDetectKernel(void);
     virtual ~EdgeDetectKernel(void);

     virtual void InitKernel(void);
 private:
     float middle_val_;
     float other_val_;
};
}  // namespace image_tools
#endif  // INCLUDE_EDGE_DETECT_KERNEL_H_

