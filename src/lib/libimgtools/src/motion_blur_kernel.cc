/*******************************************************************************
 * Name            : motion_blur_kernel.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of MotionBlurKernel class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/motion_blur_kernel.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

MotionBlurKernel::MotionBlurKernel(float motion_blur_amount,
                                   enum UICtrl::MotionBlurDirection direction,
                                   int dim)
    : Kernel(sqrt(motion_blur_amount) / 10, dim),
      direction_(direction) {

    MotionBlurKernel::InitKernel();
}
MotionBlurKernel::~MotionBlurKernel(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* 
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

void MotionBlurKernel::InitKernel(void) {
    int dim = dimension();
    int direction = static_cast<int>(direction_);
    int directions[4][2] = { {0, 1},
                             {1, 0},
                             {1, 1},
                             {-1, 1} };
    int starts[4][2] = { {dim / 2, 0},
                         {0, dim / 2},
                         {0, 0},
                         {dim, 0} };
    float weight_val = 1.0 / dim;

    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            weight(i, j, 0.0);
        }
    }

    i = starts[direction][0];
    j = starts[direction][1];
    int k = 0;
    // the number of non-zero weights is always equal to dim.
    // having started at the appropriate starts array coords, we use
    // the corresponding directions selection to increment on each iteration
    while (k < dim) {
        weight(i, j, weight_val);
        i += directions[direction][0];
        j += directions[direction][1];
        k++;
    }
}
}  // namespace image_tools

