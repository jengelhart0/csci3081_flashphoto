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
 * as well the pixel mask but nothing else.
 */
class Tool {
 public:
    Tool(int length, int height);
    virtual ~Tool(void)

    virtual void Draw(int x, int y,
        float red, float green, float blue
        PixelBuffer* display);
    float* mask(void) { return mask_; }

 private:
    float mask_[][];
};
}  // namespace image_tools

#endif  // INCLUDE_TOOL_H_
