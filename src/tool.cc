/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Tool class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/tool.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Tool::Tool(int length, int height) {
    int i = 0;
    height_ = height;
    length_ = length;
    mask_ = new float[height*length];
}

Tool::~Tool(void) {
    if (mask_) { delete mask_; }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Tool::mask(float new_mask[]) {
    int index = 0;
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < length_; j++) {
            index = j + (i*length_);
            mask_[index] = new_mask[index];
        }
    }
}

void Tool::Draw(int x, int y,
    float red, float green, float blue,
    PixelBuffer* display) {
    // Set lower and upper bounds
    int starting_x = x - (length_ / 2);
    int starting_y = x - (height_ / 2);
    int max_y = length_;
    int max_x = length_;
    // Check lower bounds, adjust upper bounds if pixel mask is too close
    // to left and/or upper edge
    if (starting_x < 0) {
        max_x = starting_x + length_;
        starting_x = 0;
    }
    if (starting_y < 0) {
        max_y = starting_y + height_;
        starting_y = 0;
    }
    // Check upper bound, adjust if too close to right and/or lower edge
    int canvas_length = display->width();
    int canvas_height = display->height();
    if ((starting_x + length_) > canvas_length) {
        max_x = canvas_length - starting_x;
    }
    if ((starting_y + height_) > canvas_height) {
        max_y = canvas_height - starting_y;
    }
    // Current position
    int cur_x = starting_x;
    int cur_y = starting_y;

    int index = 0;
    float intensity = 1.0;
    ColorData color = ColorData(red, green, blue);
    ColorData cur_pixel;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            cur_x = j + starting_x;
            cur_y = i + starting_y;
            index = cur_x + (cur_y*length_);
            intensity = mask_[index];

            cur_pixel = display->get_pixel(cur_x, cur_y);
            ColorData color = (color*intensity) + (cur_pixel*(1.0 - intensity));
            display->set_pixel(cur_x, cur_y, color);
        }
    }
}

}  // namespace image_tools
