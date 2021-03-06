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

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "./pixel_buffer.h"

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
    /**
     * @return float array that represents each value of tool mask.
     */
    float* mask(void) { return mask_; }
    void mask(float new_mask[]);
    int height(void) { return height_; }
    int length(void) { return length_; }
    /**
     * @brief Draws pixels changed by tool onto canvas.
     */
    virtual void Draw(int x, int y,
        float red, float green, float blue,
        PixelBuffer* display);

    /**
     * @brief Determines tool mask values.
     * Must be implemented by derived types
     */
    virtual void CalculateMask(void) = 0;

 private:
    float* mask_; /**< Array of floats that determines shape/behavior of tool */
    int length_;
    int height_;
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_TOOL_H_
