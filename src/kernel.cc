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

Kernel::Kernel(float filter_amount, int dimension)
    : filter_amount_(filter_amount),
      dimension_(dimension) {

    init_data();
}
Kernel::Kernel(int dimension) : Kernel::Kernel(1.0, dimension) {}
Kernel::~Kernel(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

int Kernel::dimension(void) { return dimension_; }

float Kernel::weight(int x, int y) { return *(data_ + (y * dimension_ + x)); }

float Kernel::filter_amount(void) { return filter_amount_; }

void Kernel::weight(int x, int y, float value) {
    int position = y * dimension_ + x;
    if(!( (position < dimension_ - 1) || (position < 0) )) {
	data_[position] = value;
    } else {
	std::cerr << "set_kernel_value() coordinates out of bounds. X: " << x << " Y: " << y << std::endl;
    } 
}

void Kernel::init_data(void) {
    data_ = new float[dimension_ * dimension_]; 
}
} // namespace image_tools
