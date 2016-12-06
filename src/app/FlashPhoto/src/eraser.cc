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
#include "eraser.h"
#include "cmath"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Eraser::Eraser(void) : Tool(21, 21) {
    CalculateMask();
}

Eraser::~Eraser(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Eraser::CalculateMask(void) {
    float center_x = 10.0;
    float center_y = 10.0;
    float current_distance = sqrt(pow(center_x, 2.0) + pow(center_y, 2.0));
    float x_distance = center_x;
    float y_distance = center_y;
    float new_mask[21*21];
    int length = Tool::length();
    int height = Tool::height();
    int index = 0;
    for (int i = 0; i < height; i++) {
        y_distance = std::abs(i - center_y);
        for (int j = 0; j < length; j++) {
            x_distance = std::abs(j - center_x);
            current_distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
            index = j + (i*length);
            if (current_distance < 10.5)
                new_mask[index] = 1.0;
            else
                new_mask[index] = 0.0;
        }
    }
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
