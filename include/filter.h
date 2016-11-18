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

#ifndef INCLUDE_FILTER_H_
#define INCLUDE_FILTER_H_
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
 * @brief This abstract base class from which all Filters inherit defines the  
 *        default implementation for ApplyFilter() and declares the interface for ModifyPixel().
 */

class Filter {
  public:
      Filter(PixelBuffer *canvas);
      virtual ~Filter(void);

      PixelBuffer *get_canvas(void);
      void set_canvas(PixelBuffer *new_canvasptr);
      virtual void ApplyFilter(void) = 0;
      /* 
       * determines filter characteristics: must be implemented by derived subclass 
       */
      virtual void ModifyPixel(int x, int y, PixelBuffer *canvas_copy) = 0;
//      virtual void ModifyPixel(int x, int y);

  private:
      PixelBuffer *canvas_;

};
} // namespace image_tools

#endif	// INCLUDE_FILTER_H
