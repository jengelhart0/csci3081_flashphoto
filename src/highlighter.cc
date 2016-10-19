/*******************************************************************************
 * Name            : highlighter.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Highlighter class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 10/18/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/highlighter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Highlighter::Highlighter(void) : Tool(5, 15) {
    CalculateMask();
}

Highlighter::~Highlighter(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Highlighter::CalculateMask(void) {
    int size = Tool::length() * Tool::height();
    float new_mask[5*15];
    for (int i = 0; i < size; i++) { new_mask[i] = 0.4; }
    Tool::mask(new_mask);
}

void Highlighter::Draw(int x, int y,
    float red, float green, float blue,
    PixelBuffer* display) {
    // Set lower and upper bounds

    /*
     * TODO: 800 must become a constant in SOME file. This is the canvas
     *       canvas dimensions so it needs to be available throughout the program
     */
    y = 800 - y;
    int length = Tool::length();
    int height = Tool::height();
    float* mask = Tool::mask();
    int starting_x = x - (length / 2);
    int starting_y = y - (height / 2);
    int max_y = height;
    int max_x = length;
    // Check lower bounds, adjust upper bounds if pixel mask is too close
    // to left and/or upper edge
    if (starting_x < 0) {
        max_x = starting_x + length;
        starting_x = 0;
    }
    if (starting_y < 0) {
        max_y = starting_y + height;
        starting_y = 0;
    }
    // Check upper bound, adjust if too close to right and/or lower edge
    int canvas_length = display->width();
    int canvas_height = display->height();
    if ((starting_x + length) > canvas_length) {
        max_x = canvas_length - starting_x;
    }
    if ((starting_y + height) > canvas_height) {
        max_y = canvas_height - starting_y;
    }
    // Current position
    int cur_x = starting_x;
    int cur_y = starting_y;

    int index = 0;
    float intensity = 1.0;
    float luminance = 0.0;
    ColorData color = ColorData(red, green, blue);
    ColorData temp_color;
    ColorData cur_pixel;
    for (int i = 0; i < max_y; i++) {
        cur_y = i + starting_y;
        for (int j = 0; j < max_x; j++) {
            cur_x = j + starting_x;
            index = j + (i*length);
            cur_pixel = display->get_pixel(cur_x, cur_y);
            intensity = mask[index] * cur_pixel.luminance();
            temp_color = (color*intensity) + (cur_pixel*(1.0 - intensity));
            display->set_pixel(cur_x, cur_y, temp_color);
        }
    }
}

}  // namespace image_tools
