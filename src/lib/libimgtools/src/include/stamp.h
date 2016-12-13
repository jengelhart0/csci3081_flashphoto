/*******************************************************************************
 * Name            : stamp.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Stamp class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/09/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_STAMP_H_
#define INCLUDE_STAMP_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "pixel_buffer.h"
#include "tool.h"

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
class Stamp : public Tool {
 public:
    explicit Stamp(PixelBuffer* stamp);
    virtual ~Stamp(void);
    /**
     * @brief Determines mask values for stamp tool.
     */
    void CalculateMask(void);
    /**
     * @brief Draws pixels under tool mask on the canvas.
     */
    void Draw(int x, int y,
        float red, float green, float blue,
        PixelBuffer* display);

 private:
    PixelBuffer* stamp_; /**< Buffer to hold stamp color data */
};
}  // namespace image_tools

#endif  // INCLUDE_STAMP_H_
