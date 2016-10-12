/*******************************************************************************
 * Name            : spray_can.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for SprayCan class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_SPRAY_CAN_H_
#define INCLUDE_SPRAY_CAN_H_
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
class SprayCan {
 public:
    SprayCan(void);
    virtual ~SprayCan(void);

    void calculate_mask(void);
 private:
};
}  // namespace image_tools

#endif  // INCLUDE_SPRAY_CAN_H_
