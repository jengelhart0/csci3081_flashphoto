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
#include "include/pixel_buffer.h"
#include "include/tool.h"
#include "include/blur_kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This parent class holds the default implementation for Draw() 
 * as well the pixel mask but nothing else.
 */
class Blur : public Tool {
 public:
    Blur(void);
    virtual ~Blur(void);

    void ModifyPixel(int x, int y, BlurKernel* kernel,
                     PixelBuffer* copy, PixelBuffer* display);
    void Draw(int x, int y,
              float red, float green, float blue,
              PixelBuffer* display);
    void CalculateMask(void);
    void CalculateKernels(void);

 private:
    std::vector<BlurKernel*> kernels_;
};
}  // namespace image_tools

#endif  // INCLUDE_BLUR_H_
