/*******************************************************************************
 * Name            : saturate.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Saturate class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_SATURATE_H_
#define INCLUDE_SATURATE_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "pixel_buffer.h"
#include "filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This abstract base class from which all Saturates inherit defines the  
 * default implementation for ApplySaturate() and declares the interface for ModifyPixel().
 */

class Saturate : public Filter {
 public:
      explicit Saturate(PixelBuffer *canvas);
      virtual ~Saturate(void);

      /**
       * @brief Set saturation value 
       */
      void saturation(float saturation) { saturation_ = saturation; }

      /** 
       * @brief Interpolate between grayscale image and original based on 
       * saturation value
       */
      void ModifyPixel(int x, int y);

 private:
      float saturation_;
};
}  // namespace image_tools

#endif  // INCLUDE_SATURATE_H_
