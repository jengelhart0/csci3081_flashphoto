/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Tool class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This parent class holds the default implementation for Draw() 
 * as well the pixel mask
 */
class Tool {
 public:
    Tool(int length, int height);
    virtual ~Tool(void);

    float* mask(void) { return mask_; }
    void mask(float new_mask[]);
    int height(void) { return height_; }
    int length(void) { return length_; }

    virtual void Draw(int x, int y,
        float red, float green, float blue,
        PixelBuffer* display);

    /*
     * Must be implemented by derived types
     */
    virtual void CalculateMask(void) = 0;

 private:
    float* mask_;
    int length_;
    int height_;
};
}  // namespace image_tools

#endif  // INCLUDE_TOOL_H_
