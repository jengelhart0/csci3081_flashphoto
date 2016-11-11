/*******************************************************************************
 * Name            : kernel.cc
 * Project         : FlashPhoto
 * Module          : image_tools
 * Description     : Implementation of Kernel class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/10/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/kernel.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

int Kernel::get_dimension(void) { return dimension_; }
float Kernel::get_weight(int index) { return *(data_ + index); }

void Kernel::set_kernel_value(int position, float value) {
    if(!( (position < dimension_ - 1) || (position < 0) )) {
	data_[position] = value;
    } else {
	std::cerr << "set_kernel_value() position out of bounds: " << position << std::endl;
    } 
}

void Kernel::init_kernel(int dimension) {
    dimension_ = dimension;
    data_ = new float[dimension]; 
}
} // namespace image_tools
