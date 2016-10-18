/*******************************************************************************
 * Name            : eraser.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Eraser class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/eraser.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Eraser::Eraser(void) : Tool(21, 21) {
    calculate_mask();
}

Eraser::~Eraser(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Eraser::calculate_mask(void) {
    int size = Tool::height() * Tool::length();
    float new_mask[size];
    for (int i = 0; i < size; i++) { new_mask[i] = 1.0; }
    Tool::mask(new_mask);
}

void Eraser::Draw(int x, int y,
    float red, float green, float blue,
    PixelBuffer* display) {
    ColorData original_color = display->background_color();
    Tool::Draw(x, y,
        original_color.red(), original_color.green(), original_color.blue(),
        display);
}
}  // namespace image_tools
