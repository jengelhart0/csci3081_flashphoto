/*******************************************************************************
 * Name            : spray_can.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of SprayCan class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 10/18/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "iostream"
#include "include/spray_can.h"
#include "cmath"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
SprayCan::SprayCan(void) : Tool(41, 41) {
    CalculateMask();
}

SprayCan::~SprayCan(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void SprayCan::CalculateMask(void) {
    // Distance information
    float center_x = 20.0;
    float center_y = 20.0;
    float current_distance = sqrt(pow(center_x, 2.0) + pow(center_y, 2.0));
    float max_distance = current_distance;
    float x_distance = center_x;
    float y_distance = center_y;

    // Slope of the line used to calculate linear dropoff
    float slope = (-0.2/max_distance);

    float intensity = 0.0;
    float new_mask[41*41];
    int length = Tool::length();
    int height = Tool::height();
    int index = 0;
    for (int i = 0; i < height; i++) {
        y_distance = std::abs(i - center_y);
        for (int j = 0; j < length; j++) {
            x_distance = std::abs(j - center_x);
            // Pythagorean theorem to calculate distance to center
            current_distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
            intensity = (slope * current_distance) + 0.2;  // y = mx + b
            index = j + (i*length);
            new_mask[index] = intensity;
        }
    }
    Tool::mask(new_mask);
}
}  // namespace image_tools
