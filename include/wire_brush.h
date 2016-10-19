/*******************************************************************************
 * Name            : wire_brush.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for WireBrush class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 10/18/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_WIRE_BRUSH_H_
#define INCLUDE_WIRE_BRUSH_H_
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
class WireBrush : public Tool {
 public:
    WireBrush(void);
    virtual ~WireBrush(void);

    void calculate_mask(void);
 private:
};
}  // namespace image_tools

#endif  // INCLUDE_WIRE_BRUSH_H_
