/*******************************************************************************
 * Name            : filter.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Filter class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include <iostream>
#include "./pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This abstract base class from which all Filters inherit defines the  
 * default implementation for ApplyFilter() and declares the interface for ModifyPixel().
 */

class Filter {
 public:
     explicit Filter(PixelBuffer *canvas);
     virtual ~Filter(void);
     /**
      * @return Returns canvas pointer for filter to use.
      */
     PixelBuffer *get_canvas(void);
     /**
      * @brief Applies filter to each pixel on the canvas.
      */
     virtual void ApplyFilter(void);
     /**
      * @brief Determines unique filter characteristics: must be implemented by derived subclass 
      */
     virtual void ModifyPixel(int x, int y) = 0;

 private:
     PixelBuffer *canvas_;
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
