/*******************************************************************************
 * Name            : blur.cc
 * Project         : BrushWork
 * Module          : image_tools
 * Description     : Implementation of Blur class
 * Copyright       : 2016 CSCI3081W Group C07. All rights reserved.
 * Creation Date   : 11/17/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "iostream"
#include "include/blur.h"
#include "cmath"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Blur::Blur(void) : Tool(31, 31) {
    CalculateMask();
    CalculateKernels();
}

Blur::~Blur(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Blur::CalculateMask(void) {
    // Distance information
    float center_x = 15.5;
    float center_y = 15.5;
    float current_distance = sqrt(pow(center_x, 2.0) + pow(center_y, 2.0));
    float x_distance = center_x;
    float y_distance = center_y;

    // Intensity ends up being an index in kernels_
    float intensity = 0.0;
    float new_mask[31*31];
    int length = Tool::length();
    int height = Tool::height();
    int index = 0;
    for (int i = 0; i < height; i++) {
        y_distance = std::abs(i - center_y);
        for (int j = 0; j < length; j++) {
            x_distance = std::abs(j - center_x);
            index = j + i*length;
            current_distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
            intensity = std::floor(current_distance/5);
            new_mask[index] = intensity;
        }
    }
    Tool::mask(new_mask);
}

void Blur::CalculateKernels(void) {
    int kernel_size = 5;
    int kernel_delta = 2;
    float blur_delta = 1.0;
    float blur_amount = 0.25;
    BlurKernel* new_kernel;
    for (int i = 0; i <= 5; i++) {
        new_kernel = new BlurKernel(blur_amount, kernel_size);
        kernels_.insert(kernels_.begin(), new_kernel);
        kernel_size += kernel_delta;
        blur_amount *= 2.0;
    }
}

void Blur::ModifyPixel(int x, int y, BlurKernel *kernel,
  PixelBuffer *copy, PixelBuffer *display) {
    int kernel_dim = kernel->dimension();

    int starting_x = x - (kernel_dim / 2);
    int starting_y = y - (kernel_dim / 2);

    int ending_x = starting_x + kernel_dim - 1;
    int ending_y = starting_y + kernel_dim - 1;

    int canvas_width = display->width();
    int canvas_height = display->height();

    ColorData old_pixel = copy->get_pixel(x, y);
    ColorData modified_pixel = ColorData(0, 0, 0, 0);

    int i = 0;
    int j = 0;
    int kernel_x = 0;
    int kernel_y = 0;
    #pragma omp for
    for (i = starting_y; i <= ending_y; i++) {
        kernel_x = 0;
        if (i >= canvas_height || i < 0) { continue; }
        for (j = starting_x; j <= ending_x; j++) {
            if (j >= canvas_width || j < 0) { continue; }
            // aggregates new pixel values as we iterate through canvas/kernel
            modified_pixel = modified_pixel +
                            (copy->get_pixel(j, i) *
                            kernel->weight(kernel_x, kernel_y));
            kernel_x++;
        }
        kernel_y++;
    }
    ColorData new_pixel = (modified_pixel - old_pixel)
                        * kernel->filter_amount() + old_pixel;
    display->set_pixel(x, y, new_pixel);
}
void Blur::Draw(int x, int y,
  float red, float green, float blue,
  PixelBuffer* display) {
    // Mask-related variables
    int length = Tool::length();
    int height = Tool::height();
    float* mask = Tool::mask();
    // Canvas-related variables
    int canvas_height = display->height();
    int canvas_width = display->width();
    int starting_x = x - (length / 2);
    int starting_y = y - (height / 2);
    int cur_x = starting_x;
    int cur_y = starting_y;
    int index = 0;
    int kernel_index = 0;
    // First kernel will always be weakest
    BlurKernel *blur = kernels_.front();
    // Make a copy of the canvas
    // PixelBuffer copy = *display;
    #pragma omp for
    for (int i = 0; i < height; i++) {
        cur_y = i + starting_y;
        if (cur_y < 0 || cur_y >= canvas_height) { continue; }
        for (int j = 0; j < length; j++) {
            cur_x = j + starting_x;
            if (cur_x < 0 || cur_x >= canvas_width) { continue; }
            index = j + (i*length);
            kernel_index = static_cast<int>(mask[index]);
            blur = kernels_[kernel_index];
            ModifyPixel(cur_x, cur_y, kernels_.back(), display, display);
        }
    }
}

}  // namespace image_tools
