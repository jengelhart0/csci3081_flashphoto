/*******************************************************************************
 * Name            : blur.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Blur class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef INCLUDE_BLUR_H_
#define INCLUDE_BLUR_H_
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
 * @brief This class implements a blur kernel for use with a ConvolutionFilter and the Blur tool.        
 */

class BlurKernel : public Kernel {
  public:
      BlurKernel(float blur_amount, int dimension);
      virtual ~BlurKernel(void);
 
      virtual void InitKernel(void);
};
} // namespace image_tools
#endif // INCLUDE_BLUR_H
