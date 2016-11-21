/*******************************************************************************
 * Name            : blur_kernel.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of BlurKernel class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/blur_kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

BlurKernel::BlurKernel(float blur_amount, int dimension)
    // utilizes adjusting formula that takes blur_amount range into account
    : Kernel(sqrt(blur_amount) / sqrt(20.0), dimension) {

    BlurKernel::InitKernel();
}
BlurKernel::~BlurKernel(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

/* 
 * init_kernel() constructs the blur kernel for this class.
 *
 * The halfway point through the kernel will have all 1's in that row/column. 
 * The number of 1's decreases by two (one from both ends), down to 1 1 in 
 * first/last row/column. See example for a dimension 5 blur kernel: 
 *
 * 00100
 * 01110
 * 11111
 * 01110
 * 00100
 */

void BlurKernel::InitKernel(void) {
    int i;
    int factor = dimension_;

    /* The following for loop initializes factor. Factor will equal the number of 1's 
     * in our kernel, and will be used to scale the weights so their sum equals 1. 
     */
    for (i = dimension_ - 2; i >= 1; i-= 2) {
        factor += i * 2;
    }

    int mid_index = dimension_ / 2;
    // all mid_index row/col positions = weight_val
    for (i = 0; i < dimension_; i++) {
        weight(i, mid_index, 1.0 / factor);
        weight(mid_index, i, 1.0 / factor);
    }
    float weight_val;
    int edge_index = dimension_ - 1;
    int j, zero_pad;
    for (j = mid_index + 1, zero_pad = 1; j < dimension_; zero_pad++, j++) {
	/* blur kernel is symmetric across both axes intersecting at the middle pixel:
	 * only iterating through one quadrant of the kernel to set all relevant pixel weights.
	 */ 
        for (i = mid_index + 1; i < dimension_; i++) {
            /* if i is more than zero_pad from the edge, the weight at (i, j),
             * as well as all of its reflections about the axes through the middle
             * pixel, will be set to weight_val. Otherwise, weight is 0.0.
	     */
            if (i < dimension_ - zero_pad) {
                weight_val = 1.0 / factor;
            } else {
                weight_val = 0.0;
            }
            weight(edge_index - i, j, weight_val);
            weight(i, j, weight_val);
            weight(edge_index - i, edge_index - j, weight_val);
            weight(i, edge_index - j, weight_val);
        }
    }
}
}  // namespace image_tools
