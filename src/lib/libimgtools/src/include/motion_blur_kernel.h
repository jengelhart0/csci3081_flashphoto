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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_KERNEL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_KERNEL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/filter_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class implements a motion blur kernel for use with a ConvolutionFilter.
 * init_kernel() constructs the motion blur kernel for this class.
 *
 * The directions/starts arrays are used to implement the line of
 * weights required for a given direction. See example below:
 *
 * .2 0 0 0 0
 * 0 .2 0 0 0
 * 0 0 .2 0 0
 * 0 0 0 .2 0
 * 0 0 0 0 .2        
 */

class MotionBlurKernel : public Kernel {
 public:
     MotionBlurKernel(float motion_blur_amount,
                      enum UICtrl::MotionBlurDirection direction,
                      int dimension);
     virtual ~MotionBlurKernel(void);
     /**
      * @brief Initializes kernel for MotionBlurKernel.
      */
     virtual void InitKernel(void);
 private:
     /** Blur direction
      *  Represents the direction of the motion blurring effect
      */
     enum UICtrl::MotionBlurDirection direction_;
};
}  // namespace image_tools
#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_MOTION_BLUR_KERNEL_H_
