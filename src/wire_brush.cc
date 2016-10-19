/*******************************************************************************
 * Name            : wire_brush.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of WireBrush class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 10/18/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "include/wire_brush.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
WireBrush::WireBrush(void) : Tool(35, 35) {
    CalculateMask();
}

WireBrush::~WireBrush(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void WireBrush::CalculateMask(void) {
    int height = Tool::height();
    int length = Tool::length();
    unsigned int seed;
    int size = height * length;
    float new_mask[35*35];
    for (int i = 0; i < size; i++) {
        if ((rand_r(&seed) % 100) <= 10) {
            new_mask[i] = 1.0;
        } else {
            new_mask[i] = 0.0;
        }
    }
    Tool::mask(new_mask);
}
}  // namespace image_tools
