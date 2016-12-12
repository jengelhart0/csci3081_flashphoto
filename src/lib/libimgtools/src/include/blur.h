/*******************************************************************************
 * Name            : blur.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Blur class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/17/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_BLUR_H_
#define INCLUDE_BLUR_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include <vector>
#include "pixel_buffer.h"
#include "tool.h"
#include "blur_kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class holds declarations for the blur tool, and uses the blur kernel 
 * to apply the blur tool to the canvas.
 */
class Blur : public Tool {
 public:
    Blur(void);
    virtual ~Blur(void);
    /**
     * @brief Uses the passed blur kernel to modify a single pixel
     */
    void ModifyPixel(int x, int y, BlurKernel* kernel,
                     PixelBuffer* copy, PixelBuffer* display);
    /**
     * @brief Draws pixels under blur tool on canvas
     */
    void Draw(int x, int y,
              float red, float green, float blue,
              PixelBuffer* display);
    /**
     * @brief Determines values of blur tool mask
     */
    void CalculateMask(void);
    /**
     * @brief Calculates each kernel needed for mask
     */
    void CalculateKernels(void);

 private:
    std::vector<BlurKernel*> kernels_; /**< kernel vector to hold different sized blur kernels */
};
}  // namespace image_tools

#endif  // INCLUDE_BLUR_H_
