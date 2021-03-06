/*******************************************************************************
 * Name            : edge_detect_kernel.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of EdgeDetectKernel class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/edge_detect_kernel.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

EdgeDetectKernel::EdgeDetectKernel(void)
    : Kernel(3),
      middle_val_(16.0),
      other_val_(-2.0) {

    EdgeDetectKernel::InitKernel();
}
EdgeDetectKernel::~EdgeDetectKernel(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* 
 * init_kernel() constructs the edge detect kernel for this class.
 *
 * The middle kernel coord will be set to one less than the square of the
 * kernel's dim. All other coords set to -1. See example for a 
 * dim 3 kernel: 
 *
 * -1-1-1
 * -1 8-1
 * -1-1-1
 */

void EdgeDetectKernel::InitKernel(void) {
    int j, i;
    int dim = dimension();
    for (j = 0; j < dim; j++) {
        for (i = 0; i < dim; i++) {
            weight(i, j, other_val_);
        }
    }
    weight(dim / 2, dim / 2, middle_val_);
}
}  // namespace image_tools









