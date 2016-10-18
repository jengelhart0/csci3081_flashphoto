/*******************************************************************************
 * Name            : caligraphy_pen.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of CaligraphyPen class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/caligraphy_pen.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
CaligraphyPen::CaligraphyPen(void) : Tool(5, 15) {
    calculate_mask();
}

CaligraphyPen::~CaligraphyPen(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void CaligraphyPen::calculate_mask(void) {
    int size = Tool::length() * Tool::height();
    float new_mask[size];
    for (int i = 0; i < size; i++) { new_mask[i] = 1.0; }
    Tool::mask(new_mask);
}
}  // namespace image_tools
