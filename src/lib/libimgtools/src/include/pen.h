/*******************************************************************************
 * Name            : pen.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Pen class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 10/11/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "./tool.h"

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
class Pen : public Tool {
 public:
    Pen(void);
    virtual ~Pen(void);
    /**
     * @brief Determines mask for the pen tool.
     */
    void CalculateMask(void);
 private:
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_PEN_H_
