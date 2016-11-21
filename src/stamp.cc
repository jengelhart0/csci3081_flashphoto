/*******************************************************************************
 * Name            : stamp.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Stamp class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/09/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/stamp.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Stamp::Stamp(PixelBuffer* stamp) : Tool(stamp->width(), stamp->height()),
                                   stamp_(stamp) {
    CalculateMask();
}

Stamp::~Stamp(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Stamp::CalculateMask(void) {
    int length = Tool::length();
    int height = Tool::height();
    float new_mask[length*height];
    int index = 0;
    ColorData px;
    ColorData background = stamp_->background_color();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < length; x++) {
            index = x + (y*length);
            px = stamp_->get_pixel(x, y);
            new_mask[index] = px.alpha();
        }
    }
    Tool::mask(new_mask);
}

void Stamp::Draw(int x, int y,
    float red, float green, float blue,
    PixelBuffer* display) {
    // Mask-related variables
    int length = Tool::length();
    int height = Tool::height();
    float* mask = Tool::mask();
    // Canvas-related variables
    int max_y = display->height();
    int max_x = display->width();
    int starting_x = x - (length / 2);
    int starting_y = y - (height / 2);
    int cur_x = starting_x;
    int cur_y = starting_y;
    int index = 0;
    float intensity = 1.0;
    ColorData temp_color;
    for (int i = 0; i < height; i++) {
        cur_y = i + starting_y;
        for (int j = 0; j < length; j++) {
            cur_x = j + starting_x;
            index = j + (i*length);
            intensity = mask[index];
            temp_color = stamp_->get_pixel(j, i);
            if (intensity == 1.0 &&
                cur_x < max_x && cur_x >= 0 &&
                cur_y < max_y && cur_y >= 0) {
                display->set_pixel(cur_x, cur_y, temp_color);
            }
        }
    }
}
}  // namespace image_tools
