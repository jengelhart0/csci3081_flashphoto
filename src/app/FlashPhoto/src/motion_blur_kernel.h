/*******************************************************************************
 * Name            : motion_blur_kernel.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for MotionBlurKernel class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef INCLUDE_MOTION_BLUR_KERNEL_H_
#define INCLUDE_MOTION_BLUR_KERNEL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "lib/libimgtools/src/include/kernel.h"
#include "filter_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class implements a motion blur kernel for use with a ConvolutionFilter.        
 */

class MotionBlurKernel : public Kernel {
 public:
     MotionBlurKernel(float motion_blur_amount,
                      enum UICtrl::MotionBlurDirection direction,
                      int dimension);
     virtual ~MotionBlurKernel(void);
     virtual void InitKernel(void);
 private:
     enum UICtrl::MotionBlurDirection direction_;
};
}  // namespace image_tools
#endif  // INCLUDE_MOTION_BLUR_KERNEL_H_
