/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Eraser class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "include/pixel_buffer.h"
#include "include/tool.h"

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
class Eraser : public Tool {
 public:
    Eraser(void);
    virtual ~Eraser(void);

    void CalculateMask(void);
    virtual void Draw(int x, int y,
        float red, float green, float blue,
        PixelBuffer* display);

 private:
};
}  // namespace image_tools

#endif  // INCLUDE_ERASER_H_
