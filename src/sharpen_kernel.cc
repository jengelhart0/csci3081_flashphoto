/*******************************************************************************
 * Name            : sharpen_kernel.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of SharpenKernel class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/sharpen_kernel.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

SharpenKernel::SharpenKernel(float sharpen_amount)
    : Kernel(sharpen_amount / 100, 3),
      middle_val_(9.0),
      other_val_(-1.0) {

    SharpenKernel::InitKernel();
}
SharpenKernel::~SharpenKernel(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* 
 * init_kernel() constructs the sharpen kernel for this class.
 *
 * The middle kernel coord will be set to the square of the
 * kernel's dimension. This is one greater than the sum of all other coord values. 
 * All other coords set to -1. See example: 
 *
 * -2 -2 -2
 * -2 17 -2
 * -2 -2 -2
 */

void SharpenKernel::InitKernel(void) {
    int j, i;
    for (j = 0; j < dimension_; j++) {
        for (i = 0; i < dimension_; i++) {
            weight(i, j, other_val_);
        }
    }
    weight(dimension_ / 2, dimension_ / 2, middle_val_);
}
}  // namespace image_tools
